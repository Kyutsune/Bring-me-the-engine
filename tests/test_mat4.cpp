#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
using namespace Catch;

#include "math/Trigo.h"
#include "math/Vec.h"
#include <iostream>

TEST_CASE("Création de Mat4", "[mat4]") {
    Mat4 m;
    REQUIRE(m[0] == Approx(1.0f));
    REQUIRE(m[5] == Approx(1.0f));
    REQUIRE(m[10] == Approx(1.0f));
    REQUIRE(m[15] == Approx(1.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Matrice identité", "[mat4]") {
    Mat4 m = Mat4::identity();
    REQUIRE(m[0] == Approx(1.0f));
    REQUIRE(m[5] == Approx(1.0f));
    REQUIRE(m[10] == Approx(1.0f));
    REQUIRE(m[15] == Approx(1.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction LookAT", "[mat4]") {
    Vec3 eye(0.0f, 0.0f, 5.0f);
    Vec3 center(0.0f, 0.0f, 0.0f);
    Vec3 up(0.0f, 1.0f, 0.0f);

    Mat4 view = Mat4::lookAt(eye, center, up);

    REQUIRE(view[0] == Approx(1.0f));
    REQUIRE(view[5] == Approx(1.0f));
    REQUIRE(view[10] == Approx(1.0f));
    REQUIRE(view[15] == Approx(1.0f));
    REQUIRE(view[12] == Approx(0.0f));
    REQUIRE(view[13] == Approx(0.0f));
    REQUIRE(view[14] == Approx(-5.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15 && i != 12 && i != 13 && i != 14) {
            REQUIRE(view[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction Translation", "[mat4]") {
    Vec3 translation(2.0f, 3.0f, 4.0f);
    Mat4 m = Mat4::Translation(translation);

    REQUIRE(m[0] == Approx(1.0f));
    REQUIRE(m[5] == Approx(1.0f));
    REQUIRE(m[10] == Approx(1.0f));
    REQUIRE(m[15] == Approx(1.0f));
    REQUIRE(m[12] == Approx(2.0f));
    REQUIRE(m[13] == Approx(3.0f));
    REQUIRE(m[14] == Approx(4.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15 && i != 12 && i != 13 && i != 14) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction translate", " [mat4]") {
    Mat4 m = Mat4::identity();
    Vec3 translation(2.0f, 3.0f, 4.0f);
    m.translate(translation);

    REQUIRE(m[0] == Approx(1.0f));
    REQUIRE(m[5] == Approx(1.0f));
    REQUIRE(m[10] == Approx(1.0f));
    REQUIRE(m[15] == Approx(1.0f));
    REQUIRE(m[12] == Approx(2.0f));
    REQUIRE(m[13] == Approx(3.0f));
    REQUIRE(m[14] == Approx(4.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15 && i != 12 && i != 13 && i != 14) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction Scale", "[mat4]") {
    Vec3 scale(2.0f, 3.0f, 4.0f);
    Mat4 m = Mat4::Scale(scale);

    REQUIRE(m[0] == Approx(2.0f));
    REQUIRE(m[5] == Approx(3.0f));
    REQUIRE(m[10] == Approx(4.0f));
    REQUIRE(m[15] == Approx(1.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction scale avec des paramètres séparés", "[mat4]") {
    Mat4 m = Mat4::Scale(2.0f, 3.0f, 4.0f);

    REQUIRE(m[0] == Approx(2.0f));
    REQUIRE(m[5] == Approx(3.0f));
    REQUIRE(m[10] == Approx(4.0f));
    REQUIRE(m[15] == Approx(1.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction Scale avec un facteur unique", "[mat4]") {
    Mat4 m = Mat4::Scale(2.0f);

    REQUIRE(m[0] == Approx(2.0f));
    REQUIRE(m[5] == Approx(2.0f));
    REQUIRE(m[10] == Approx(2.0f));
    REQUIRE(m[15] == Approx(1.0f));
    for (int i = 0; i < 16; ++i) {
        if (i != 0 && i != 5 && i != 10 && i != 15) {
            REQUIRE(m[i] == Approx(0.0f));
        }
    }
}

TEST_CASE("Test de la fonction rotateY", "[mat4]") {
    Mat4 m = Mat4::rotateY(radians(90.0f));

    std::cout << "Matrice de rotation Y:\n"
              << m;

    REQUIRE(m[0] == Approx(0.0f).margin(1e-5));
    REQUIRE(m[1] == Approx(0.0f));
    REQUIRE(m[2] == Approx(-1.0f));
    REQUIRE(m[3] == Approx(0.0f));
    REQUIRE(m[4] == Approx(0.0f));
    REQUIRE(m[5] == Approx(1.0f));
    REQUIRE(m[6] == Approx(0.0f));
    REQUIRE(m[7] == Approx(0.0f));
    REQUIRE(m[8] == Approx(1.0f));
    REQUIRE(m[9] == Approx(0.0f));
    REQUIRE(m[10] == Approx(0.0f).margin(1e-5));
    REQUIRE(m[11] == Approx(0.0f));
    REQUIRE(m[12] == Approx(0.0f));
    REQUIRE(m[13] == Approx(0.0f));
    REQUIRE(m[14] == Approx(0.0f));
    REQUIRE(m[15] == Approx(1.0f));
}
