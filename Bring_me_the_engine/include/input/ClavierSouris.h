#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Globals.h"
#include "math/intersect/Ray.h"

/**
 * @brief Fonction pour réagir à une touche clavier pressée.
 * 
 * Cette fonction gère la logique liée à la détection des touches pressées,
 * séparée de la logique de déplacement.
 * Elle permet aussi de gérer les touches pressées en continu.
 * 
 * @param window Fenêtre GLFW ciblée.
 * @param nameKeyPressed Nom de la touche pressée (ex: "w", "a").
 * @param keyPressed Code de la touche GLFW.
 */
void reactKeyboardPressed(GLFWwindow * window, const char * nameKeyPressed, int keyPressed);

namespace ClavierSouris {

    /**
     * @brief Met à jour les états clavier/souris chaque frame.
     * 
     * @param window Fenêtre GLFW ciblée.
     */
    void update(GLFWwindow * window);

    /**
     * @brief Gère le clic gauche de la souris.
     * 
     * @param window Fenêtre GLFW ciblée.
     */
    void handleMouseLeftClick(GLFWwindow * window);

    /**
     * @brief Gère le déplacement de la souris.
     * 
     * @param window Fenêtre GLFW ciblée.
     * @param xpos Position X de la souris.
     * @param ypos Position Y de la souris.
     */
    void handleMouseMovement(GLFWwindow * window, double xpos, double ypos);

    /**
     * @brief Gère les entrées clavier continues (touches maintenues).
     * 
     * @param window Fenêtre GLFW ciblée.
     */
    void handleContinuousInput(GLFWwindow * window);

    /**
     * @brief Gère un clic gauche interne.
     * 
     * @note Cette fonction est interne, mais exposée publiquement au cas où.
     *       Sinon, il serait possible de la rendre `static` dans le .cpp.
     * 
     * @param x Position X du clic.
     * @param y Position Y du clic.
     */
    void gestionClicGauche(double x, double y);
}
