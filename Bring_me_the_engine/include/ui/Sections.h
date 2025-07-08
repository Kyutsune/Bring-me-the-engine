#pragma once

#include "Globals.h"
#include "engine/Scene.h"

namespace Sections {
    void textureSection(Scene * scene);
    void lightSection(Scene * scene);
    void directionnalLightSection(Scene * scene);
    void ponctualLightSection(Scene * scene);
    void sensitivitySection();
    void fogSection(Scene * scene);
    // Le booléen sert à savoir si on à changer de scène ou non
    bool SceneSection(Scene * scene);
    void quitButton(GLFWwindow * window);
}