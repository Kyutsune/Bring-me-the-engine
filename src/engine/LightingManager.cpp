#include "engine/LightingManager.h"
#include <iostream>

LightingManager::LightingManager() {
    // // Par défaut, on peut initialiser une lumière blanche
    // lights.push_back({Vec3(0, 2, -3), Vec3(1,1,1), 1.0f});
}

void LightingManager::addLight(const Light& light) {
    lights.push_back(light);
}

void LightingManager::clearLights() {
    lights.clear();
}

void LightingManager::apply(Shader& shader, const Vec3& viewPos) {
    shader.use();

    int numLights = static_cast<int>(lights.size());
    if(numLights > MAX_LIGHTS) {
        numLights = MAX_LIGHTS; 
        std::cout<< "Attention: trop de lumières, on va limiter à " << MAX_LIGHTS << " lumières.\n";
    }
    // std::cout<< "Nombre de lumières appliquées: " << numLights << "\n";
    shader.set("numLights", numLights); 

    for (int i = 0; i < numLights; ++i) {
        std::string idx = std::to_string(i);
        shader.set("lights[" + idx + "].position", lights[i].position);
        shader.set("lights[" + idx + "].color", lights[i].color);
        shader.set("lights[" + idx + "].intensity", lights[i].intensity);
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

    shader.set("viewPos", viewPos);
}
