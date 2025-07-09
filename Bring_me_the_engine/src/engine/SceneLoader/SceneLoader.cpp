#include "engine/SceneLoader/SceneLoader.h"
#include "engine/SceneLoader/ScenePreloaded.h"


namespace SceneLoader {

    void loadScene(const int & sceneIndex,
                   std::vector<std::shared_ptr<Entity>> & entities,
                   std::vector<std::shared_ptr<Entity>> & lightEntities,
                   std::unique_ptr<Skybox> & skybox,
                   LightingManager & lightingManager) {

        switch (sceneIndex) {
        case 1:
            scenePreloaded::loadScene1(entities, lightEntities, skybox, lightingManager);
            break;
        case 2:
            scenePreloaded::loadScene2(entities, lightEntities, skybox, lightingManager);
            break;
        default:
            std::cerr << "SceneLoader: Scene index " << sceneIndex << " not implemented.\n";
            break;
        }
    }
}
