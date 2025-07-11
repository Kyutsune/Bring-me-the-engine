#pragma once

#include <memory>
#include <vector>

class GLFWwindow;
#include "rendering/Shader.h"
#include "ui/Menu.h"

class Application {
public:
    int run();

private:
    bool initGLFW();
    bool initWindow();
    bool initGlad();
    void setupCallbacks();
    void setupScene();
    void setupShaders();
    void cleanup();

    GLFWwindow* m_window = nullptr;
    std::unique_ptr<Menu> m_menu;
    std::vector<std::unique_ptr<Shader>> m_shaders;
};
