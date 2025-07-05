#version 410 core

uniform vec3 lightPos;
uniform float farPlane;

in vec4 FragPosWorld; // si tu veux calculer la distance, sinon tu peux passer directement la position

void main() {
    float lightDistance = length(FragPosWorld.xyz - lightPos);
    lightDistance /= farPlane;
    lightDistance = clamp(lightDistance, 0.0, 1.0);
    gl_FragDepth = lightDistance;
}