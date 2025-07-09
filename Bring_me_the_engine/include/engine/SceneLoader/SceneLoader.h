#pragma once
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "rendering/Skybox.h"
#include <memory>
#include <string>
#include <vector>

namespace SceneLoader {
    void loadScene(const int & sceneIndex,
                   std::vector<std::shared_ptr<Entity>> & m_entities,
                   std::vector<std::shared_ptr<Entity>> & m_lightEntities,
                   std::unique_ptr<Skybox> & m_skybox,
                   LightingManager & lightingManager);

    // AVENIR: Avoir un système de gestion de scène ou l'on importe les scène de fichiers de configurations
    //  Plutôt qu'en dur dans le code
    void loadScene(const std::string & sceneName);

}