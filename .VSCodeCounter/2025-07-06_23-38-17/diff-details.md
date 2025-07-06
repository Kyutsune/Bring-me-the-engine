# Diff Details

Date : 2025-07-06 23:38:17

Directory /home/kyutsune/Bring-me-the-engine

Total : 52 files,  410 codes, 15 comments, 118 blanks, all 543 lines

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [CMakeLists.txt](/CMakeLists.txt) | CMake | 15 | 0 | 2 | 17 |
| [README.md](/README.md) | Markdown | 2 | 0 | 2 | 4 |
| [include/Globals.h](/include/Globals.h) | C++ | 3 | 0 | 1 | 4 |
| [include/camera/Camera.h](/include/camera/Camera.h) | C++ | -2 | 0 | 1 | -1 |
| [include/engine/Light.h](/include/engine/Light.h) | C++ | 29 | 1 | 6 | 36 |
| [include/engine/LightingManager.h](/include/engine/LightingManager.h) | C++ | 1 | 0 | 2 | 3 |
| [include/engine/Scene.h](/include/engine/Scene.h) | C++ | 0 | -1 | -3 | -4 |
| [include/math/Color.h](/include/math/Color.h) | C++ | 1 | 0 | 1 | 2 |
| [include/math/Vec.h](/include/math/Vec.h) | C++ | 0 | 2 | 0 | 2 |
| [include/rendering/Renderer.h](/include/rendering/Renderer.h) | C++ | -2 | 0 | -2 | -4 |
| [include/rendering/Shader.h](/include/rendering/Shader.h) | C++ | 3 | 0 | 2 | 5 |
| [include/rendering/ShadowManager.h](/include/rendering/ShadowManager.h) | C++ | 20 | 0 | 8 | 28 |
| [include/shadows/DirectionalShadowMap.h](/include/shadows/DirectionalShadowMap.h) | C++ | 18 | 0 | 6 | 24 |
| [include/shadows/PonctualShadowMap.h](/include/shadows/PonctualShadowMap.h) | C++ | 25 | 4 | 7 | 36 |
| [include/ui/Sections.h](/include/ui/Sections.h) | C++ | 0 | 0 | -2 | -2 |
| [shaders/bounding\_box.frag](/shaders/bounding_box.frag) | GLSL | -6 | 0 | -3 | -9 |
| [shaders/bounding\_box.vert](/shaders/bounding_box.vert) | GLSL | -8 | 0 | -2 | -10 |
| [shaders/debug/bounding\_box.frag](/shaders/debug/bounding_box.frag) | GLSL | 6 | 0 | 3 | 9 |
| [shaders/debug/bounding\_box.vert](/shaders/debug/bounding_box.vert) | GLSL | 8 | 0 | 2 | 10 |
| [shaders/debug/debug\_cubemap\_shadow.frag](/shaders/debug/debug_cubemap_shadow.frag) | GLSL | 18 | 0 | 6 | 24 |
| [shaders/debug/debug\_cubemap\_shadow.vert](/shaders/debug/debug_cubemap_shadow.vert) | GLSL | 8 | 0 | 2 | 10 |
| [shaders/light\_pos.frag](/shaders/light_pos.frag) | GLSL | -6 | 0 | 0 | -6 |
| [shaders/light\_pos.vert](/shaders/light_pos.vert) | GLSL | -8 | 0 | 0 | -8 |
| [shaders/main\_shaders/light\_pos.frag](/shaders/main_shaders/light_pos.frag) | GLSL | 6 | 0 | 0 | 6 |
| [shaders/main\_shaders/light\_pos.vert](/shaders/main_shaders/light_pos.vert) | GLSL | 8 | 0 | 0 | 8 |
| [shaders/main\_shaders/skybox.frag](/shaders/main_shaders/skybox.frag) | GLSL | 7 | 0 | 2 | 9 |
| [shaders/main\_shaders/skybox.vert](/shaders/main_shaders/skybox.vert) | GLSL | 10 | 0 | 3 | 13 |
| [shaders/main\_shaders/vertex.frag](/shaders/main_shaders/vertex.frag) | GLSL | 188 | 18 | 60 | 266 |
| [shaders/main\_shaders/vertex.vert](/shaders/main_shaders/vertex.vert) | GLSL | 30 | 0 | 10 | 40 |
| [shaders/shadow.frag](/shaders/shadow.frag) | GLSL | -4 | 0 | 0 | -4 |
| [shaders/shadow.vert](/shaders/shadow.vert) | GLSL | -8 | 0 | -4 | -12 |
| [shaders/shadows/dir\_shadow.frag](/shaders/shadows/dir_shadow.frag) | GLSL | 4 | 0 | 0 | 4 |
| [shaders/shadows/dir\_shadow.vert](/shaders/shadows/dir_shadow.vert) | GLSL | 8 | 0 | 4 | 12 |
| [shaders/shadows/ponc\_shadow.frag](/shaders/shadows/ponc_shadow.frag) | GLSL | 10 | 0 | 3 | 13 |
| [shaders/shadows/ponc\_shadow.geom](/shaders/shadows/ponc_shadow.geom) | GLSL | 17 | 0 | 3 | 20 |
| [shaders/shadows/ponc\_shadow.vert](/shaders/shadows/ponc_shadow.vert) | GLSL | 9 | 0 | 3 | 12 |
| [shaders/skybox.frag](/shaders/skybox.frag) | GLSL | -7 | 0 | -2 | -9 |
| [shaders/skybox.vert](/shaders/skybox.vert) | GLSL | -10 | 0 | -3 | -13 |
| [shaders/vertex.frag](/shaders/vertex.frag) | GLSL | -139 | -15 | -38 | -192 |
| [shaders/vertex.vert](/shaders/vertex.vert) | GLSL | -30 | 0 | -10 | -40 |
| [src/Globals.cpp](/src/Globals.cpp) | C++ | 0 | 0 | 3 | 3 |
| [src/engine/LightingManager.cpp](/src/engine/LightingManager.cpp) | C++ | 21 | 0 | 3 | 24 |
| [src/engine/Scene.cpp](/src/engine/Scene.cpp) | C++ | 21 | 0 | 2 | 23 |
| [src/main.cpp](/src/main.cpp) | C++ | 13 | 0 | 0 | 13 |
| [src/math/Vec.cpp](/src/math/Vec.cpp) | C++ | 2 | 0 | 1 | 3 |
| [src/rendering/Renderer.cpp](/src/rendering/Renderer.cpp) | C++ | -115 | -5 | -27 | -147 |
| [src/rendering/Shader.cpp](/src/rendering/Shader.cpp) | C++ | 37 | 0 | 7 | 44 |
| [src/rendering/ShadowManager.cpp](/src/rendering/ShadowManager.cpp) | C++ | 62 | 10 | 16 | 88 |
| [src/rendering/Texture.cpp](/src/rendering/Texture.cpp) | C++ | 4 | 0 | -1 | 3 |
| [src/shadows/DirectionalShadowMap.cpp](/src/shadows/DirectionalShadowMap.cpp) | C++ | 64 | 0 | 20 | 84 |
| [src/shadows/PonctualShadowMap.cpp](/src/shadows/PonctualShadowMap.cpp) | C++ | 72 | 1 | 24 | 97 |
| [src/ui/Sections.cpp](/src/ui/Sections.cpp) | C++ | 5 | 0 | 0 | 5 |

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details