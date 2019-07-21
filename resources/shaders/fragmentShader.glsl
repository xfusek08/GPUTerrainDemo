
#version 330

in vec3 vertColor;

out vec4 fragColor;

void main()
{
    vec3 finalColor = vertColor;
    if ((finalColor.x + finalColor.y + finalColor.z) == 0.0f)
        finalColor = vec3(0.5f, 0.5f, 0.5f);
    fragColor = vec4(finalColor,1.0f);
}
