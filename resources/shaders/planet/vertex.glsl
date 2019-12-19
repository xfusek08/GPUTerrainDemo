
#version 430

uniform mat4 projectionMatrix;  // Projection matrix
uniform mat4 viewMatrix;        // View Matrix
uniform uint resolution;

out vec3 direction;

void main()
{
    uint vertPerFace = 6 * resolution * resolution;
    uint faceId      = gl_VertexID / vertPerFace;
    uint faceVertId  = gl_VertexID % vertPerFace;
    uint quadID      = faceVertId / 6;

    float step       = 1.0 / float(resolution);

    vec3 pos   = vec3(0.0, 0.0, 1.0);
    vec3 right = vec3(step, 0.0f, 0.0f);
    vec3 up    = vec3(0.0f, step, 0.0f);
    switch(faceVertId % 6) {
        case 0: pos += -right + up; break;
        case 1: pos += -right - up; break;
        case 2: pos += +right + up; break;
        case 3: pos += -right - up; break;
        case 4: pos += +right - up; break;
        case 5: pos += +right + up; break;
        default: pos += vec3(0,0,-2);
    }

    pos += vec3(
        -1.0 + step + (quadID % resolution) * 2 * step,
        1.0 - step - ((quadID / resolution) % resolution) * 2 * step,
        0.0
    );

    switch(faceId) {
        // case 0 : front face
        case 1: pos = vec3(pos.xz, -pos.y); break; // top face
        case 2: pos = vec3(pos.x, -pos.z, pos.y); break; // bottom face
        case 3: pos = vec3(-pos.z, pos.y, pos.x); break; // left face
        case 4: pos = vec3(pos.z, pos.y, -pos.x); break; // right face
        case 5: pos = vec3(-pos.x, pos.y, -pos.z); break; // back face
    }
    pos = normalize(pos);
    direction = pos;
    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0f);
}
