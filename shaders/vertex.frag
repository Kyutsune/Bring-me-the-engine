#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 vColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 FragColor;

void main() {
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    
    // ✅ Normalisez l'intensité (1.0 = intensité normale)
    vec3 ambient = 0.2 * vColor;
    vec3 diffuse = diff * vColor;  // Sans intensité d'abord
    
    vec3 finalColor = ambient + diffuse;
    FragColor = vec4(finalColor, 1.0);
}
