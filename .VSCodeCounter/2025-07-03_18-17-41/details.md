# Details

Date : 2025-07-03 18:17:41

Directory /home/kyutsune/Bring-me-the-engine

Total : 61 files,  2723 codes, 142 comments, 678 blanks, all 3543 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [CMakeLists.txt](/CMakeLists.txt) | CMake | 57 | 0 | 16 | 73 |
| [Competences\_acquises/Callback.cpp](/Competences_acquises/Callback.cpp) | C++ | 13 | 9 | 7 | 29 |
| [README.md](/README.md) | Markdown | 57 | 0 | 7 | 64 |
| [include/Globals.h](/include/Globals.h) | C++ | 7 | 3 | 3 | 13 |
| [include/camera/Camera.h](/include/camera/Camera.h) | C++ | 40 | 0 | 8 | 48 |
| [include/camera/Frustum.h](/include/camera/Frustum.h) | C++ | 12 | 4 | 4 | 20 |
| [include/engine/Entity.h](/include/engine/Entity.h) | C++ | 38 | 0 | 13 | 51 |
| [include/engine/Light.h](/include/engine/Light.h) | C++ | 39 | 2 | 5 | 46 |
| [include/engine/LightSettings.h](/include/engine/LightSettings.h) | C++ | 17 | 1 | 5 | 23 |
| [include/engine/LightingManager.h](/include/engine/LightingManager.h) | C++ | 25 | 5 | 8 | 38 |
| [include/engine/Material.h](/include/engine/Material.h) | C++ | 11 | 3 | 3 | 17 |
| [include/engine/Mesh.h](/include/engine/Mesh.h) | C++ | 22 | 1 | 9 | 32 |
| [include/engine/Scene.h](/include/engine/Scene.h) | C++ | 46 | 1 | 14 | 61 |
| [include/geometry/Cube.h](/include/geometry/Cube.h) | C++ | 52 | 6 | 12 | 70 |
| [include/geometry/Floor.h](/include/geometry/Floor.h) | C++ | 29 | 0 | 6 | 35 |
| [include/geometry/Skybox\_mesh.h](/include/geometry/Skybox_mesh.h) | C++ | 44 | 1 | 9 | 54 |
| [include/geometry/Sphere.h](/include/geometry/Sphere.h) | C++ | 58 | 1 | 12 | 71 |
| [include/input/ClavierSouris.h](/include/input/ClavierSouris.h) | C++ | 13 | 3 | 4 | 20 |
| [include/math/Color.h](/include/math/Color.h) | C++ | 46 | 0 | 6 | 52 |
| [include/math/PlaneBoundingVolume.h](/include/math/PlaneBoundingVolume.h) | C++ | 50 | 3 | 14 | 67 |
| [include/math/Tang\_Bitang.h](/include/math/Tang_Bitang.h) | C++ | 47 | 3 | 12 | 62 |
| [include/math/Trigo.h](/include/math/Trigo.h) | C++ | 5 | 0 | 1 | 6 |
| [include/math/Vec.h](/include/math/Vec.h) | C++ | 151 | 3 | 39 | 193 |
| [include/rendering/Renderer.h](/include/rendering/Renderer.h) | C++ | 31 | 0 | 9 | 40 |
| [include/rendering/Shader.h](/include/rendering/Shader.h) | C++ | 28 | 1 | 10 | 39 |
| [include/rendering/Skybox.h](/include/rendering/Skybox.h) | C++ | 16 | 0 | 5 | 21 |
| [include/rendering/Texture.h](/include/rendering/Texture.h) | C++ | 13 | 0 | 3 | 16 |
| [include/rendering/Vertex.h](/include/rendering/Vertex.h) | C++ | 10 | 0 | 2 | 12 |
| [include/ui/Menu.h](/include/ui/Menu.h) | C++ | 24 | 1 | 8 | 33 |
| [include/ui/Sections.h](/include/ui/Sections.h) | C++ | 10 | 0 | 4 | 14 |
| [rebuild.sh](/rebuild.sh) | Shell Script | 5 | 1 | 1 | 7 |
| [shaders/bounding\_box.frag](/shaders/bounding_box.frag) | GLSL | 6 | 0 | 3 | 9 |
| [shaders/bounding\_box.vert](/shaders/bounding_box.vert) | GLSL | 8 | 0 | 2 | 10 |
| [shaders/debug/quad.frag](/shaders/debug/quad.frag) | GLSL | 8 | 0 | 1 | 9 |
| [shaders/debug/quad.vert](/shaders/debug/quad.vert) | GLSL | 9 | 0 | 3 | 12 |
| [shaders/light\_pos.frag](/shaders/light_pos.frag) | GLSL | 6 | 0 | 0 | 6 |
| [shaders/light\_pos.vert](/shaders/light_pos.vert) | GLSL | 8 | 0 | 0 | 8 |
| [shaders/shadow.frag](/shaders/shadow.frag) | GLSL | 4 | 0 | 0 | 4 |
| [shaders/shadow.vert](/shaders/shadow.vert) | GLSL | 8 | 0 | 4 | 12 |
| [shaders/skybox.frag](/shaders/skybox.frag) | GLSL | 7 | 0 | 2 | 9 |
| [shaders/skybox.vert](/shaders/skybox.vert) | GLSL | 10 | 0 | 3 | 13 |
| [shaders/vertex.frag](/shaders/vertex.frag) | GLSL | 139 | 15 | 38 | 192 |
| [shaders/vertex.vert](/shaders/vertex.vert) | GLSL | 30 | 0 | 10 | 40 |
| [src/Globals.cpp](/src/Globals.cpp) | C++ | 6 | 0 | 1 | 7 |
| [src/camera/Camera.cpp](/src/camera/Camera.cpp) | C++ | 7 | 0 | 2 | 9 |
| [src/camera/Frustum.cpp](/src/camera/Frustum.cpp) | C++ | 101 | 13 | 32 | 146 |
| [src/engine/Entity.cpp](/src/engine/Entity.cpp) | C++ | 58 | 0 | 11 | 69 |
| [src/engine/LightingManager.cpp](/src/engine/LightingManager.cpp) | C++ | 88 | 7 | 19 | 114 |
| [src/engine/Mesh.cpp](/src/engine/Mesh.cpp) | C++ | 55 | 8 | 20 | 83 |
| [src/engine/Scene.cpp](/src/engine/Scene.cpp) | C++ | 89 | 7 | 15 | 111 |
| [src/input/ClavierSouris.cpp](/src/input/ClavierSouris.cpp) | C++ | 76 | 5 | 24 | 105 |
| [src/main.cpp](/src/main.cpp) | C++ | 80 | 10 | 23 | 113 |
| [src/math/PlaneBoundingVolume.cpp](/src/math/PlaneBoundingVolume.cpp) | C++ | 95 | 1 | 17 | 113 |
| [src/math/Vec.cpp](/src/math/Vec.cpp) | C++ | 270 | 4 | 56 | 330 |
| [src/rendering/Renderer.cpp](/src/rendering/Renderer.cpp) | C++ | 169 | 14 | 43 | 226 |
| [src/rendering/Shader.cpp](/src/rendering/Shader.cpp) | C++ | 89 | 0 | 22 | 111 |
| [src/rendering/Skybox.cpp](/src/rendering/Skybox.cpp) | C++ | 95 | 0 | 23 | 118 |
| [src/rendering/Texture.cpp](/src/rendering/Texture.cpp) | C++ | 36 | 3 | 10 | 49 |
| [src/ui/Menu.cpp](/src/ui/Menu.cpp) | C++ | 54 | 3 | 16 | 73 |
| [src/ui/Sections.cpp](/src/ui/Sections.cpp) | C++ | 84 | 0 | 15 | 99 |
| [tests/test\_vec.cpp](/tests/test_vec.cpp) | C++ | 12 | 0 | 4 | 16 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)