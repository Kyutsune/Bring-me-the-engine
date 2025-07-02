#pragma once
#include "engine/Scene.h"

// Pointeur global vers la scène actuelle, utilisé pour accéder à la caméra et aux entités
extern Scene * g_scene;
//Sensibilité de déplacement de la caméra via le clavier
extern float sensibility_depl;
//Sensibilité de rotation de la caméra via la souris
extern float sensibility_rot;

extern int windowWidth;
extern int windowHeight;
