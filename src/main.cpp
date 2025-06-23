#include "base/Vec.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "engine/Scene.h"
#include "engine/Shader.h"
#include "tools/Trigo.h"
#include "utils/Cube.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

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

    // Set viewport
    glViewport(0, 0, 1600, 800);
    glEnable(GL_DEPTH_TEST);

    Shader shader("../shaders/vertex.vert", "../shaders/vertex.frag");
    Scene gameScene(&shader);


    // boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gameScene.update();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
