#include "math/PlaneBoundingVolume.h"
#include <cfloat>
#include <iostream>

AABB AABB::transform(const Mat4 & matrix) const {
    Vec3 corners[8] = {
        {min.x, min.y, min.z}, // corner 0
        {min.x, min.y, max.z}, // corner 1
        {min.x, max.y, min.z}, // corner 2
        {min.x, max.y, max.z}, // corner 3
        {max.x, min.y, min.z}, // corner 4
        {max.x, min.y, max.z}, // corner 5
        {max.x, max.y, min.z}, // corner 6
        {max.x, max.y, max.z}  // corner 7
    };

    AABB transformed;
    transformed.min = Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    transformed.max = Vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (const auto & corner : corners) {
        Vec3 transformedCorner = matrix * corner;
        transformed.min = Vec3(
            std::min(transformed.min.x, transformedCorner.x),
            std::min(transformed.min.y, transformedCorner.y),
            std::min(transformed.min.z, transformedCorner.z));
        transformed.max = Vec3(
            std::max(transformed.max.x, transformedCorner.x),
            std::max(transformed.max.y, transformedCorner.y),
            std::max(transformed.max.z, transformedCorner.z));
    }

    return transformed;
}

void AABB::setupBBoxBuffers() {
    float vertices[] = {
        min.x,
        min.y,
        min.z,
        max.x,
        min.y,
        min.z,
        min.x,
        max.y,
        min.z,
        max.x,
        max.y,
        min.z,
        min.x,
        min.y,
        max.z,
        max.x,
        min.y,
        max.z,
        min.x,
        max.y,
        max.z,
        max.x,
        max.y,
        max.z,
    };

    unsigned int indices[] = {
        0, 1, 1, 3, 3, 2, 2, 0, // bottom
        4, 5, 5, 7, 7, 6, 6, 4, // top
        0, 4, 1, 5, 2, 6, 3, 7  // vertical
    };

    glGenVertexArrays(1, &bboxVAO);
    glGenBuffers(1, &bboxVBO);
    glGenBuffers(1, &bboxEBO);

    glBindVertexArray(bboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, bboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindVertexArray(0);
}

void AABB::drawAABB(const Mat4 & model, const Mat4 & view, const Mat4 & projection, Shader & shader) {
    shader.use();

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.set("color", Vec3(1.0f, 1.0f, 1.0f));

    glBindVertexArray(bboxVAO);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Vec3 AABB::intersectPlanes(const Plane& p1, const Plane& p2, const Plane& p3) {
    Mat4 A({
        p1.normal.x, p1.normal.y, p1.normal.z, 0.0f,
        p2.normal.x, p2.normal.y, p2.normal.z, 0.0f,
        p3.normal.x, p3.normal.y, p3.normal.z, 0.0f,
        0.0f,        0.0f,        0.0f,        1.0f
    });

    Vec3 b(-p1.distance, -p2.distance, -p3.distance);
    Vec3 result = A.inverse() * b;
    return result;
}