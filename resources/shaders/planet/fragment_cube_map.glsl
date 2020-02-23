
#version 430

out vec4 fColor;

in vec3 direction;

// uniform uint doWarp;

uniform samplerCube warpedTexture;
// uniform samplerCube unwarpedTexture;

void main()
{
    // if (doWarp == 0) {
    //     fColor = texture(unwarpedTexture, direction);
    // } else {
    //     fColor = texture(warpedTexture, direction);
    // }
    fColor = texture(warpedTexture, direction);
}
