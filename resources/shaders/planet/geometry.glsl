
#version 430

#define DIVISION 10.0

#define NORMALIZE

layout(points) in;
layout(triangle_strip, max_vertices = 220) out; // 2 * (DIVISION + 1) * DIVISION

out vec2 texCoords;

uniform mat4 projectionMatrix;  // Projection matrix
uniform mat4 viewMatrix;        // View Matrix

void main()
{
    // mat4 PV = projectionMatrix * viewMatrix;
    mat4 VP = projectionMatrix * viewMatrix;

    vec3 right  = vec3(0.0);
    vec3 up     = vec3(0.0);
    vec3 pos    = gl_in[0].gl_Position.xyz;

    if (pos.z == 1) {       // FRONT_FACE
        right  = vec3(-1.0, 0.0, 0.0);
        up     = vec3(0.0, 1.0, 0.0);
    } else if (pos.z == -1) { // BACK_FACE
        right  = vec3(1.0, 0.0, 0.0);
        up     = vec3(0.0, 1.0, 0.0);
    } else if (pos.x == 1) {  // LEFT_FACE
        right  = vec3(0.0, 0.0, 1.0);
        up     = vec3(0.0, 1.0, 0.0);
    } else if (pos.x == -1) { // RIGHT_FACE
        right  = vec3(0.0, 0.0, -1.0);
        up     = vec3(0.0, 1.0, 0.0);
    } else if (pos.y == 1) {  // TOP_FACE
        right  = vec3(-1.0, 0.0, 0.0);
        up     = vec3(0.0, 0.0, -1.0);
    } else if (pos.y == -1) { // BOTTOM_FACE
        right  = vec3(-1.0, 0.0, 0.0);
        up     = vec3(0.0, 0.0, 1.0);
    }

    vec3 leftBottom = pos - right - up;
    vec3 stepRight  = right / (DIVISION / 2.0);
    vec3 stepUp     = up / (DIVISION / 2.0);
    for (int k = 0; k < DIVISION; ++k) {
        for (int i = 0; i < DIVISION + 1; ++i) {
            #ifdef NORMALIZE

                texCoords = vec2(i / (DIVISION + 1), k / DIVISION);
                gl_Position = VP * vec4(normalize(leftBottom), gl_in[0].gl_Position.w);
                EmitVertex();

                texCoords = vec2(i / (DIVISION + 1), (k + 1) / DIVISION);
                gl_Position = VP * vec4(normalize(leftBottom + stepUp), gl_in[0].gl_Position.w);
                EmitVertex();
            #else
                gl_Position = VP * vec4((leftBottom), gl_in[0].gl_Position.w);
                EmitVertex();
                gl_Position = VP * vec4((leftBottom + stepUp), gl_in[0].gl_Position.w);
                EmitVertex();
            #endif
            leftBottom += stepRight;
        }
        EndPrimitive();
        leftBottom += stepUp - (DIVISION + 1) * stepRight;
    }
}