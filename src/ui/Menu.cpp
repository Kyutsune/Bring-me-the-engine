#include "ui/Menu.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

Menu::Menu(GLFWwindow * window) : window(window), scene(g_scene) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark(); // ou .Classic(), .Light()

    ImGuiStyle & style = ImGui::GetStyle();
    style.ScaleAllSizes(1.5f);

    ImGuiIO & io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f; 
    // Permet de changer le nom du fichier de configuration 
    io.IniFilename = "menu.ini";

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

Menu::~Menu() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Menu::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Menu::render() {
    if (!show)
        return;

    // On force la taille de la fenêtre à la taille minimale nécessaire pour afficher le contenu
    ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::Begin("Mon menu", &show);
    drawFogSection();
    drawQuitButton();

    ImGui::End();
}


void Menu::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::drawFogSection() {
    if (ImGui::CollapsingHeader("Brouillard", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Contrôle du brouillard");

        static const char * items[] = {"Aucun", "Linéaire", "Exponentiel", "Exponentiel²"};
        static int currentType = scene->getFogType();

        if (ImGui::Combo("Type de Fog", &currentType, items, IM_ARRAYSIZE(items))) {
            scene->setFogType(currentType);
        }
    }
}

void Menu::drawQuitButton() {
    if (ImGui::Button("Quitter")) {
        glfwSetWindowShouldClose(window, true);
    }
}