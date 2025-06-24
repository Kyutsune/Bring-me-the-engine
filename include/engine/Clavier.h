#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Globals.h"


// Ici on a une fonction à part pour réagir aux touches du clavier et une autre pour le déplacement.
// Cela permet de séparer la logique de gestion des entrées clavier et la logique de déplacement de la caméra d'une part.
// Mais aussi de gérer le fait que la touche puisse être pressée en continu.
void reactKeyboardPressed(GLFWwindow* window, const char * nameKeyPressed, int keyPressed);

class Clavier {
public:
    static void handleContinuousInput(GLFWwindow* window);
};