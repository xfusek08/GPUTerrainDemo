
#version 450

in vec3 vertPosition;
in vec3 vertColor;
in vec3 vertNormal;

out vec4 fColor; // output fragment color

uniform vec3 cameraPosition; // position of camera

uniform vec3 lightColor         = vec3(1.f, 1.f, 1.f); // lightColor = white
uniform vec3 lightPosition      = vec3(2.f,2.f,2.f);

// specularColor = white
uniform vec3 specularColor      = vec3(1.0f, 1.0f, 1.0f);
uniform float shininessFactor   = 40.f; // shininess factor

void main()
{
    vec3 light = normalize(lightPosition - vertPosition);
    vec3 camera = normalize(cameraPosition - vertPosition);

    // diffuseColor calculation

    vec3 diffuseColor = vec3(
        1.f,
        1.f,
        1.f
    );

    float nY = vertNormal.y;

    vec3 ambient = diffuseColor * 0.5f;

    vec3 diffuse =
        lightColor *
        diffuseColor *
        clamp(dot(vertNormal, light), 0.f, 1.f);

    vec3 R = normalize(-1.f * reflect(light, vertNormal));
    vec3 specular =
        lightColor *
        specularColor *
        pow(clamp(dot(R, camera), 0.f, 1.f), shininessFactor);

    // write output color
    fColor = vec4(ambient + diffuse + specular, 1.f);
    // fColor = vec4(vertPosition, 1.f);
}
