//
// Created by Konstantin Grigoriev on 27/09/2019.
//

#define CATCH_CONFIG_MAIN

#include "../hw3/numcast.h"
#include "../hw3/stringops.h"
#include "../catch.hpp"
#include "../hw3/sortc.h"

TEST_CASE("Cast int to str with ns", "[numCast]") {
	CHECK("1000" == numCast(8, 2));
	CHECK("-1000" == numCast(-8, 2));
	CHECK("8" == numCast(8, 10));
	CHECK("2A" == numCast(42, 16));
	CHECK("1H" == numCast(35, 18));
}

TEST_CASE("Cast str to int with ns", "[numCast]") {
	CHECK(8 == numCast("1000", 2));
	CHECK(-8 == numCast("-1000", 2));
	CHECK(8 == numCast("8", 10));
	CHECK(42 == numCast("2A", 16));
	CHECK(35 == numCast("1H", 18));
}

TEST_CASE("Split string", "[split]") {
	SECTION("Simple test") {
		std::vector<std::string> expected = {"pen", "pineapple", "apple", "pen"};
		CHECK(expected == split("pen-pineapple-apple-pen", '-'));
	}SECTION("Start and end with delimiter") {
		std::vector<std::string> expected = {"", "once", "again", ""};
		CHECK(expected == split(" once again ", ' '));
	}SECTION("No delimiter in text") {
		std::vector<std::string> expected = {"tristam"};
		CHECK(expected == split("tristam", ' '));
	}
}

TEST_CASE("Bubble sort test", "[bubbleSort]") {
	SECTION("Simple test") {
		std::vector<int> start = {1, 2, 3, 0};
		bubbleSort(start);
		CHECK(std::vector<int>{0, 1, 2, 3} == start);
	}SECTION("Nothing to sort") {
		std::vector<int> start = {1, 2, 3, 4};
		bubbleSort(start);
		CHECK(std::vector<int>{1, 2, 3, 4} == start);
	}SECTION("Reversed") {
		std::vector<int> start = {4, 3, 2, 1};
		bubbleSort(start);
		CHECK(std::vector<int>{1, 2, 3, 4} == start);
	}SECTION("Empty array") {
		std::vector<int> start = {};
		bubbleSort(start);
		CHECK(start.empty());
	}
}
