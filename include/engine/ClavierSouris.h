#pragma once

#include "Globals.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Ici on a une fonction à part pour réagir aux touches du clavier et une autre pour le déplacement.
// Cela permet de séparer la logique de gestion des entrées clavier et la logique de déplacement de la caméra d'une part.
// Mais aussi de gérer le fait que la touche puisse être pressée en continu.
void reactKeyboardPressed(GLFWwindow * window, const char * nameKeyPressed, int keyPressed);

class ClavierSouris {
public:
    static void handleMouse(GLFWwindow * window, double xpos, double ypos);
    static void handleContinuousInput(GLFWwindow * window);

private:
    inline static double lastX = 0.0, lastY = 0.0;
    inline static bool firstMouse = true;
};