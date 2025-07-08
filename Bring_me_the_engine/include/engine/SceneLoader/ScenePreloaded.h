#pragma once

#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include "rendering/Skybox.h"

namespace scenePreloaded {
    void loadScene1(std::vector<std::shared_ptr<Entity>> & entities,
                    std::vector<std::shared_ptr<Entity>> & lightEntities,
                    std::unique_ptr<Skybox> & skybox,
                    LightingManager & lightingManager);

    void loadScene2(std::vector<std::shared_ptr<Entity>> & entities,
                    std::vector<std::shared_ptr<Entity>> & lightEntities,
                    std::unique_ptr<Skybox> & skybox,
                    LightingManager & lightingManager);
}