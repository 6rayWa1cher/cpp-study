//
// Created by Konstantin Grigoriev on 27/09/2019.
//

#define CATCH_CONFIG_MAIN

#include "../hw3/numcast.h"
#include "../catch.hpp"

TEST_CASE("Cast int to str with ns", "[numCast]") {
    REQUIRE("1000" == numCast(8, 2));
    REQUIRE("-1000" == numCast(-8, 2));
    REQUIRE("8" == numCast(8, 10));
    REQUIRE("2A" == numCast(42, 16));
    REQUIRE("1H" == numCast(35, 18));
}

TEST_CASE("Cast str to int with ns", "[numCast]") {
    REQUIRE(8 == numCast("1000", 2));
    REQUIRE(-8 == numCast("-1000", 2));
    REQUIRE(8 == numCast("8", 10));
    REQUIRE(42 == numCast("2A", 16));
    REQUIRE(35 == numCast("1H", 18));
}