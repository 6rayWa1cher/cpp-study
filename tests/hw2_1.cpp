//
// Created by Konstantin Grigoriev on 13/09/2019.
//

#define CATCH_CONFIG_MAIN

#include "../hw2.1/definefun.h"
#include "../catch.hpp"

TEST_CASE("Get max number", "[getMax]") {
    REQUIRE(3 == getMax(2, 3));
    REQUIRE(3 == getMax(3, 1));
}

TEST_CASE("It's broken!", "[brokenGetMax]") {
    char result = brokenGetMax(2, 3) + 5;
    std::cout << result << std::endl;
    REQUIRE(3 != result);
    REQUIRE(8 == result);
}