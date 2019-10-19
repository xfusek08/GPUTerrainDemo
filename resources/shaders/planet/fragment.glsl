
#version 430
out vec4 fColor;
in vec3 direction;

uniform uint regionResolution;

struct Region {
    vec3 position;
    vec3 color;
};

layout (std430) buffer regionBuffer { Region regions[]; };

#define REGION_ID    uint
#define FACE_ID      uint

#define INVALID_REGION_ID -1

#define FACE_FRONT   0
#define FACE_RIGHT   1
#define FACE_BACK    2
#define FACE_LEFT    3
#define FACE_NORTH   4
#define FACE_SOUTH   5
#define FACE_SOUTH   5
#define FACE_INVALID 99

FACE_ID faceIdFromPos(inout vec3 pos)
{
    vec3 absVector = abs(pos);
    float maxComp = max(max(absVector.x, absVector.y), absVector.z);
    pos /= maxComp; // normalize vector to surface of cube

    if (pos.z > 0.9999) {
        return FACE_FRONT;
    } else if (pos.z < -0.9999) {
        return FACE_BACK;
    } else if (pos.x > 0.9999) {
        return FACE_RIGHT;
    } else if (pos.x < -0.9999) {
        return FACE_LEFT;
    } else if (pos.y > 0.9999) {
        return FACE_NORTH;
    } else if (pos.y < -0.9999) {
        return FACE_SOUTH;
    }

    return FACE_INVALID;
}

mat3 ptFromFaceId(FACE_ID faceId)
{
    switch(faceId) {
        case FACE_FRONT: return mat3(
            vec3(1,0,0),
            vec3(0,1,0),
            vec3(0,0,1)
        );
        case FACE_RIGHT: return mat3(
            vec3(0,0,-1),
            vec3(0,1,0),
            vec3(1,0,0)
        );
        case FACE_BACK: return mat3(
            vec3(-1,0,0),
            vec3(0,1,0),
            vec3(0,0,-1)
        );
        case FACE_LEFT: return mat3(
            vec3(0,0,1),
            vec3(0,1,0),
            vec3(-1,0,0)
        );
        case FACE_NORTH: return mat3(
            vec3(1,0,0),
            vec3(0,0,-1),
            vec3(0,1,0)
        );
        case FACE_SOUTH: return mat3(
            vec3(1,0,0),
            vec3(0,0,1),
            vec3(0,-1,0)
        );
        default: return mat3(0);
    }
}

REGION_ID getRegionOnFace(in FACE_ID faceId, in vec3 local3dCoors)
{
    vec2 p = vec2(local3dCoors.x + 1.0f, 1.0f - local3dCoors.y) / 2.0f;
    uint x = uint(p.x * regionResolution);
    uint y = uint(p.y * regionResolution);
    return (faceId * regionResolution * regionResolution) + (regionResolution * y) + x;
}

REGION_ID regionFrom3D(in vec3 global3DPositon)
{
    FACE_ID actFace = faceIdFromPos(global3DPositon);
    mat3    facePt  = ptFromFaceId(actFace);
    return getRegionOnFace(actFace, global3DPositon * facePt);
}

float regionDistanceToVector(in REGION_ID region, in vec3 position)
{
    return distance(normalize(position), normalize(regions[region].position));
}

REGION_ID regionIdFromLocal3d(in FACE_ID faceId, in vec3 local3DPos)
{
	vec2 faceCoords_clamp = clamp(local3DPos.xy, -1.0f, 1.0f);
    vec2 faceCoords_extra = abs(faceCoords_clamp - vec2(local3DPos));
    float extra_dist = faceCoords_extra.x + faceCoords_extra.y;

    if (extra_dist == 0.0) {
        return getRegionOnFace(faceId, local3DPos);
    }
    if (min(faceCoords_extra.x, faceCoords_extra.y) > 0) {
        return INVALID_REGION_ID; // double wrap - not allowed
    } else {
        // wrap to neighbor cube face in 3D space
        return regionFrom3D(ptFromFaceId(faceId) * vec3(faceCoords_clamp.x, faceCoords_clamp.y, 1.0f - extra_dist));
    }

}

REGION_ID getClosestRegionId(in vec3 global3DPositon, out float distToClosest)
{
    vec3      pos             = global3DPositon;
    FACE_ID   faceId          = faceIdFromPos(pos);
    REGION_ID region          = getRegionOnFace(faceId, pos * ptFromFaceId(faceId));
    REGION_ID closestRegionID = region;
    float     gridstep        = 2.0f / float(regionResolution);
    int       gridX           = int(region % regionResolution);
    int       gridY           = int(float(region) / float(regionResolution)) % int(regionResolution);
    float     closestDistance = regionDistanceToVector(closestRegionID, global3DPositon);

    for (int y = gridY - 1; y <= gridY + 1; ++y) {
        for (int x = gridX - 1; x <= gridX + 1; ++x) {
            REGION_ID neighbor = regionIdFromLocal3d(faceId, vec3(
                -1.0f + ((gridstep / 2.0f) + gridstep * x),
                 1.0f - ((gridstep / 2.0f) + gridstep * y),
                 1)
            );
            if (neighbor != INVALID_REGION_ID) {
                float dist = regionDistanceToVector(neighbor, global3DPositon);
                if (dist < closestDistance) {
                    closestDistance = dist;
                    closestRegionID = neighbor;
                }
            }
        }
    }

    distToClosest = closestDistance;
    return closestRegionID;
}

void main()
{
    float distToClosest = 0.0;
    REGION_ID regId = getClosestRegionId(direction, distToClosest);
    fColor = distToClosest < (1.0f / float(10*regionResolution)) ? vec4(0,0,0,0) : vec4(regions[regId].color, 0);
}
