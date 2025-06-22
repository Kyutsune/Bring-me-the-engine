#version 330 core

in vec3 vColor;      // Couleur interpolée venant du vertex shader
in vec2 vTexCoords;  // Coordonnées de texture interpolées

out vec4 FragColor;  // Couleur finale du fragment

void main() {
    // Pour commencer on affiche simplement la couleur reçue du vertex shader
    FragColor = vec4(vColor, 1.0); 
}
