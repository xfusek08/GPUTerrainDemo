
#version 430
out vec4 fColor;
in vec3 direction;

uniform uint regionResolution;
uniform uint warpTexture;

struct Region {
    vec3 position;
    vec3 color;
};

layout (std430) buffer regionBuffer { Region regions[]; };

bool dthrown = false;
#define THROW_COLOR(c) dthrown = true; fColor = c
#define IS_ERROR       (dthrown == true)
#define ASSERTC(e,c)   if (!(e)) THROW_COLOR(c)
#define ASSERT(e)      if (!(e)) THROW_COLOR(vec4(1,1,1,0))

#define REGION_ID    uint
#define FACE_ID      uint

#define INVALID_REGION_ID -1

#define FACE_FRONT   0
#define FACE_RIGHT   1
#define FACE_BACK    2
#define FACE_LEFT    3
#define FACE_NORTH   4
#define FACE_SOUTH   5
#define FACE_INVALID 99

#define MAGIC_ANGLE 0.868734829276 // radians
float tan_warp_theta;

/* Unwarp to go sphere -> cube */
vec2 unwarp(vec2 x) {
    if (warpTexture != 0) {
        return atan(x * tan_warp_theta) / MAGIC_ANGLE;
    }
    return x;
}

vec3 normalizeToCube(vec3 pos)
{
    vec3 absVector = abs(pos);
    float maxComp = max(max(absVector.x, absVector.y), absVector.z);
    return pos /= maxComp; // normalize vector to surface of cube
}

vec3 sphereLocalToCubeLocal(vec3 coords)
{
    vec3 p = normalizeToCube(coords);
    return vec3(unwarp(p.xy), p.z);
}

FACE_ID faceIdFromPos(in vec3 sphereGlobal3dCoords)
{
    vec3 pos = normalizeToCube(sphereGlobal3dCoords);

    if (pos.z > 0.9999) {
        return FACE_FRONT;
    } else if (pos.z < -0.99999) {
        return FACE_BACK;
    } else if (pos.x >  0.99999) {
        return FACE_RIGHT;
    } else if (pos.x < -0.99999) {
        return FACE_LEFT;
    } else if (pos.y >  0.99999) {
        return FACE_NORTH;
    } else if (pos.y < -0.99999) {
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

REGION_ID getRegionOnFace(in FACE_ID faceId, in vec3 cubeLocal3dCoords)
{
    vec2 p = clamp(vec2(cubeLocal3dCoords.x + 1.0f, 1.0f - cubeLocal3dCoords.y) / 2.0f, 0.0f, 1.0f);
    uint x = uint(p.x * regionResolution);
    uint y = uint(p.y * regionResolution);
    return (faceId * regionResolution * regionResolution) + (regionResolution * y) + x;
}

float regionDistanceToVector(in REGION_ID region, in vec3 position)
{
    return distance(normalize(position), normalize(regions[region].position));
}

REGION_ID regionIdFromLocal3d(in FACE_ID faceId, in vec3 cubeLocal3dCoords)
{
    vec2  faceCoords_clamp = clamp(cubeLocal3dCoords.xy, -1.0f, 1.0f);
    vec2  faceCoords_extra = abs(faceCoords_clamp - cubeLocal3dCoords.xy);
    float extra_dist       = faceCoords_extra.x + faceCoords_extra.y;

    if (extra_dist == 0.0) {
        return getRegionOnFace(faceId, cubeLocal3dCoords);
    }
    if (min(faceCoords_extra.x, faceCoords_extra.y) > 0) {
        return INVALID_REGION_ID; // double wrap - not allowed
    } else {
        // wrap to neighbor cube face in 3D space
        vec3    cubeGlobalCoords = ptFromFaceId(faceId) * vec3(faceCoords_clamp.x, faceCoords_clamp.y, 1.0f - extra_dist);
        FACE_ID newFaceId        = faceIdFromPos(cubeGlobalCoords);
        return getRegionOnFace(newFaceId, cubeGlobalCoords * ptFromFaceId(newFaceId));
    }
}

REGION_ID getClosestRegionId(in vec3 sphereGlobal3dCoords, out float distToClosest)
{
    vec3      speheLocalPos   = sphereGlobal3dCoords;
    FACE_ID   faceId          = faceIdFromPos(speheLocalPos);
    REGION_ID region          = getRegionOnFace(faceId, sphereLocalToCubeLocal(speheLocalPos * ptFromFaceId(faceId)));
    REGION_ID closestRegionId = region;
    float     closestDistance = regionDistanceToVector(closestRegionId, sphereGlobal3dCoords);
    float     gridHalfStep    = 1.0f / float(regionResolution);
    float     gridStep        = 2.0f * gridHalfStep;
    int       gridX           = int(region % regionResolution);
    int       gridY           = int(double(region % (regionResolution * regionResolution)) / double(regionResolution));

    for (int y = gridY - 1; y <= gridY + 1; ++y) {
        for (int x = gridX - 1; x <= gridX + 1; ++x) {
            if (x == gridX && y == gridY)
                continue;
            REGION_ID neighbor = regionIdFromLocal3d(faceId, vec3(
                -1.0f + (gridHalfStep + gridStep * x),
                1.0f - (gridHalfStep + gridStep * y),
                1
            ));
            if (neighbor != INVALID_REGION_ID) {
                float dist = regionDistanceToVector(neighbor, sphereGlobal3dCoords);
                if (dist < closestDistance) {
                    closestDistance = dist;
                    closestRegionId = neighbor;
                }
            }
        }
    }

    distToClosest = closestDistance;
    return closestRegionId;
}

void main()
{
    tan_warp_theta = tan(MAGIC_ANGLE);
    float distToClosest = 0.0;
    REGION_ID regId = getClosestRegionId(direction, distToClosest);

    if (!IS_ERROR) {
        fColor = distToClosest < (1.0f / float(10*regionResolution)) ? vec4(0,0,0,0) : vec4(regions[regId].color, 0);
    }
}
