
#version 430

out vec4 fColor;

in vec2 uv;

uniform sampler2D tex;

void main()
{
    fColor = vec4(255, 0, 0, 0);
}
