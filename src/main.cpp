#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "base/Shader.h"
#include "base/Vec.h"
#include "engine/Camera.h"
#include "engine/ClavierSouris.h"
#include "engine/Mesh.h"
#include "engine/Scene.h"
#include "tools/Trigo.h"
#include "utils/Cube.h"
#include "Globals.h"

// Cette fonction est un callback pour gérer les événements de clavier crée par GLFW.
// Concept nouveau et pratique à mes yeux, la manière d'en créer une est donnée en exemple dans le dossier compétences_acquises dans src
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

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
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

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);


    // Set viewport
    glViewport(0, 0, 1600, 800);
    glEnable(GL_DEPTH_TEST);

    // Ici on alloue des unique_ptr pour gérer la mémoire d'une plus jolie manière, et plus sûre.
    std::vector<std::unique_ptr<Shader>> shaders;
    shaders.push_back(std::make_unique<Shader>("../shaders/vertex.vert", "../shaders/vertex.frag"));
    shaders.push_back(std::make_unique<Shader>("../shaders/light_pos.vert", "../shaders/light_pos.frag"));
    std::unique_ptr<Scene> gameScene = std::make_unique<Scene>(shaders[0].get(), shaders[1].get());

    // On à une variable globale pour la scène, on peut y accéder depuis n'importe où dans le code.
    // C'est pratique pour les callbacks et autres fonctions qui n'ont pas accès à la scène
    g_scene = gameScene.get();

    // boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ClavierSouris::handleContinuousInput(window); 
        gameScene->update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // On oublie pas de nettoyer les ressources allouées, on le fait à la main ici car si on utilise
    // glfwTerminate() avant, on ne pourra plus désallouer les shaders ensuite.
    gameScene.reset();
    shaders.clear();

    glfwTerminate();
    return 0;
}
