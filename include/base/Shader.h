#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "base/Vec.h"
#include "engine/Light.h"
#include "engine/LightSettings.h"

// Classe qui représente les shaders du moteur, utilisée pour compiler et lier les vertex et fragment shaders.
class Shader {
public:
    GLuint ID;

    Shader(const std::string & vertexPath, const std::string & fragmentPath);
    ~Shader();

    void use() const;
    void setBool(const std::string & name, bool value) const;
    void setInt(const std::string & name, int value) const;
    void setFloat(const std::string & name, float value) const;

    void setMat4(const std::string & name, const Mat4 & mat) const;
    void setVec3(const std::string & name, float x, float y, float z) const;
    void setVec3(const std::string & name, const Vec3 & vec) const;


    void set(const std::string &name, const Vec3 &vec);
    void set(const std::string &name, float value);
    void set(const std::string &name, int value);

private:
    std::string loadFile(const std::string & path) const;
    GLuint compileShader(GLenum type, const std::string & source) const;
};
