#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
    GLuint ID;

    Shader(const std::string & vertexPath, const std::string & fragmentPath);
    ~Shader();

    void use() const;
    void setBool(const std::string & name, bool value) const;
    void setInt(const std::string & name, int value) const;
    void setFloat(const std::string & name, float value) const;

    void setMat4(const std::string & name, const glm::mat4 & mat) const;
    void setVec3(const std::string & name, float x, float y, float z) const;
    void setVec3(const std::string & name, const glm::vec3 & vec) const;

private:
    std::string loadFile(const std::string & path) const;
    GLuint compileShader(GLenum type, const std::string & source) const;
};
