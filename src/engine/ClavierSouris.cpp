#include "engine/ClavierSouris.h"
#include "Globals.h"
#include <iostream>

void reactKeyboardPressed(GLFWwindow * window, const char * nameKeyPressed, int keyPressed) {
    // Gestion pour fermer la fenêtre si la touche Échap est pressée
    if (keyPressed == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
}

void ClavierSouris::handleContinuousInput(GLFWwindow * window) {
    if (!g_scene)
        return;

    Camera * cam = g_scene->getCamera();
    if (!cam)
        return;

    //FIXME: J'utilise du hardcode pour les entiers de touches car le système de GLFW est sur le qwerty et pas azerty.
    // Il pourrait y avoir d'autres moyens plus propre pour gérer cela?
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
    if(glfwGetKey(window, 67) == GLFW_PRESS) {
        std::cout<< "Position de la caméra: " << cam->getPosition() << std::endl;
    }


}

void ClavierSouris::handleMouse(GLFWwindow * window, double xpos, double ypos) {
    if (!g_scene)
        return;

    Camera * cam = g_scene->getCamera();
    if (!cam)
        return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    double dx = xpos - lastX;
    double dy = ypos - lastY;

    // Déplacement latéral + vertical avec Ctrl
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {

        cam->setPosition(cam->getPosition() - cam->getRight() * static_cast<float>(dx) * sensibility_depl);
        cam->setTarget(cam->getTarget() - cam->getRight() * static_cast<float>(dx) * sensibility_depl);

        cam->setPosition(cam->getPosition() + Vec3(0, 1, 0) * static_cast<float>(dy) * sensibility_depl);
        cam->setTarget(cam->getTarget() + Vec3(0, 1, 0) * static_cast<float>(dy) * sensibility_depl);
    }

    // Rotation caméra avec clic droit
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        Vec3 dir = cam->getDirection();
        Vec3 right = cam->getRight();
        Vec3 up = Vec3(0, 1, 0); 

        float yaw = static_cast<float>(dx) * sensibility_rot;
        float pitch = static_cast<float>(dy) * sensibility_rot;

        Mat4 yawRotation;
        yawRotation = yawRotation.rotate(up, yaw); 

        Mat4 pitchRotation;
        pitchRotation = pitchRotation.rotate(right, pitch); 

        Vec3 rotatedDir = pitchRotation * (yawRotation * dir);

        cam->setTarget(cam->getPosition() + rotatedDir.normalized());
    }

    lastX = xpos;
    lastY = ypos;
}
