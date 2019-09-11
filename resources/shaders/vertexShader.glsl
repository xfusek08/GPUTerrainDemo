
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 colorIn;

out vec3 vertPosition;
out vec3 vertColor;
out vec3 vertNormal;

uniform mat4 projectionMatrix; // Projection matrix
uniform mat4 viewMatrix; // View Matrix

float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p){
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);

    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}

void main()
{
    vec3 pos = position;

    // pos *= 1 + pow(noise(pos * 3.f), 2.f);
    // pos = 1.f + (0.7f + 0.3f * noise(pos * 10.f));
    // pos = 1.f + (0.9f + 0.1f * noise(pos * 20.f));

    vertColor = colorIn;
    vertNormal = position;
    vertPosition = position;
    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1.0f);
}
