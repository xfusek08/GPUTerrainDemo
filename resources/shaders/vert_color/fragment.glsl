
#version 450

in vec3 vertColor;

out vec4 fColor;

void main()
{
    fColor = vec4(vertColor, 1.f);
}
