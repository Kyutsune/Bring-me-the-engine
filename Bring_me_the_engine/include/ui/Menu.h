#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/Scene.h"
#include "ui/Sections.h"
#include "Globals.h"


class Menu {
public:
    // Fonctions de base afin d'initialiser, configurer et rendre le menu à l'écran
    Menu(GLFWwindow * window);
    ~Menu();

    void beginFrame();
    void render();
    void endFrame();
    void setupMenuDisplay();

protected:
    GLFWwindow * window;
    Scene * scene;

private:
    bool m_show = true;

    int m_taille_minimale_x;
    int m_taille_minimale_y;
    int m_taille_maximale_x;
    int m_taille_maximale_y;
};
