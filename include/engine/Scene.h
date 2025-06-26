#pragma once

#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "base/Shader.h"
#include "utils/Cube.h"
#include "utils/Floor.h"
#include "engine/Entity.h"
#include "engine/LightingManager.h"
#include <iostream>
#include <memory>
#include <vector>

class Scene {
public:
    Scene(Shader * shader, Shader * lightShader);
    void init();
    void update();

    void initObjects();

    inline Camera * getCamera() { return &camera; }
    inline Mat4 & getView() { return view; }

private:
    Camera camera;
    //Ici chaque objet de la scène aura sa propre matrice de transformation donc pas de model global
    Mat4 view;
    Mat4 projection;

    std::vector<std::shared_ptr<Entity>> entities;

    LightingManager lightingManager;

    std::vector<std::shared_ptr<Entity>> lightEntities;
    
    Shader * shader;
    // Ce shader va me permettre de dessiner les lumières, on le fait à part pour éviter de mélanger les deux
    // ainsi que permettre de ne pas faire de lumière sur les lumières elles-mêmes
    Shader * lightShader;
    Color lightColor = Color::red();
};