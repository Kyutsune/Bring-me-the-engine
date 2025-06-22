#include "base/Vec.h"
#include "engine/Mesh.h"
#include "engine/Shader.h"
#include "tools/Trigo.h"
#include "utils/Cube.h"
#include "engine/Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void updateCameraUniforms(Shader & shader, const Mat4 & model, const Mat4 & view, const Mat4 & projection) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(1600, 800, "Bring Me The Engine", nullptr, nullptr);
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

    // Définition des différentes matrices de transformation
    Mat4 model = Mat4::identity();

    Camera camera(
        Vec3(2, 1, 3),    // position à l'initialisation
        Vec3(0, 0, 0),    // le point ciblé
        Vec3(0, 1, 0),    // up
        45.0f,            // FOV
        1600.0f / 800.0f, // aspect ratio
        0.1f, 100.0f);

    Mat4 view = camera.getViewMatrix();
    Mat4 projection = camera.getProjectionMatrix();

    // Set viewport
    glViewport(0, 0, 1600, 800);
    glEnable(GL_DEPTH_TEST);

    Shader shader("../shaders/vertex.vert", "../shaders/vertex.frag");

    Mesh cube = createCube();

    // boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float angle = glfwGetTime(); 
        Mat4 rotation = Mat4::rotateY(angle);
        model = rotation;

        // On passe au shader les matrices de transformation
        updateCameraUniforms(shader, model, view, projection);
        cube.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
