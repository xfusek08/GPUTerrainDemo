
#version 430
out vec4 fColor;
in vec3 direction;

uniform uint regionResolution;
uniform uint showRegionBounds;
uniform uint showCube;
uniform uint isWarp;

struct Region {
    vec3 position;
    vec3 color;
};

layout (std430) buffer regionBuffer { Region regions[]; };

bool dthrown = false;
#define IS_ERROR       (dthrown)
#define THROW_COLOR(c) { if (!dthrown) { dthrown = true; fColor = c; } }
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

#define NEARLY_ONE       0.99999

#define MAGIC_ANGLE 0.868734829276 // radians
float tan_warp_theta;

/* Unwarp to go sphere -> cube */
vec2 unwarp(vec2 x)
{
    if (isWarp == 0) {
        return x;
    }
    return atan(x * tan_warp_theta) / MAGIC_ANGLE;
}

vec3 toCubeFace(vec3 direction)
{
    vec3 absPos = abs(direction);
    return direction /= max(max(absPos.x, absPos.y), absPos.z);
}

/**
 * Just used to visualize distance from spherical Voronoi cell edges.
 * From: https://www.shadertoy.com/view/MtBGRD
 */
float bisectorDistance(vec3 p, vec3 a, vec3 b)
{
    if (showCube == 0) {
        vec3 n1 = cross(a,b);
        vec3 n2 = normalize(cross(n1, 0.5*(normalize(a)+normalize(b))));
        return abs(dot(p, n2));
    } else {
        p = toCubeFace(p);
        a = toCubeFace(a);
        b = toCubeFace(b);
        vec3 N = a - b;
        vec3 V = b + (N / 2);
        vec3 u = p - V;
        return abs(dot(u, normalize(N)));
    }
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

FACE_ID faceIdFromPos(in vec3 gPos)
{
    vec3 pos = normalizeToCube(gPos);

    if (pos.z > NEARLY_ONE) {
        return FACE_FRONT;
    } else if (pos.z < -NEARLY_ONE) {
        return FACE_BACK;
    } else if (pos.x >  NEARLY_ONE) {
        return FACE_RIGHT;
    } else if (pos.x < -NEARLY_ONE) {
        return FACE_LEFT;
    } else if (pos.y >  NEARLY_ONE) {
        return FACE_NORTH;
    } else if (pos.y < -NEARLY_ONE) {
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
    if (showCube == 0) {
        return distance(normalize(position), normalize(regions[region].position));
    } else {
        return distance(toCubeFace(position), toCubeFace(regions[region].position));
    }
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

REGION_ID getClosestRegionId(in vec3 gPos, out float distToClosest, out float distToBorder)
{
    // constant
    vec3      speheLocalPos   = gPos;
    FACE_ID   faceId          = faceIdFromPos(speheLocalPos);
    REGION_ID region          = getRegionOnFace(faceId, sphereLocalToCubeLocal(speheLocalPos * ptFromFaceId(faceId)));
    REGION_ID closestRegionId = region;
    float     gridHalfStep    = 1.0f / float(regionResolution);
    float     gridStep        = 2.0f * gridHalfStep;
    int       gridX           = int(region % regionResolution);
    int       gridY           = int(double(region % (regionResolution * regionResolution)) / double(regionResolution));

    // outs
    distToClosest = regionDistanceToVector(closestRegionId, gPos); // closest distance
    distToBorder  = 2.0; // some arbitrary large number

    // second closest
    REGION_ID secondClosestRegionId = INVALID_REGION_ID;
    float secondClosestDistance = 2.0;

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
                float dist = regionDistanceToVector(neighbor, gPos);
                if (dist < distToClosest) {
                    secondClosestRegionId = closestRegionId;
                    secondClosestDistance = distToClosest;
                    closestRegionId = neighbor;
                    distToClosest = dist;
                } else if (dist < secondClosestDistance) {
                    secondClosestRegionId = neighbor;
                    secondClosestDistance = dist;
                }
            }
        }
    }

    distToBorder = bisectorDistance(gPos, regions[closestRegionId].position, regions[secondClosestRegionId].position);

    return closestRegionId;
}

void main()
{
    float distToClosest;
    float distToSecondClosest;
    float distToBorder;
    float distToCenter;

    tan_warp_theta = tan(MAGIC_ANGLE); // global magic warp value
    REGION_ID regId = getClosestRegionId(direction, distToClosest, distToBorder);


    float borderTreshold = (1.0f / float(10 * regionResolution));

    if (showCube == 1) {
        float cubeTreshold = (1.0f - (borderTreshold*0.5));
        uint ones = ((abs(direction.x) >= cubeTreshold) ? 1 : 0)
            + ((abs(direction.y) >= cubeTreshold) ? 1 : 0)
            + ((abs(direction.z) >= cubeTreshold) ? 1 : 0);
        if (ones > 1) {
            THROW_COLOR(vec4(0.1, 0.1, 0.2, 1));
            return;
        }
    }

    if (showRegionBounds == 1 && (
        distToClosest < borderTreshold
        ||
        distToBorder < (borderTreshold / 3)
    )) {
        THROW_COLOR(vec4(0, 0, 0, 1));
        return;
    }

    THROW_COLOR(vec4(regions[regId].color, 1));
}
