#version 330 core

in vec4 FragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main() {
    float lightDistance = length(FragPos.xyz - lightPos);
    lightDistance = lightDistance / farPlane; 
    lightDistance = clamp(lightDistance, 0.0, 1.0);
    gl_FragDepth = lightDistance;
}