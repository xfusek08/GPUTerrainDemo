
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

out vec3 vertColor;

uniform mat4 projectionMatrix;  // Projection matrix
uniform mat4 viewMatrix;        // View Matrix

void main()
{
    vertColor = color;
    gl_Position = projectionMatrix * viewMatrix * vec4(1.2 * position, 1.0f);
}
