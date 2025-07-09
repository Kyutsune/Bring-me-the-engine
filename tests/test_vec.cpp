#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
using namespace Catch;

#include "math/Vec.h"

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
