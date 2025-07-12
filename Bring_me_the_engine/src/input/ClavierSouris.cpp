#include "input/ClavierSouris.h"
#include "Globals.h"
#include "math/intersect/IntersectInfo.h"
#include "math/intersect/IntersectUtils.h"
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

    // FIXME: J'utilise du hardcode pour les entiers de touches car le système de GLFW est sur le qwerty et pas azerty.
    //  Il pourrait y avoir d'autres moyens plus propre pour gérer cela?
    //  Voici la solution de Hazel par exemple :
    //  https://github.com/TheCherno/Hazel/blob/1feb70572fa87fa1c4ba784a2cfeada5b4a500db/Hazel/src/Hazel/Core/KeyCodes.h
    if (glfwGetKey(window, 87) == GLFW_PRESS) { // z
        Vec3 dir = cam->getForward();
        cam->setPosition(cam->getPosition() + dir * g_sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * g_sensibility_depl);
    }

    if (glfwGetKey(window, 83) == GLFW_PRESS) { // s
        Vec3 dir = cam->getBackward();
        cam->setPosition(cam->getPosition() + dir * g_sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * g_sensibility_depl);
    }

    if (glfwGetKey(window, 81) == GLFW_PRESS) { // a
        Vec3 dir = cam->getLeft();
        cam->setPosition(cam->getPosition() + dir * g_sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * g_sensibility_depl);
    }

    if (glfwGetKey(window, 68) == GLFW_PRESS) { // d
        Vec3 dir = cam->getRight();
        cam->setPosition(cam->getPosition() + dir * g_sensibility_depl);
        cam->setTarget(cam->getTarget() + dir * g_sensibility_depl);
    }
    if (glfwGetKey(window, 67) == GLFW_PRESS) { // c
        std::cout << "Position de la caméra: " << cam->getPosition() << std::endl;
    }
}

void ClavierSouris::handleMouse(GLFWwindow * window, double xpos, double ypos) {
    if (!g_scene)
        return;

    Camera * cam = g_scene->getCamera();
    if (!cam)
        return;

    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
        return;
    }

    double dx = xpos - m_lastX;
    double dy = ypos - m_lastY;

    // Déplacement latéral + vertical avec Ctrl
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {

        cam->setPosition(cam->getPosition() - cam->getRight() * static_cast<float>(dx) * g_sensibility_depl);
        cam->setTarget(cam->getTarget() - cam->getRight() * static_cast<float>(dx) * g_sensibility_depl);

        cam->setPosition(cam->getPosition() + Vec3(0, 1, 0) * static_cast<float>(dy) * g_sensibility_depl);
        cam->setTarget(cam->getTarget() + Vec3(0, 1, 0) * static_cast<float>(dy) * g_sensibility_depl);
    }

    // Rotation caméra avec clic droit
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        Vec3 dir = cam->getDirection();
        Vec3 right = cam->getRight();
        Vec3 up = Vec3(0, 1, 0);

        float yaw = static_cast<float>(dx) * g_sensibility_rot;
        float pitch = static_cast<float>(dy) * g_sensibility_rot;

        Mat4 yawRotation;
        yawRotation = yawRotation.rotate(up, yaw);

        Mat4 pitchRotation;
        pitchRotation = pitchRotation.rotate(right, pitch);

        Vec3 rotatedDir = pitchRotation * (yawRotation * dir);

        cam->setTarget(cam->getPosition() + rotatedDir.normalized());
    }

    // Gestion du clic gauche
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        ClavierSouris::gestionClicGauche(xpos, ypos);
    }

    m_lastX = xpos;
    m_lastY = ypos;
}

Ray ClavierSouris::generateRayFromScreen(double mouseX, double mouseY) {
    const Scene & scene = getScene();
    const Camera & cam = scene.getCamera();

    // Étape 1 : Normalisation écran -> NDC (-1 à 1)
    float x_ndc = (2.0f * static_cast<float>(mouseX)) / g_windowWidth - 1.0f;
    float y_ndc = 1.0f - (2.0f * static_cast<float>(mouseY)) / g_windowHeight; // OpenGL : y inversé

    // Étape 2 : clip space
    Vec4 ray_clip(x_ndc, y_ndc, -1.0f, 1.0f);

    // Étape 3 : caméra space
    Vec4 ray_eye = cam.getProjectionMatrix().inverse() * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f; // Direction, pas un point

    // Étape 4 : monde
    Vec4 ray_world4 = cam.getViewMatrix().inverse() * ray_eye;
    Vec3 ray_world(ray_world4.x, ray_world4.y, ray_world4.z);
    ray_world = ray_world.normalized();

    Vec3 origin = cam.getPosition();
    return Ray(origin, ray_world);
}

void ClavierSouris::gestionClicGauche(double x, double y) {
    Ray ray = generateRayFromScreen(x, y);
    const Scene & scene = getScene();
    const std::vector<std::shared_ptr<Entity>> & entities = scene.getEntities();
    IntersectionInfo retour_info;

    for (const auto & entity : entities) {
        if (IntersectUtils::intersectEntity(ray, *entity, retour_info)) {
            std::cout << "Intersection avec l'entité: " << entity->getName() << std::endl;
            std::cout << "Position d'intersection: " << retour_info.position << std::endl;
            std::cout << "Normale à l'intersection: " << retour_info.normal << std::endl;
            return; // On arrête après la première intersection trouvée, par soucis d'optimisation 
        }
    }
}