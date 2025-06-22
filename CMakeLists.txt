cmake_minimum_required(VERSION 3.14)
project(BringMeTheEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Rechercher GLFW et GLM via le système
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Ajout de GLAD depuis un dossier externe
add_subdirectory(external/glad)

# Récupère tous les fichiers .cpp dans src/
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Exécutable final
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES})

# Include dirs
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${CMAKE_SOURCE_DIR}/src
)

# Lier les bibliothèques
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad
        glfw
        glm::glm
)
