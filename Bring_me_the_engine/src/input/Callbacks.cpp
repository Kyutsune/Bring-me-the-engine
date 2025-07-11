#include "input/Callbacks.h"
#include "input/ClavierSouris.h"
#include "Globals.h"

namespace Callbacks {

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            const char* name = glfwGetKeyName(key, scancode);
            reactKeyboardPressed(window, name, key);
        }
    }

    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        ClavierSouris::handleMouse(window, xpos, ypos);
    }

}