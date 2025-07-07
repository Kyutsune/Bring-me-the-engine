#pragma once
#include "engine/Scene.h"

// Pointeur global vers la scène actuelle, utilisé pour accéder à la caméra et aux entités
extern Scene * g_scene;
// Sensibilité de déplacement de la caméra via le clavier
extern float g_sensibility_depl;
// Sensibilité de rotation de la caméra via la souris
extern float g_sensibility_rot;

extern int g_windowWidth;
extern int g_windowHeight;

inline constexpr size_t MAX_DIR_LIGHTS = 1;
inline constexpr size_t MAX_PONC_LIGHTS = 8;
inline constexpr size_t MAX_LIGHTS = MAX_DIR_LIGHTS + MAX_PONC_LIGHTS;
