#include "rendering/TextureManager.h"

std::shared_ptr<Texture> TextureManager::load(const std::string & path) {
    auto it = cache.find(path);
    if (it != cache.end())
        return it->second;

    auto texture = std::make_shared<Texture>(path);
    cache[path] = texture;
    return texture;
}

void TextureManager::clear() {
    cache.clear();
}   