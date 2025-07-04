#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Globals.h"
#include "camera/Camera.h"
#include "engine/Scene.h"
#include "input/ClavierSouris.h"
#include "math/Vec.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "ui/Menu.h"

#include "../external/imgui/backends/imgui_impl_glfw.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "../external/imgui/imgui.h"

// Cette fonction est un callback pour gérer les événements de clavier crée par GLFW.
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        const char * name = glfwGetKeyName(key, scancode);
        // std::cout << "Touche pressée: " << (name ? name : "Inconnue") << " (code: " << key << ")\n";
        if (name) {
            reactKeyboardPressed(window, name, key);
        } else {
            reactKeyboardPressed(window, name, key);
        }
    }
}

void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
    ClavierSouris::handleMouse(window, xpos, ypos);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Problème à l'initialisation de GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(1600, 800, "Bring Me The Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Problème à la création de la fenêtre GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Problème à l'initialisation de GLAD\n";
        return -1;
    }
    glfwSwapInterval(1); // V-Sync

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Set viewport
    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);

    std::unique_ptr<Scene> gameScene = std::make_unique<Scene>();

    // On à une variable globale pour la scène, on peut y accéder depuis n'importe où dans le code.
    // C'est pratique pour les callbacks et autres fonctions qui n'ont pas accès à la scène
    g_scene = gameScene.get();

    // Création du menu et donc du contexte ImGui
    std::unique_ptr<Menu> menu = std::make_unique<Menu>(window);

    // On initialise le Renderer avec les shaders, c'est lui qui va dessiner la scène.
    std::vector<std::unique_ptr<Shader>> shaders;
    shaders.push_back(std::make_unique<Shader>("../shaders/main_shaders/vertex.vert", "../shaders/main_shaders/vertex.frag"));
    shaders.push_back(std::make_unique<Shader>("../shaders/main_shaders/light_pos.vert", "../shaders/main_shaders/light_pos.frag"));
    shaders.push_back(std::make_unique<Shader>("../shaders/main_shaders/skybox.vert", "../shaders/main_shaders/skybox.frag"));
    shaders.push_back(std::make_unique<Shader>("../shaders/debug/bounding_box.vert", "../shaders/debug/bounding_box.frag"));
    shaders.push_back(std::make_unique<Shader>("../shaders/shadows/dir_shadow.vert", "../shaders/shadows/dir_shadow.frag"));
    shaders.push_back(std::make_unique<Shader>("../shaders/shadows/ponc_shadow.vert", "../shaders/shadows/ponc_shadow.frag", "../shaders/shadows/ponc_shadow.geom"));
    for (size_t i = 0; i < shaders.size(); ++i) {
        if (!shaders[i]) {
            std::cerr << "Erreur : le shader " << i << " est nullptr.\n";
            return -1;
        }
        if (shaders[i]->ID == 0) {
            std::cerr << "Erreur : le shader " << i << " n'a pas été compilé correctement (ID == 0).\n";
            return -1;
        }
    }
    Renderer renderer(shaders[0].get(), shaders[1].get(), shaders[2].get(), shaders[3].get(), shaders[4].get(), shaders[5].get());
    renderer.initShadowMap();

    // boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        menu->beginFrame();

        ClavierSouris::handleContinuousInput(window);
        gameScene->update();

        renderer.renderFrame(*gameScene);

        menu->render();
        menu->endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // On oublie pas de nettoyer les ressources allouées, on le fait à la main ici car si on utilise
    // glfwTerminate() avant, on ne pourra plus désallouer les shaders ensuite.
    gameScene.reset();
    shaders.clear();

    menu.reset();

    glfwTerminate();
    return 0;
}
