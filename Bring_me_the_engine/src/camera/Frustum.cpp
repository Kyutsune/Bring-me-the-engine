#include "camera/Frustum.h"
#include <array>
#include <math/Trigo.h>

void Frustum::update(const Mat4 & m) {
    // Left plane
    m_planes[0].m_normal.x = m.data[3] + m.data[0];
    m_planes[0].m_normal.y = m.data[7] + m.data[4];
    m_planes[0].m_normal.z = m.data[11] + m.data[8];
    m_planes[0].m_distance = m.data[15] + m.data[12];

    // Right plane
    m_planes[1].m_normal.x = m.data[3] - m.data[0];
    m_planes[1].m_normal.y = m.data[7] - m.data[4];
    m_planes[1].m_normal.z = m.data[11] - m.data[8];
    m_planes[1].m_distance = m.data[15] - m.data[12];

    // Bottom plane
    m_planes[2].m_normal.x = m.data[3] + m.data[1];
    m_planes[2].m_normal.y = m.data[7] + m.data[5];
    m_planes[2].m_normal.z = m.data[11] + m.data[9];
    m_planes[2].m_distance = m.data[15] + m.data[13];

    // Top plane
    m_planes[3].m_normal.x = m.data[3] - m.data[1];
    m_planes[3].m_normal.y = m.data[7] - m.data[5];
    m_planes[3].m_normal.z = m.data[11] - m.data[9];
    m_planes[3].m_distance = m.data[15] - m.data[13];

    // Near plane
    m_planes[4].m_normal.x = m.data[3] + m.data[2];
    m_planes[4].m_normal.y = m.data[7] + m.data[6];
    m_planes[4].m_normal.z = m.data[11] + m.data[10];
    m_planes[4].m_distance = m.data[15] + m.data[14];

    // Far plane
    m_planes[5].m_normal.x = m.data[3] - m.data[2];
    m_planes[5].m_normal.y = m.data[7] - m.data[6];
    m_planes[5].m_normal.z = m.data[11] - m.data[10];
    m_planes[5].m_distance = m.data[15] - m.data[14];

    // Et on les normalise
    for (int i = 0; i < 6; i++) {
        float length = m_planes[i].m_normal.length();
        m_planes[i].m_normal = m_planes[i].m_normal / length;
        m_planes[i].m_distance /= length;

        // if (planes[i].distance < 0) {
        //     planes[i].normal = -planes[i].normal;
        //     planes[i].distance = -planes[i].distance;
        // }
    }
}

Frustum Frustum::updateFromCamera(const Camera & cam) {
    // Je suis un petit rigolo :)
    Frustum frutsum;

    const float halfVSide = cam.getFarPlane() * tanf((radians(cam.getFov())) * 0.5f);

    const float halfHSide = halfVSide * cam.getAspectRatio();
    const Vec3 frontMultFar = cam.getFarPlane() * cam.getForward();

    frutsum.m_planes[4] = Plane( // nearFace
        cam.getPosition() + cam.getNearPlane() * cam.getForward(),
        cam.getForward());

    frutsum.m_planes[5] = Plane( // farFace
        cam.getPosition() + frontMultFar,
        -cam.getForward());

    frutsum.m_planes[1] = Plane( // rightFace
        cam.getPosition(),
        (frontMultFar - cam.getRight() * halfHSide).cross(cam.getUp()));

    frutsum.m_planes[0] = Plane( // leftFace
        cam.getPosition(),
        cam.getUp().cross(frontMultFar + cam.getRight() * halfHSide));

    frutsum.m_planes[3] = Plane( // topFace
        cam.getPosition(),
        cam.getRight().cross(frontMultFar - cam.getUp() * halfVSide));

    frutsum.m_planes[2] = Plane( // bottomFace
        cam.getPosition(),
        (frontMultFar + cam.getUp() * halfVSide).cross(cam.getRight()));

    return frutsum;
}

bool Frustum::isBoxInFrustum(const AABB & box) const {
    for (int i = 0; i < 6; i++) {
        const Plane & plane = m_planes[i];

        Vec3 p;
        float minX = std::min(box.m_min.x, box.m_max.x);
        float maxX = std::max(box.m_min.x, box.m_max.x);
        float minY = std::min(box.m_min.y, box.m_max.y);
        float maxY = std::max(box.m_min.y, box.m_max.y);
        float minZ = std::min(box.m_min.z, box.m_max.z);
        float maxZ = std::max(box.m_min.z, box.m_max.z);

        p.x = (plane.m_normal.x >= 0) ? maxX : minX;
        p.y = (plane.m_normal.y >= 0) ? maxY : minY;
        p.z = (plane.m_normal.z >= 0) ? maxZ : minZ;


        if (plane.distanceToPoint(p) < 0) {
            return false; // Box complètement hors du frustum
        }
    }
    return true; // Partiellement ou complètement dedans
}

AABB Frustum::computeBoundingBox() const {
    // Les 8 coins du frustum sont obtenus en intersectant les triplets de plans correspondants
    std::array<Vec3, 8> corners = {
        AABB::intersectPlanes(m_planes[0], m_planes[2], m_planes[4]), // left, bottom, near
        AABB::intersectPlanes(m_planes[0], m_planes[3], m_planes[4]), // left, top, near
        AABB::intersectPlanes(m_planes[1], m_planes[3], m_planes[4]), // right, top, near
        AABB::intersectPlanes(m_planes[1], m_planes[2], m_planes[4]), // right, bottom, near

        AABB::intersectPlanes(m_planes[0], m_planes[2], m_planes[5]), // left, bottom, far
        AABB::intersectPlanes(m_planes[0], m_planes[3], m_planes[5]), // left, top, far
        AABB::intersectPlanes(m_planes[1], m_planes[3], m_planes[5]), // right, top, far
        AABB::intersectPlanes(m_planes[1], m_planes[2], m_planes[5])  // right, bottom, far
    };

    Vec3 minCorner = corners[0];
    Vec3 maxCorner = corners[0];

    for (const auto & corner : corners) {
        minCorner.x = std::min(minCorner.x, corner.x);
        minCorner.y = std::min(minCorner.y, corner.y);
        minCorner.z = std::min(minCorner.z, corner.z);

        maxCorner.x = std::max(maxCorner.x, corner.x);
        maxCorner.y = std::max(maxCorner.y, corner.y);
        maxCorner.z = std::max(maxCorner.z, corner.z);
    }

    return AABB(minCorner, maxCorner);
}
