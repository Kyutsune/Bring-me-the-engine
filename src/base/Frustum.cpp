#include "base/Frustum.h"
#include <iostream>

void Frustum::update(const Mat4 & m) {
    // Left plane
    planes[0].normal.x = m.data[3] + m.data[0];
    planes[0].normal.y = m.data[7] + m.data[4];
    planes[0].normal.z = m.data[11] + m.data[8];
    planes[0].distance = m.data[15] + m.data[12];

    // Right plane
    planes[1].normal.x = m.data[3] - m.data[0];
    planes[1].normal.y = m.data[7] - m.data[4];
    planes[1].normal.z = m.data[11] - m.data[8];
    planes[1].distance = m.data[15] - m.data[12];

    // Bottom plane
    planes[2].normal.x = m.data[3] + m.data[1];
    planes[2].normal.y = m.data[7] + m.data[5];
    planes[2].normal.z = m.data[11] + m.data[9];
    planes[2].distance = m.data[15] + m.data[13];

    // Top plane
    planes[3].normal.x = m.data[3] - m.data[1];
    planes[3].normal.y = m.data[7] - m.data[5];
    planes[3].normal.z = m.data[11] - m.data[9];
    planes[3].distance = m.data[15] - m.data[13];

    // Near plane
    planes[4].normal.x = m.data[3] + m.data[2];
    planes[4].normal.y = m.data[7] + m.data[6];
    planes[4].normal.z = m.data[11] + m.data[10];
    planes[4].distance = m.data[15] + m.data[14];

    // Far plane
    planes[5].normal.x = m.data[3] - m.data[2];
    planes[5].normal.y = m.data[7] - m.data[6];
    planes[5].normal.z = m.data[11] - m.data[10];
    planes[5].distance = m.data[15] - m.data[14];

    // Et on les normalise
    for (int i = 0; i < 6; i++) {
        float length = planes[i].normal.length();
        planes[i].normal = planes[i].normal / length;
        planes[i].distance /= length;

        // if (planes[i].distance < 0) {
        //     planes[i].normal = -planes[i].normal;
        //     planes[i].distance = -planes[i].distance;
        // }
    }
}

//FIXME: Corriger le bug du frustum qui ne détecte pas parfaitement les entités sur leur côté droit 
//(en regardant côté lumière au début de l'appli)
//Le problème NE SEMBLE pas venir ni du frustum car en le bougeant a travers la scène on se rend compte
//que c'est le côté de la boite qui pose soucis pas la cam
//Mais en affichant le AABB de la boîté ça à l'air bien construit visuellement donc???
bool Frustum::isBoxInFrustum(const AABB & box) const {
    for (int i = 0; i < 6; i++) {
        const Plane & plane = planes[i];

        Vec3 p;
        float minX = std::min(box.min.x, box.max.x);
        float maxX = std::max(box.min.x, box.max.x);
        float minY = std::min(box.min.y, box.max.y);
        float maxY = std::max(box.min.y, box.max.y);
        float minZ = std::min(box.min.z, box.max.z);
        float maxZ = std::max(box.min.z, box.max.z);

        p.x = (plane.normal.x >= 0) ? maxX : minX;
        p.y = (plane.normal.y >= 0) ? maxY : minY;
        p.z = (plane.normal.z >= 0) ? maxZ : minZ;

        if (plane.distanceToPoint(p) < 0) {
            return false; // Box complètement hors du frustum
        }
    }
    return true; // Partiellement ou complètement dedans
}
