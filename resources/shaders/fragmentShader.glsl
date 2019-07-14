// #version 430

// in vec3 vPosition; // fragment position
// in vec3 vNormal; // fragment normal

// layout(location=0) out vec4 fColor; // output fragment color

// uniform vec3 cameraPosition; // position of camera
// uniform vec3 lightPosition; // position of light

// uniform vec3 lightColor = vec3(1.f, 1.f, 1.f); // lightColor = white
// // specualrColor = white
// uniform vec3 specularColor = vec3(1.f, 1.f, 1.f);
// uniform float shininessFactor = 40.f; // shininess factor
// uniform float eps = .001f;

// void main()
// {
//     vec3 light = normalize(lightPosition - vPosition);
//     vec3 camera = normalize(cameraPosition - vPosition);

//     // diffuseColor calculation
//     vec3 diffuseColor;
//     float nY = vNormal.y;
//     if (abs(nY - 1.f) <= eps)
//         // nY == 1 => normal goes vertical up
//         diffuseColor = vec3(1.f, 1.f, 1.f); // diffuseColor = white
//     else if (nY < 0 || abs(nY) <= eps)
//         // nY < 0 OR nY == 0 => normal goes down or it is horizontal
//         diffuseColor = vec3(0.f, 1.f, 0.f); // diffuseColor = green
//     else
//     { // nY < 1 AND nY > 0
//         // diffuseColor = linear interpolation of white and green
//         float t = abs(nY * nY);
//         diffuseColor = vec3(t, 1.f, t);
//     }
//     vec3 diffuse = lightColor
//          * diffuseColor
//          * clamp(dot(vNormal, light), 0.f, 1.f);

//     vec3 R = normalize(-1.f * reflect(light, vNormal));
//     vec3 specular = lightColor
//         * specularColor
//         * pow(clamp(dot(R, camera), 0.f, 1.f), shininessFactor);

//     write output color
//     fColor = vec4(diffuse + specular, 1.f);
//     fColor = vec4(vPosition, 1.f);
// }

#version 330

out vec4 fragColor;

void main()
{
    fragColor = vec4(0.5,0.5,0.5,1.0f);
}
