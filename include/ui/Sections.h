#pragma once

#include "engine/Scene.h" 
#include "Globals.h"

namespace UI {

void drawTextureSection(Scene * scene);
void drawSensitivitySection();
void drawFogSection(Scene* scene);
void drawQuitButton(GLFWwindow* window);

}