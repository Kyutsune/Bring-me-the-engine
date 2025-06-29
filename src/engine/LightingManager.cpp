#include "engine/LightingManager.h"
#include <iostream>

LightingManager::LightingManager() {
    // // Par défaut, on peut initialiser une lumière blanche
    // lights.push_back({Vec3(0, 2, -3), Vec3(1,1,1), 1.0f});
}

void LightingManager::addLight(const Light & light) {
    lights.push_back(light);
}

void LightingManager::clearLights() {
    lights.clear();
}

void LightingManager::applyLightning(Shader & shader, const Vec3 & viewPos) {
    shader.use();

    int numLights = static_cast<int>(lights.size());
    if (numLights > MAX_LIGHTS) {
        numLights = MAX_LIGHTS;
        std::cout << "Attention: trop de lumières, on va limiter à " << MAX_LIGHTS << " lumières.\n";
    }
    // std::cout<< "Nombre de lumières appliquées: " << numLights << "\n";
    shader.set("numLights", numLights);

    for (int i = 0; i < numLights; ++i) {
        std::string idx = std::to_string(i);
        shader.set("lights[" + idx + "].type", (int)lights[i].type);
        shader.set("lights[" + idx + "].position", lights[i].position);
        shader.set("lights[" + idx + "].direction", lights[i].direction.normalized());
        shader.set("lights[" + idx + "].color", Vec3(lights[i].color.r, lights[i].color.g, lights[i].color.b));
        shader.set("lights[" + idx + "].intensity", lights[i].intensity);
        shader.set("lights[" + idx + "].constant", lights[i].constant);
        shader.set("lights[" + idx + "].linear", lights[i].linear);
        shader.set("lights[" + idx + "].quadratic", lights[i].quadratic);
        // std::cout<< "Lumière " << i << ": Position = " << lights[i].position
        //          << ", Couleur = " << lights[i].color
        //          << ", Intensité = " << lights[i].intensity << "\n";
    }

    // Paramètres globaux
    shader.set("ambientColor", lightingSettings.ambientColor);
    shader.set("ambientStrength", lightingSettings.ambientStrength);

    shader.set("diffuseColor", lightingSettings.diffuseColor);
    shader.set("diffuseIntensity", lightingSettings.diffuseIntensity);

    shader.set("specularColor", lightingSettings.specularColor);
    shader.set("specularStrength", lightingSettings.specularStrength);
    shader.set("shininess", lightingSettings.shininess);

    // Paramètres sur le fog
    shader.setVec3("fogColor", Vec3(lightingSettings.fogColor.r/255.0f, 
                                    lightingSettings.fogColor.g/255.0f, 
                                    lightingSettings.fogColor.b/255.0f));
    shader.setFloat("fogStart", lightingSettings.fogStart);
    shader.setFloat("fogEnd", lightingSettings.fogEnd);
    shader.setFloat("fogDensity", lightingSettings.fogDensity);
    shader.setInt("fogType", lightingSettings.fogType);



    shader.set("viewPos", viewPos);
}

void LightingManager::applyPosLights(Shader & shader) {
    shader.use();
    shader.set("color", Vec3(colorMeshLight));
}
