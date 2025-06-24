#include "engine/Clavier.h"
#include "Globals.h"
#include <iostream>

void reactKeyboardPressed(GLFWwindow * window, const char * nameKeyPressed, int keyPressed) {
    // Gestion pour fermer la fenêtre si la touche Échap est pressée
    if (keyPressed == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
}

void Clavier::handleContinuousInput(GLFWwindow * window) {
    if (!g_scene)
        return;

    Camera * cam = g_scene->getCamera();
    if (!cam)
        return;

    if (glfwGetKey(window, 87) == GLFW_PRESS) {
        Vec3 dir = cam->getForward();
        cam->setPosition(cam->getPosition() + dir * sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * sensibility_depl);
    }

    if (glfwGetKey(window, 83) == GLFW_PRESS) {
        Vec3 dir = cam->getBackward();
        cam->setPosition(cam->getPosition() + dir * sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * sensibility_depl);
    }

    if (glfwGetKey(window, 81) == GLFW_PRESS) {
        Vec3 dir = cam->getLeft();
        cam->setPosition(cam->getPosition() + dir * sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * sensibility_depl);
    }

    if (glfwGetKey(window, 68) == GLFW_PRESS) {
        Vec3 dir = cam->getRight();
        cam->setPosition(cam->getPosition() + dir * sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * sensibility_depl);
    }
}
