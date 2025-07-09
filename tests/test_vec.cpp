#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
using namespace Catch;

#include "math/Vec.h"

TEST_CASE("Vec3 addition works", "[vec3]") {
    Vec3 a(1, 2, 3);
    Vec3 b(4, 5, 6);
    Vec3 c = a + b;

    REQUIRE(c.x == Approx(5.0f));
    REQUIRE(c.y == Approx(7.0f));
    REQUIRE(c.z == Approx(9.0f));
}

TEST_CASE("Vec3 subtraction works", "[vec3]") {
    Vec3 a(4, 5, 6);
    Vec3 b(1, 2, 3);
    Vec3 c = a - b;

    REQUIRE(c.x == Approx(3.0f));
    REQUIRE(c.y == Approx(3.0f));
    REQUIRE(c.z == Approx(3.0f));
}
