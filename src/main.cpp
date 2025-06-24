#include "base/Shader.h"
#include "base/Vec.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "engine/Scene.h"
#include "tools/Trigo.h"
#include "utils/Cube.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        const char * name = glfwGetKeyName(key, scancode);
        if (name) {
            std::cout << "Appui sur: " << name << std::endl;
        } else {
            std::cout << "Appui sur une touche dont le code est: " << key << std::endl;
        }
    }
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

    // Set viewport
    glViewport(0, 0, 1600, 800);
    glEnable(GL_DEPTH_TEST);

    // Ici on alloue des unique_ptr pour gérer la mémoire d'une plus jolie manière, et plus sûre.
    std::unique_ptr<Shader> shader = std::make_unique<Shader>("../shaders/vertex.vert", "../shaders/vertex.frag");
    std::unique_ptr<Scene> gameScene = std::make_unique<Scene>(shader.get());

    // boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gameScene->update();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gameScene.reset();
    shader.reset();

    glfwTerminate();
    return 0;
}
