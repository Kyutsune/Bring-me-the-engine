#version 410 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 shadowMatrix;

out vec4 FragPosWorld; 

void main() {
    FragPosWorld = model * vec4(aPos, 1.0); 
    gl_Position = shadowMatrix * model * vec4(aPos, 1.0);
}