//
// Created by Konstantin Grigoriev on 13/09/2019.
//
#define CATCH_CONFIG_MAIN

#include "../hw2/vectorfunc.h"
#include "../catch.hpp"

TEST_CASE("(1)Min index calculated", "[minIndex]") {
    SECTION("First is min") {
        std::vector<int> vector = {1, 5, 2, 4};
        REQUIRE(0 == minIndex(vector));
    }SECTION("Last is min") {
        std::vector<int> vector = {1, 5, 2, 4, 0};
        REQUIRE(4 == minIndex(vector));
    }SECTION("Random is min") {
        std::vector<int> vector = {1, 5, 2, -1, 4, 0};
        REQUIRE(3 == minIndex(vector));
    }SECTION("Line") {
        std::vector<int> vector = {1, 1, 1, 1, 1};
        REQUIRE(0 == minIndex(vector));
    }
}

TEST_CASE("(2)Strange expression calculated", "[calcExpress]") {
    SECTION("On zero") {
        std::vector<int> vector = calcExpress(0);
        REQUIRE(vector.empty());
    }SECTION("On one") {
        std::vector<int> vector = calcExpress(1);
        std::vector<int> expected = {1 + 4};
        REQUIRE(1 == vector.size());
        REQUIRE(expected == vector);
    }SECTION("On two") {
        std::vector<int> vector = calcExpress(2);
        std::vector<int> expected = {1 + 4, 4 + 9 + 16};
        REQUIRE(2 == vector.size());
        REQUIRE(expected == vector);
    }
}

TEST_CASE("(3) Palindrome checked", "[isPalindrome]") {
    SECTION("On empty") {
        std::vector<int> vector(0);
        REQUIRE(isPalindrome(vector));
    }SECTION("Standard palindrome") {
        std::vector<int> vector = {1, 2, 3, 2, 1};
        REQUIRE(isPalindrome(vector));
    }SECTION("Even palindrome") {
        std::vector<int> vector = {1, 2, 3, 3, 2, 1};
        REQUIRE(isPalindrome(vector));
    }SECTION("Wrong case 1") {
        std::vector<int> vector = {1, 2, 3, 4, 2, 1};
        REQUIRE_FALSE(isPalindrome(vector));
    }SECTION("Wrong case 2") {
        std::vector<int> vector = {1, 2, 3, 4, 3, 2, 3};
        REQUIRE_FALSE(isPalindrome(vector));
    }
}

TEST_CASE("(4) DNA stats calculated") {
    SECTION("On empty") {
        std::vector<char> vector(0);
        REQUIRE(calcDnaStats(vector).empty());
    }SECTION("Check case 1") {
        std::vector<char> vector = {'A', 'A', 'G', 'G', 'C', 'C', 'T', 'C'};
        std::vector<int> expected = {0, 0, 0, 1, 2, 1, 0, 0};
        REQUIRE(expected.size() == vector.size());
        REQUIRE(expected == calcDnaStats(vector));
    }SECTION("Check case 2") {
        std::vector<char> vector = {'G'};
        std::vector<int> expected = {0};
        REQUIRE(expected.size() == vector.size());
        REQUIRE(expected == calcDnaStats(vector));
    }
}