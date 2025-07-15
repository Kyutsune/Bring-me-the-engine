#include "input/ClavierSouris.h"
#include "Globals.h"
#include "math/intersect/IntersectInfo.h"
#include "math/intersect/IntersectUtils.h"
#include "imgui.h"
#include <iostream>

void reactKeyboardPressed(GLFWwindow * window, const char * nameKeyPressed, int keyPressed) {
    // Gestion pour fermer la fenêtre si la touche Échap est pressée
    if (keyPressed == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
}

namespace ClavierSouris {

    // Variables statiques internes au namespace
    static double m_lastX = 0.0;
    static double m_lastY = 0.0;
    static bool m_firstMouse = true;

    void update(GLFWwindow * window) {
        handleContinuousInput(window);
        handleMouseLeftClick(window);
    }

    void handleContinuousInput(GLFWwindow * window) {
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

    void handleMouseLeftClick(GLFWwindow * window) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (ImGui::GetIO().WantCaptureMouse)
            return;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            gestionClicGauche(xpos, ypos);
        }
    }

    void handleMouseMovement(GLFWwindow * window, double xpos, double ypos) {
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

        m_lastX = xpos;
        m_lastY = ypos;
    }

    // FIXME: Pas vraiment un fixme mais cette fonction devrait vraiment être gérée par ClavierSouris??
    // Certes c'est le clic qui déclenche cela mais le fait que ce soit un teste de collision entre rayon
    // et entité n'impliquerait pas que cela doive aller dans la struct Ray voir Entity?
    void gestionClicGauche(double x, double y) {
        Ray ray = Ray::generateRayFromScreen(x, y);
        const Scene & scene = getScene();
        const std::vector<std::shared_ptr<Entity>> & entities = scene.getEntities();
        IntersectionInfo retour_info;

        /// Partie servant à sélectionner l'entité sur laquelle on clique, et d'ouvir son menu
        for (const auto & entity : entities) {
            if (entity->isVisible() && IntersectUtils::intersectEntity(ray, *entity, retour_info)) {
                // std::cout << "Intersection avec l'entité: " << entity->getName() << std::endl;
                // std::cout << "Position d'intersection: " << retour_info.position << std::endl;
                // std::cout << "Normale à l'intersection: " << retour_info.normal << std::endl;

                g_entityExpanded.clear(); // Pour n'ouvrir qu'une seule section et fermer les autres
                g_entityExpanded[entity->getName()] = true;
                g_forceOpenObjectHeader = true; // Force l'ouverture de la section des objets dans le menu

                return; // Stop à la première intersection trouvée
            }
        }
        /// Si aucune entité séléctionnée à l'endroit du clic, on va créer une entité selon le choix dans le menu
        


    }
}