#include "Globals.h"
#include "math/intersect/Ray.h"
#include "engine/Scene.h"

Ray Ray::generateRayFromScreen(double mouseX, double mouseY) {
    const Scene & scene = getScene();
    const Camera & cam = scene.getCamera();

    // Étape 1 : Normalisation écran -> NDC (-1 à 1)
    float x_ndc = (2.0f * static_cast<float>(mouseX)) / g_windowWidth - 1.0f;
    float y_ndc = 1.0f - (2.0f * static_cast<float>(mouseY)) / g_windowHeight; // OpenGL : y inversé

    // Étape 2 : clip space
    Vec4 ray_clip(x_ndc, y_ndc, -1.0f, 1.0f);

    // Étape 3 : caméra space
    Vec4 ray_eye = cam.getProjectionMatrix().inverse() * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f; // Direction, pas un point

    // Étape 4 : monde
    Vec4 ray_world4 = cam.getViewMatrix().inverse() * ray_eye;
    Vec3 ray_world(ray_world4.x, ray_world4.y, ray_world4.z);
    ray_world = ray_world.normalized();

    Vec3 origin = cam.getPosition();
    return Ray(origin, ray_world);
}
