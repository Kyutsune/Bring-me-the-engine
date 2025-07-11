#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Callbacks {
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
}