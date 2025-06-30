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

    // Déclaration de chaque section du menu
    drawFogSection();
    drawQuitButton();

    ImGui::End();
}

void Menu::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::drawFogSection() {
    if (ImGui::CollapsingHeader("Fog")) {
        ImGui::SeparatorText("Type de fog actif");
        // Section sur le Type de Fog
        static const char * items[] = {"Aucun", "Linéaire", "Exponentiel", "Exponentiel²"};
        static int currentType = scene->getFogType();

        if (ImGui::Combo("Type de Fog", &currentType, items, IM_ARRAYSIZE(items))) {
            scene->setFogType(currentType);
        }

        ImGui::SeparatorText("Valeurs du Fog");

        ImGui::SliderFloat("Début", scene->getFogStart(), 0.0f, *scene->getFogEnd(), "%.1f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::SliderFloat("Fin", scene->getFogEnd(), *scene->getFogStart(), 100.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
        float fogDensity = *scene->getFogDensity();
        if (ImGui::SliderFloat("Densité##slider", &fogDensity, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp) ||
            ImGui::InputFloat("Densité##input", &fogDensity, 0.01f, 0.1f, "%.3f")) {
            scene->setFogDensity(fogDensity);
        }

        ImGui::SeparatorText("Couleur du Fog");
        Color & fogColor = scene->getFogColor();
        float colorTmp[3] = {
            fogColor.r / 255.0f,
            fogColor.g / 255.0f,
            fogColor.b / 255.0f};

        if (ImGui::ColorEdit3("Couleur", colorTmp)) {
            fogColor.r = colorTmp[0] * 255.0f;
            fogColor.g = colorTmp[1] * 255.0f;
            fogColor.b = colorTmp[2] * 255.0f;
        }
    }
}

void Menu::drawQuitButton() {
    if (ImGui::Button("Quitter")) {
        glfwSetWindowShouldClose(window, true);
    }
}