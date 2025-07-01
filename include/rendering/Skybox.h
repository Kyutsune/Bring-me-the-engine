#pragma once
#include <glad/glad.h>
#include <string>
#include <vector>
#include "rendering/Shader.h"

class Skybox {
public:
    GLuint textureID;
    GLuint VAO, VBO;

    Skybox(const std::vector<std::string> & faces);
    ~Skybox();

    void bind(unsigned int unit = 0) const;
    void unbind() const;
    
    void setupCube();
    void draw(const Shader& shader, const Mat4& view, const Mat4& projection) const;
};
