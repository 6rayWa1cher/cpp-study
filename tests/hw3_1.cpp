//
// Created by Konstantin Grigoriev on 04/10/2019.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw3_1/functionalprog.h"

int double_val(int val) {
    return val * val;
}

std::string append_one(std::string str) {
    return str + '1';
}


TEST_CASE("Map vectors", "[map]") {
    SECTION("Simple test") {
        std::vector<int> input = {0, 3, 10};
        CHECK(std::vector<int>{0, 9, 100} == map(input, double_val));
    }SECTION("Empty vector") {
        std::vector<int> input = {};
        CHECK(map(input, double_val).empty());
    }SECTION("String data") {
        std::vector<std::string> input = {"2 - 1 = ", "0.5 + 0.5 = "};
        CHECK(std::vector<std::string>{"2 - 1 = 1", "0.5 + 0.5 = 1"} == map(input, append_one));
    }
}