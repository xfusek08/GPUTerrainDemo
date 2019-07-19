
#version 450

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 colorIn;

out vec3 vertColor;

uniform mat4 projectionMatrix; // Projection matrix
uniform mat4 viewMatrix; // View Matrix

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0f);
    vertColor = colorIn;
}
