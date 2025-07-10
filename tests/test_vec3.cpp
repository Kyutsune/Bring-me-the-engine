#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
using namespace Catch;

#include "math/Vec.h"

TEST_CASE("Création de Vec3", "[vec3]") {
    Vec3 v(1, 2, 3);
    REQUIRE(v.x == Approx(1.0f));
    REQUIRE(v.y == Approx(2.0f));
    REQUIRE(v.z == Approx(3.0f));
}

TEST_CASE("Addition de Vec3", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 c = a + b;

    REQUIRE(c.x == Approx(5.0f));
    REQUIRE(c.y == Approx(7.0f));
    REQUIRE(c.z == Approx(9.0f));
}

TEST_CASE("Soustraction de Vec3", "[vec3]") {
    Vec3 a(4, 5, 6);
    Vec3 b(1, 2, 3);
    Vec3 c = a - b;

    REQUIRE(c.x == Approx(3.0f));
    REQUIRE(c.y == Approx(3.0f));
    REQUIRE(c.z == Approx(3.0f));
}

TEST_CASE("Exceptions: Division par zéro", "[vec3]") {
    REQUIRE_THROWS(Vec3(1, 2, 3) / 0);
}

TEST_CASE("Division par un scalaire", "[vec3]") {
    Vec3 a(4, 8, 12);
    Vec3 b = a / 2;

    REQUIRE(b.x == Approx(2.0f));
    REQUIRE(b.y == Approx(4.0f));
    REQUIRE(b.z == Approx(6.0f));
}

TEST_CASE("Division par un scalaire négatif", "[vec3]") {
    Vec3 a(4, 8, 12);
    Vec3 b = a / -2;

    REQUIRE(b.x == Approx(-2.0f));
    REQUIRE(b.y == Approx(-4.0f));
    REQUIRE(b.z == Approx(-6.0f));
}


TEST_CASE("Multiplication par un scalaire", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b = a * 2;

    REQUIRE(b.x == Approx(2.0f));
    REQUIRE(b.y == Approx(4.0f));
    REQUIRE(b.z == Approx(6.0f));
}

TEST_CASE("Multiplication par un scalaire négatif", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b = a * -2;

    REQUIRE(b.x == Approx(-2.0f));
    REQUIRE(b.y == Approx(-4.0f));
    REQUIRE(b.z == Approx(-6.0f));
}

TEST_CASE("Multiplication par un autre Vec3", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 c = a * b;

    REQUIRE(c.x == Approx(4.0f));
    REQUIRE(c.y == Approx(10.0f));
    REQUIRE(c.z == Approx(18.0f));
}

TEST_CASE("Normalisation de Vec3", "[vec3]") {
    Vec3 a(3, 4, 0);
    Vec3 b = a.normalized();

    REQUIRE(b.length() == Approx(1.0f));
    REQUIRE(b.x == Approx(0.6f));
    REQUIRE(b.y == Approx(0.8f));
    REQUIRE(b.z == Approx(0.0f));
}

TEST_CASE("Longueur de Vec3", "[vec3]") {
    Vec3 a(3, 4, 0);
    float length = a.length();

    REQUIRE(length == Approx(5.0f));
}

TEST_CASE("produit scalaire de Vec3", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    float dotProduct = a.dot(b);

    REQUIRE(dotProduct == Approx(32.0f));
}

TEST_CASE("produit vectoriel de Vec3", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 crossProduct = a.cross(b);

    REQUIRE(crossProduct.x == Approx(-3.0f));
    REQUIRE(crossProduct.y == Approx(6.0f));
    REQUIRE(crossProduct.z == Approx(-3.0f));
}