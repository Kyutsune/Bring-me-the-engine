#version 330 core
#define MAX_LIGHTS 8

struct Light {
    int type;        // 0 = ponctuelle, 1 = directionnelle
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

// Touts les paramètres relatifs à la lumière (systeme Phong pour le moment)
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

// Toutes les composantes de la texture (diffuse, normal, spéculaire)
uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

uniform bool useTexture;
uniform bool useNormalMap;
uniform bool useSpecularMap;

// Les informations sur le fog 
uniform vec3 fogColor;
uniform float fogStart;    
uniform float fogEnd;
uniform float fogDensity;  
uniform int fogType;       // 0: aucun, 1: linéaire, 2: exp, 3: exp²


// Les informations sur le pixel cible
in vec3 FragPos;
in vec3 Normal;
in vec3 vColor;
in vec2 TexCoord;
in vec3 Tangent;
in vec3 Bitangent;


out vec4 FragColor;

vec3 getNormal() {
    if (!useNormalMap) return normalize(Normal);

    vec3 T = normalize(Tangent);
    vec3 N = normalize(Normal);
    vec3 B = normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    vec3 normalMap = texture(texture_normal, TexCoord).rgb * 2.0 - 1.0;
    return normalize(TBN * normalMap);
}

float getFogFactor(float dist) {
    if (fogType == 1)
        return clamp((fogEnd - dist) / (fogEnd - fogStart), 0.0, 1.0);
    else if (fogType == 2)
        return exp(-fogDensity * dist);
    else if (fogType == 3)
        return exp(-pow(fogDensity * dist, 2.0));
    else
        return 1.0;
}

vec3 calcAmbient(vec3 norm) {
    vec3 upColor = vec3(1.0, 1.0, 1.0);
    vec3 downColor = vec3(0.3, 0.3, 0.3);
    float factor = norm.y * 0.5 + 0.5;
    return mix(downColor, upColor, factor) * ambientStrength;
}

vec3 calcLight(Light light, vec3 norm, vec3 viewDir, vec3 fragPos) {
    vec3 lightDir;
    float attenuation = 1.0;
    float lightIntensity = light.intensity;

    if (light.type == 0) {
        lightDir = normalize(light.position - fragPos);
        float distance = length(light.position - fragPos);
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    } else if (light.type == 1) {
        lightDir = normalize(-light.direction);
        attenuation = 1.0;
        lightIntensity *= 0.1;
    } else {
        lightDir = vec3(0.0);
        attenuation = 1.0;
    }

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = attenuation * diff * diffuseIntensity * diffuseColor * light.color * lightIntensity;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    float specMapVal = useSpecularMap ? dot(texture(texture_specular, TexCoord).rgb, vec3(0.299, 0.587, 0.114)) : 1.0;
    vec3 specular = attenuation * specularStrength * specMapVal * spec * specularColor * light.color * lightIntensity;

    return diffuse + specular;
}

void main() {
    vec3 norm = getNormal();
    vec3 viewDir = normalize(viewPos - FragPos);

    float distance_to_obj = length(viewPos - FragPos);
    float fogFactor = getFogFactor(distance_to_obj);

    vec3 result = calcAmbient(norm);

    for (int i = 0; i < numLights; i++) {
        result += calcLight(lights[i], norm, viewDir, FragPos);
    }

    vec3 baseColor = useTexture ? texture(texture_diffuse, TexCoord).rgb : vColor;
    result *= baseColor;
    result = clamp(result, 0.0, 1.0);

    vec3 finalColor = mix(fogColor, result, fogFactor);
    FragColor = vec4(finalColor, 1.0);
}
