
#version 430

uniform mat4 projectionMatrix;  // Projection matrix
uniform mat4 viewMatrix;        // View Matrix
uniform uint resolution;
uniform uint showCube;

out vec3 direction;

vec3 calculateSphereVertex(uint resolution);

void main()
{
    vec3 pos = calculateSphereVertex(resolution);

    if (showCube == 0) {
        pos = normalize(pos);
    }

    direction = pos;
    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0f);
}
