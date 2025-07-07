#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];

in vec4 FragPosWorld[]; // Recevoir du vertex shader
out vec4 FragPos;       // Envoyer au fragment shader

void main() {
    for (int face = 0; face < 6; ++face) {
        gl_Layer = face; // Important pour le rendu direct vers la cubemap
        for (int i = 0; i < 3; ++i) {
            FragPos = FragPosWorld[i]; // Position world space
            gl_Position = shadowMatrices[face] * FragPosWorld[i];
            EmitVertex();
        }
        EndPrimitive();
    }
}