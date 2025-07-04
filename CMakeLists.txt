cmake_minimum_required(VERSION 3.14)
project(BringMeTheEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option pour activer AddressSanitizer (mettre ON avec -DSANITIZE_ADDRESS=ON)
option(SANITIZE_ADDRESS "Enable AddressSanitizer" OFF)

# Rechercher GLFW et GLM via le système
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Ajout de GLAD depuis un dossier externe
add_subdirectory(external/glad)
add_subdirectory(external/Catch2-3.8.1)

# Récupère tous les fichiers .cpp dans src/
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Récupère tout ce qu'il faut pour ImGui
file(GLOB IMGUI_SRC
    external/imgui/*.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# Exécutable final
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${IMGUI_SRC})

# Include dirs
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
)

# Lier les bibliothèques
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad
        glfw
        glm::glm
)

# Récupérer tous les fichiers de test
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

# Créer l'exécutable de tests
add_executable(BringMeTheEngine-tests ${TEST_SOURCES})

# Inclure les headers nécessaires
target_include_directories(BringMeTheEngine-tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# Lier les bibliothèques : moteur + dépendances + Catch2
target_link_libraries(BringMeTheEngine-tests
    PRIVATE
        Catch2::Catch2WithMain
        glad
        glfw
        glm::glm
)

include(CTest)
include(Catch)
catch_discover_tests(BringMeTheEngine-tests)

# Configuration AddressSanitizer
if(SANITIZE_ADDRESS)
    message(STATUS "🔍 AddressSanitizer activé")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        set(SANITIZE_FLAGS "-fsanitize=address" "-g")

        target_compile_options(${PROJECT_NAME} PRIVATE ${SANITIZE_FLAGS})
        target_link_options(${PROJECT_NAME} PRIVATE "-fsanitize=address")

        target_compile_options(BringMeTheEngine-tests PRIVATE ${SANITIZE_FLAGS})
        target_link_options(BringMeTheEngine-tests PRIVATE "-fsanitize=address")
    else()
        message(WARNING "AddressSanitizer n'est pas pris en charge par ce compilateur.")
    endif()
endif()