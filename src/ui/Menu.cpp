#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "ui/Menu.h"
#include "ui/Sections.h"

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

    ImGui::LoadIniSettingsFromDisk(io.IniFilename);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    taille_minimale_x = 300;
    taille_minimale_y = 100;
    taille_maximale_x = 800;
    taille_maximale_y = 400;
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

void Menu::setupMenuDisplay() {
    // On force la taille de la fenêtre à la taille minimale nécessaire pour afficher le contenu
    ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Always);
    // Et on fixe des contraintes maximales et minimales pour la taille de ce menu
    ImGui::SetNextWindowSizeConstraints(
        ImVec2(taille_minimale_x, taille_minimale_y),
        ImVec2(taille_maximale_x, taille_maximale_y));
}

void Menu::render() {
    if (!show)
        return;

    setupMenuDisplay();
    ImGui::Begin("Bring me the menu", &show);

    UI::drawSensitivitySection();
    UI::drawFogSection(scene);
    UI::drawQuitButton(window);

    ImGui::End();
}

void Menu::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
