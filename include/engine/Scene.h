#pragma once

#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "base/Shader.h"
#include "utils/Cube.h"
#include "engine/Entity.h"
#include <iostream>
#include <memory>
#include <vector>

class Scene {
public:
    Scene(Shader * shader);
    void init();
    void update();

    void initObjects();

private:
    Camera camera;
    Mat4 model;
    Mat4 view;
    Mat4 projection;

    std::vector<std::shared_ptr<Entity>> entities;
    Shader * shader;
};