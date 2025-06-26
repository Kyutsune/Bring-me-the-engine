#version 330 core
#define MAX_LIGHTS 8

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

uniform int numLights;
uniform Light lights[MAX_LIGHTS];

uniform vec3 ambientColor;
uniform float ambientStrength;
uniform vec3 diffuseColor;
uniform float diffuseIntensity;
uniform vec3 specularColor;
uniform float specularStrength;
uniform float shininess;

uniform vec3 viewPos;
uniform sampler2D texture_diffuse;
uniform bool useTexture;

in vec3 FragPos;
in vec3 Normal;
in vec3 vColor;
in vec2 TexCoord; 

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Composante Ambiante
    vec3 ambient = ambientStrength * ambientColor;
    vec3 result = ambient;

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - FragPos);

        // Composante Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * diffuseIntensity * diffuseColor * lights[i].color * lights[i].intensity;

        // Composante Spéculaire
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular = specularStrength * spec * specularColor * lights[i].color * lights[i].intensity;

        result += diffuse + specular;
    }

    vec3 baseColor = useTexture ? texture(texture_diffuse, TexCoord).rgb : vColor;
    result *= baseColor;

    FragColor = vec4(result, 1.0);
}
