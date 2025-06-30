#pragma once

#include <GLFW/glfw3.h>

class Menu {
public:
    Menu(GLFWwindow* window);
    ~Menu();

    void beginFrame();
    void render();
    void endFrame();

private:
    GLFWwindow* window;
    bool show = true;
};
