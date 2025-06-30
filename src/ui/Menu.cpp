#include "ui/Menu.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

Menu::Menu(GLFWwindow * window) : window(window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark(); // ou .Classic(), .Light()

    ImGuiStyle & style = ImGui::GetStyle();
    style.ScaleAllSizes(1.5f); // Augmente la taille générale (boutons, padding, etc.)

    ImGuiIO & io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f; // Augmente la taille de la police à l'écran
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

    ImGui::Begin("Mon menu", &show);
    ImGui::Text("Hello from ImGui!");
    if (ImGui::Button("Quitter"))
        glfwSetWindowShouldClose(window, true);
    ImGui::End();
}

void Menu::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
