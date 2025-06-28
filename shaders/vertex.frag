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


// Les informations sur le pixel cible
in vec3 FragPos;
in vec3 Normal;
in vec3 vColor;
in vec2 TexCoord;
in vec3 Tangent;
in vec3 Bitangent;


out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);

    // Ici le calcul de la normal map, utile pour donner du relief
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

    // Composante ambiante hémisphérique
    // Le but de l'hémisphérique est de tricher pour simuler le fait que les objets au sol font
    // rebondir la lumière provenant du ciel
    //TODO: Petit soucis ici ce système fonctionne bien dans le cas de lumière directionnelle,
    // par soucis de réalisme en réalité il faudrait que dans une scene ne contenant que de la ponctuelle
    // on ne fasse qu'un calcul de lumière ambiant classique par soucis de réalisme.
    // Pour l'instant ce système est convaincant dans les deux cas donc pas un soucis immense 
    vec3 upColor = vec3(1.0, 1.0, 1.0);    // lumière du ciel
    vec3 downColor = vec3(0.3, 0.3, 0.3);  // lumière du sol (ou ombre)
    float factor = norm.y * 0.5 + 0.5;     // interpole [-1,1] vers [0,1]
    vec3 ambient = mix(downColor, upColor, factor) * ambientStrength;
    vec3 result = ambient;

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float attenuation = 1.0;
        float lightIntensity = lights[i].intensity;

        if (lights[i].type == 0) { // Point light
            lightDir = normalize(lights[i].position - FragPos);
            float distance = length(lights[i].position - FragPos);
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));
        } 
        else if (lights[i].type == 1) { // Directional light
            lightDir = normalize(-lights[i].direction);
            attenuation = 1.0;
            lightIntensity *= 0.1; // diminue la lumière directionnelle
        } 
        else {
            lightDir = vec3(0.0);
            attenuation = 1.0;
        }

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = attenuation * diff * diffuseIntensity * diffuseColor * lights[i].color * lightIntensity;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

        float specMapVal = useSpecularMap ? 
            dot(texture(texture_specular, TexCoord).rgb, vec3(0.299, 0.587, 0.114)) : 1.0;

        vec3 specular = attenuation * specularStrength * specMapVal * spec * specularColor * lights[i].color * lightIntensity;

        result += diffuse + specular;
    }

    vec3 baseColor = useTexture ? texture(texture_diffuse, TexCoord).rgb : vColor;
    result *= baseColor;
    result = clamp(result, 0.0, 1.0);


    FragColor = vec4(result, 1.0);
}
