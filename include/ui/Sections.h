#pragma once

#include "Globals.h"
#include "engine/Scene.h"

namespace UI {
    void drawTextureSection(Scene * scene);
    void drawDirectionnalLightSection(Scene * scene);
    void drawSensitivitySection();
    void drawFogSection(Scene * scene);
    void drawQuitButton(GLFWwindow * window);
}