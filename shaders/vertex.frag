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
uniform sampler2D texture_normal;
uniform bool useTexture;
uniform bool useNormalMap;

in vec3 FragPos;
in vec3 Normal;
in vec3 Tangent;
in vec3 Bitangent;
in vec3 vColor;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    if (useNormalMap) {
        // Construction matrice TBN
        vec3 T = normalize(Tangent);
        vec3 N = normalize(Normal);
        vec3 B = normalize(cross(N, T));
        mat3 TBN = mat3(T, B, N);

        // Extraction normale depuis la normal map, conversion [0,1] -> [-1,1]
        vec3 normalMap = texture(texture_normal, TexCoord).rgb;
        normalMap = normalMap * 2.0 - 1.0;

        norm = normalize(TBN * normalMap);
    }

    vec3 viewDir = normalize(viewPos - FragPos);

    // Composante ambiante
    vec3 ambient = ambientStrength * ambientColor;
    vec3 result = ambient;

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - FragPos);

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * diffuseIntensity * diffuseColor * lights[i].color * lights[i].intensity;

        // Spéculaire
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular = specularStrength * spec * specularColor * lights[i].color * lights[i].intensity;

        result += diffuse + specular;
    }

    vec3 baseColor = useTexture ? texture(texture_diffuse, TexCoord).rgb : vColor;
    result *= baseColor;

    FragColor = vec4(result, 1.0);
}
