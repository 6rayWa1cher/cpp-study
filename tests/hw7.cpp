//
// Created by 6rayWa1cher on 04.02.2020.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw7/dispersion.h"
#include "../hw7/search.h"
#include "../hw7/sequence.h"
#include "../hw7/economics.h"
#include "../hw7/datepalindromes.h"

TEST_CASE("Dispersion evaluation", "[calculateDispersion]") {
	std::vector<int> testCase = {1, 3, 6, 1};
	CHECK(calculateDispersion(testCase.begin(), testCase.end()) == Approx(4.1875));
}

TEST_CASE("Nearest value search", "[searchNearest]") {
	SECTION("No values") {
		std::vector<double> v = {};
		CHECK(std::numeric_limits<double>::infinity() == searchNearest(v.begin(), v.end(), 15.0));
	} SECTION("Approx") {
		std::vector<double> v = {-7, 2, -1, 1};
		CHECK(-1 == searchNearest(v.begin(), v.end(), 0.0));
	} SECTION("Exact number") {
		std::vector<double> v = {-7, 2, -1, 1};
		CHECK(1 == searchNearest(v.begin(), v.end(), 2));
	}
}

TEST_CASE("Borders distance eval", "[getBorderDistances]") {
	SECTION("No values") {
		std::vector<int> v = {};
		CHECK(getBorderDistances(v).empty());
	} SECTION("Some sequences") {
		std::vector<int> v = {3, 3, 3, 3, 1, 5, 5, 2, 2, 2, 2, 2};
		CHECK(std::vector<int>{0, 1, 1, 0, 0, 0, 0, 0, 1, 2, 1, 0} == getBorderDistances(v));
	}
}

TEST_CASE("Economics report", "[makeYearReport]") {
	SECTION("No values") {
		std::map<std::string, std::vector<int>> map;
		std::ostringstream oss;
		makeYearReport(map, oss);
		CHECK("\n" == oss.str());
	} SECTION("Test #1") {
		std::map<std::string, std::vector<int>> map = {
				{std::string("John"),     std::vector<int>{
						2000, 2000, 2000, 2000,
						2000, 2000, 2000, 2000,
						2000, 2000, 2000, 2000
				}},
				{std::string("Mike"),     std::vector<int>{
						1500, 1500, 1500, 1500,
						1500, 1500, 1500, 1500,
						1500, 1500, 1500, 1500
				}},
				{std::string("Scarlett"), std::vector<int>{
						2500, 2500, 2500, 2500,
						2500, 2500, 2500, 2500,
						2500, 2500, 2500, 2500
				}}
		};
		std::ostringstream oss;
		makeYearReport(map, oss);
		CHECK(
				("Mike " + std::to_string(1500 * 12) + "\n" +
				 "John " + std::to_string(2000 * 12) + "\n" +
				 "Scarlett " + std::to_string(2500 * 12) + "\n")
				==
				oss.str()
		);
	}
}

TEST_CASE("Find date-palindromes", "[getPalindromeDatesBetween]") {
	SECTION("Reversed") {
		CHECK(getPalindromeDatesBetween("21.02.2012", "20.02.2012").empty());
	} SECTION("Test #1") {
		CHECK(std::vector<std::string>{"11.02.2011"} == getPalindromeDatesBetween("11.02.2011", "12.02.2011"));
	} SECTION("Test #2") {
		CHECK_THROWS(getPalindromeDatesBetween("11.02.011", "12.02.2011"));
	}
}