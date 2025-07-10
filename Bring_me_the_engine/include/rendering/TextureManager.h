#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "rendering/Texture.h"

class TextureManager {
public:
    static std::shared_ptr<Texture> load(const std::string& path);
    static void clear();

private:
    static inline std::unordered_map<std::string, std::shared_ptr<Texture>> cache;
};