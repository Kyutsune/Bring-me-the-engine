#pragma once

#include "Globals.h"
#include "engine/Scene.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Menu {
public:
    // Fonctions de base afin d'initialiser, configurer et rendre le menu à l'écran
    Menu(GLFWwindow * window);
    ~Menu();

    void beginFrame();
    void render();
    void endFrame();
    void setupMenuDisplay();

    // Chaque section à mettre dans le menu
    void drawFogSection();
    void drawQuitButton();

private:
    GLFWwindow * window;
    bool show = true;
    Scene * scene;

    int taille_minimale_x;
    int taille_minimale_y;
    int taille_maximale_x;
    int taille_maximale_y;
};
