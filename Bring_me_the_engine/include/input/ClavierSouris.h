#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Globals.h"
#include "math/intersect/Ray.h"

// Ici on a une fonction à part pour réagir aux touches du clavier et une autre pour le déplacement.
// Cela permet de séparer la logique de gestion des entrées clavier et la logique de déplacement de la caméra d'une part.
// Mais aussi de gérer le fait que la touche puisse être pressée en continu.
void reactKeyboardPressed(GLFWwindow * window, const char * nameKeyPressed, int keyPressed);

namespace ClavierSouris {
    void update(GLFWwindow * window);

    void handleMouseLeftClick(GLFWwindow * window);

    void handleMouseMovement(GLFWwindow * window, double xpos, double ypos);
    void handleContinuousInput(GLFWwindow * window);

    // Cette fonction est interne, mais on la laisse publique si besoin,
    // sinon la déplacer dans le .cpp et la rendre `static` là-bas
    void gestionClicGauche(double x, double y);
}