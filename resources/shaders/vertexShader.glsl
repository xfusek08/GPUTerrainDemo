// #version 430
// layout(location=0)in vec3 position; // vertex position
// layout(location=1)in vec3 normal; // vertex normal

// out vec3 vPosition; // <- vertex position
// out vec3 vNormal; // <- vertex normal

// // uniform mat4 projectionMatrix; // Projection matrix
// // uniform mat4 viewMatrix; // View Matrix

// void main()
// {
//     // transform vertices to clip-space
//     // World space -(View matrix)-> View space
//     // View space -(Projection matrix)-> Clip space
//     gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.f);

//     // set output attributes
//     vPosition = position;
//     vNormal = normal;
// }

#version 450

in layout(location = 0) vec3 position;

uniform mat4 projectionMatrix; // Projection matrix
uniform mat4 viewMatrix; // View Matrix

void main()
{
    // mat4 mvp = projectionMatrix * viewMatrix;
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0f);
    // gl_Position = vec4(position, 1.0f);
}
