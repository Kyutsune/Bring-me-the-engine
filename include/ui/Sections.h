#pragma once

#include "Globals.h"
#include "engine/Scene.h"

namespace Sections {
    void textureSection(Scene * scene);
    void directionnalLightSection(Scene * scene);
    void sensitivitySection();
    void fogSection(Scene * scene);
    void quitButton(GLFWwindow * window);
}