
#version 430

in vec3 facePos;

out vec4 fColor;

void main()
{
    float col = length(facePos.xy);
    fColor = vec4(col,col,col,col);
}
