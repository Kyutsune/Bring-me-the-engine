#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform samplerCube depthCubemap;
uniform int faceIndex;

void main() {
    vec2 uv = TexCoords * 2.0 - 1.0;
    vec3 sampleDir;

    if (faceIndex == 0) sampleDir = vec3(1.0, -uv.y, -uv.x);
    else if (faceIndex == 1) sampleDir = vec3(-1.0, -uv.y, uv.x);
    else if (faceIndex == 2) sampleDir = vec3(uv.x, 1.0, uv.y);
    else if (faceIndex == 3) sampleDir = vec3(uv.x, -1.0, -uv.y);
    else if (faceIndex == 4) sampleDir = vec3(uv.x, -uv.y, 1.0);
    else if (faceIndex == 5) sampleDir = vec3(-uv.x, -uv.y, -1.0);
    else sampleDir = vec3(0.0);

    float depthValue = texture(depthCubemap, sampleDir).r;

    FragColor = vec4(vec3(depthValue), 1.0);
}
