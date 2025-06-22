#include "engine/Shader.h"
#include "engine/Mesh.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>


int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(800, 600, "Bring Me The Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 800, 600);

    // Ici on affiche un triangle avec la classe Shader
    Shader shader("../shaders/vertex.vert", "../shaders/vertex.frag");


    // Ici affichage d'un triangle avec la classe Mesh
    std::vector<Vertex> vertices = {
        // positions           normals         colors          texCoords
        {{-0.5f, -0.5f,  0.5f}, {0, 0, 1}, {1, 0, 0}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0, 0, 1}, {0, 1, 0}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0, 0, 1}, {0, 0, 1}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0, 0, 1}, {1, 0, 1}, {0.0f, 1.0f}},
        

        {{-0.5f, -0.5f, -0.5f}, {0, 0, -1}, {1, 0, 1}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0, 0, -1}, {0, 1, 1}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0, 0, -1}, {1, 1, 1}, {0.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0, 0, -1}, {0, 0, 1}, {1.0f, 1.0f}},
    };
    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Back face
        5, 4, 7, 7, 6, 5,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        4, 5, 1, 1, 0, 4
    };
    Mesh mesh(vertices, indices);

    // boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
