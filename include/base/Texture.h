#pragma once
#include <string>

class Texture {
public:
    Texture(const std::string& path, bool flip = true);
    ~Texture();

    void bind(unsigned int unit = 0) const;
    void unbind() const;
    unsigned int getID() const { return textureID; }

private:
    unsigned int textureID;
    int width, height, nrChannels;
};