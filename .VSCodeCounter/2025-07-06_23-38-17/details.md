# Details

Date : 2025-07-06 23:38:17

Directory /home/kyutsune/Bring-me-the-engine

Total : 72 files,  3133 codes, 157 comments, 796 blanks, all 4086 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [CMakeLists.txt](/CMakeLists.txt) | CMake | 72 | 0 | 18 | 90 |
| [Competences\_acquises/Callback.cpp](/Competences_acquises/Callback.cpp) | C++ | 13 | 9 | 7 | 29 |
| [README.md](/README.md) | Markdown | 59 | 0 | 9 | 68 |
| [include/Globals.h](/include/Globals.h) | C++ | 10 | 3 | 4 | 17 |
| [include/camera/Camera.h](/include/camera/Camera.h) | C++ | 38 | 0 | 9 | 47 |
| [include/camera/Frustum.h](/include/camera/Frustum.h) | C++ | 12 | 4 | 4 | 20 |
| [include/engine/Entity.h](/include/engine/Entity.h) | C++ | 38 | 0 | 13 | 51 |
| [include/engine/Light.h](/include/engine/Light.h) | C++ | 68 | 3 | 11 | 82 |
| [include/engine/LightSettings.h](/include/engine/LightSettings.h) | C++ | 17 | 1 | 5 | 23 |
| [include/engine/LightingManager.h](/include/engine/LightingManager.h) | C++ | 26 | 5 | 10 | 41 |
| [include/engine/Material.h](/include/engine/Material.h) | C++ | 11 | 3 | 3 | 17 |
| [include/engine/Mesh.h](/include/engine/Mesh.h) | C++ | 22 | 1 | 9 | 32 |
| [include/engine/Scene.h](/include/engine/Scene.h) | C++ | 46 | 0 | 11 | 57 |
| [include/geometry/Cube.h](/include/geometry/Cube.h) | C++ | 52 | 6 | 12 | 70 |
| [include/geometry/Floor.h](/include/geometry/Floor.h) | C++ | 29 | 0 | 6 | 35 |
| [include/geometry/Skybox\_mesh.h](/include/geometry/Skybox_mesh.h) | C++ | 44 | 1 | 9 | 54 |
| [include/geometry/Sphere.h](/include/geometry/Sphere.h) | C++ | 58 | 1 | 12 | 71 |
| [include/input/ClavierSouris.h](/include/input/ClavierSouris.h) | C++ | 13 | 3 | 4 | 20 |
| [include/math/Color.h](/include/math/Color.h) | C++ | 47 | 0 | 7 | 54 |
| [include/math/PlaneBoundingVolume.h](/include/math/PlaneBoundingVolume.h) | C++ | 50 | 3 | 14 | 67 |
| [include/math/Tang\_Bitang.h](/include/math/Tang_Bitang.h) | C++ | 47 | 3 | 12 | 62 |
| [include/math/Trigo.h](/include/math/Trigo.h) | C++ | 5 | 0 | 1 | 6 |
| [include/math/Vec.h](/include/math/Vec.h) | C++ | 151 | 5 | 39 | 195 |
| [include/rendering/Renderer.h](/include/rendering/Renderer.h) | C++ | 29 | 0 | 7 | 36 |
| [include/rendering/Shader.h](/include/rendering/Shader.h) | C++ | 31 | 1 | 12 | 44 |
| [include/rendering/ShadowManager.h](/include/rendering/ShadowManager.h) | C++ | 20 | 0 | 8 | 28 |
| [include/rendering/Skybox.h](/include/rendering/Skybox.h) | C++ | 16 | 0 | 5 | 21 |
| [include/rendering/Texture.h](/include/rendering/Texture.h) | C++ | 13 | 0 | 3 | 16 |
| [include/rendering/Vertex.h](/include/rendering/Vertex.h) | C++ | 10 | 0 | 2 | 12 |
| [include/shadows/DirectionalShadowMap.h](/include/shadows/DirectionalShadowMap.h) | C++ | 18 | 0 | 6 | 24 |
| [include/shadows/PonctualShadowMap.h](/include/shadows/PonctualShadowMap.h) | C++ | 25 | 4 | 7 | 36 |
| [include/ui/Menu.h](/include/ui/Menu.h) | C++ | 24 | 1 | 8 | 33 |
| [include/ui/Sections.h](/include/ui/Sections.h) | C++ | 10 | 0 | 2 | 12 |
| [rebuild.sh](/rebuild.sh) | Shell Script | 5 | 1 | 1 | 7 |
| [shaders/debug/bounding\_box.frag](/shaders/debug/bounding_box.frag) | GLSL | 6 | 0 | 3 | 9 |
| [shaders/debug/bounding\_box.vert](/shaders/debug/bounding_box.vert) | GLSL | 8 | 0 | 2 | 10 |
| [shaders/debug/debug\_cubemap\_shadow.frag](/shaders/debug/debug_cubemap_shadow.frag) | GLSL | 18 | 0 | 6 | 24 |
| [shaders/debug/debug\_cubemap\_shadow.vert](/shaders/debug/debug_cubemap_shadow.vert) | GLSL | 8 | 0 | 2 | 10 |
| [shaders/debug/quad.frag](/shaders/debug/quad.frag) | GLSL | 8 | 0 | 1 | 9 |
| [shaders/debug/quad.vert](/shaders/debug/quad.vert) | GLSL | 9 | 0 | 3 | 12 |
| [shaders/main\_shaders/light\_pos.frag](/shaders/main_shaders/light_pos.frag) | GLSL | 6 | 0 | 0 | 6 |
| [shaders/main\_shaders/light\_pos.vert](/shaders/main_shaders/light_pos.vert) | GLSL | 8 | 0 | 0 | 8 |
| [shaders/main\_shaders/skybox.frag](/shaders/main_shaders/skybox.frag) | GLSL | 7 | 0 | 2 | 9 |
| [shaders/main\_shaders/skybox.vert](/shaders/main_shaders/skybox.vert) | GLSL | 10 | 0 | 3 | 13 |
| [shaders/main\_shaders/vertex.frag](/shaders/main_shaders/vertex.frag) | GLSL | 188 | 18 | 60 | 266 |
| [shaders/main\_shaders/vertex.vert](/shaders/main_shaders/vertex.vert) | GLSL | 30 | 0 | 10 | 40 |
| [shaders/shadows/dir\_shadow.frag](/shaders/shadows/dir_shadow.frag) | GLSL | 4 | 0 | 0 | 4 |
| [shaders/shadows/dir\_shadow.vert](/shaders/shadows/dir_shadow.vert) | GLSL | 8 | 0 | 4 | 12 |
| [shaders/shadows/ponc\_shadow.frag](/shaders/shadows/ponc_shadow.frag) | GLSL | 10 | 0 | 3 | 13 |
| [shaders/shadows/ponc\_shadow.geom](/shaders/shadows/ponc_shadow.geom) | GLSL | 17 | 0 | 3 | 20 |
| [shaders/shadows/ponc\_shadow.vert](/shaders/shadows/ponc_shadow.vert) | GLSL | 9 | 0 | 3 | 12 |
| [src/Globals.cpp](/src/Globals.cpp) | C++ | 6 | 0 | 4 | 10 |
| [src/camera/Camera.cpp](/src/camera/Camera.cpp) | C++ | 7 | 0 | 2 | 9 |
| [src/camera/Frustum.cpp](/src/camera/Frustum.cpp) | C++ | 101 | 13 | 32 | 146 |
| [src/engine/Entity.cpp](/src/engine/Entity.cpp) | C++ | 58 | 0 | 11 | 69 |
| [src/engine/LightingManager.cpp](/src/engine/LightingManager.cpp) | C++ | 109 | 7 | 22 | 138 |
| [src/engine/Mesh.cpp](/src/engine/Mesh.cpp) | C++ | 55 | 8 | 20 | 83 |
| [src/engine/Scene.cpp](/src/engine/Scene.cpp) | C++ | 110 | 7 | 17 | 134 |
| [src/input/ClavierSouris.cpp](/src/input/ClavierSouris.cpp) | C++ | 76 | 5 | 24 | 105 |
| [src/main.cpp](/src/main.cpp) | C++ | 93 | 10 | 23 | 126 |
| [src/math/PlaneBoundingVolume.cpp](/src/math/PlaneBoundingVolume.cpp) | C++ | 95 | 1 | 17 | 113 |
| [src/math/Vec.cpp](/src/math/Vec.cpp) | C++ | 272 | 4 | 57 | 333 |
| [src/rendering/Renderer.cpp](/src/rendering/Renderer.cpp) | C++ | 54 | 9 | 16 | 79 |
| [src/rendering/Shader.cpp](/src/rendering/Shader.cpp) | C++ | 126 | 0 | 29 | 155 |
| [src/rendering/ShadowManager.cpp](/src/rendering/ShadowManager.cpp) | C++ | 62 | 10 | 16 | 88 |
| [src/rendering/Skybox.cpp](/src/rendering/Skybox.cpp) | C++ | 95 | 0 | 23 | 118 |
| [src/rendering/Texture.cpp](/src/rendering/Texture.cpp) | C++ | 40 | 3 | 9 | 52 |
| [src/shadows/DirectionalShadowMap.cpp](/src/shadows/DirectionalShadowMap.cpp) | C++ | 64 | 0 | 20 | 84 |
| [src/shadows/PonctualShadowMap.cpp](/src/shadows/PonctualShadowMap.cpp) | C++ | 72 | 1 | 24 | 97 |
| [src/ui/Menu.cpp](/src/ui/Menu.cpp) | C++ | 54 | 3 | 16 | 73 |
| [src/ui/Sections.cpp](/src/ui/Sections.cpp) | C++ | 89 | 0 | 15 | 104 |
| [tests/test\_vec.cpp](/tests/test_vec.cpp) | C++ | 12 | 0 | 4 | 16 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)