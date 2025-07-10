#pragma once
#include <string>

class Texture {
public:
    Texture(const std::string& path, bool flip = true);
    ~Texture();

    void bind(unsigned int unit = 0) const;
    void unbind() const;
    unsigned int getID() const { return m_textureID; }

private:
    unsigned int m_textureID;
    int m_width, m_height, m_nrChannels;
};