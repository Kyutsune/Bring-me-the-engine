#version 330 core
uniform sampler2D depthMap;
in vec2 TexCoords;
out vec4 FragColor;

void main() {
    float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
}