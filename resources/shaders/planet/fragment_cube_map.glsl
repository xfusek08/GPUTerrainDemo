
#version 430

out vec4 fColor;

in vec3 direction;

uniform samplerCube tex;

void main()
{
    fColor = texture(tex, direction);
}
