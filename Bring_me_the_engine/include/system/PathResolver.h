#pragma once

#include <filesystem>
#include <string>

class PathResolver {
public:
    static std::filesystem::path getExecutableDir(); // Dossier où se trouve l'exécutable
    static std::filesystem::path getResourcePath(const std::string& relative); // Fichier depuis le dossier du projet
};
