//
// Created by 6rayWa1cher on 07.05.2020.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw11_12/firstfollow.h"

TEST_CASE("Grammar test 1", "[Grammar]") {
	Grammar grammar;
	std::string grammarString =
			"A -> B C\n"
			"B -> t\n"
			"C -> l\n"
			"D -> m\n";
	std::istringstream iss(grammarString);
	REQUIRE(grammar.loadGrammar(iss));

	SECTION("FIRST") {
		CHECK(std::set<std::string>{"t"} == grammar.first(std::vector<std::string>{"A"}));
		CHECK(std::set<std::string>{"t"} == grammar.first(std::vector<std::string>{"B"}));
		CHECK(std::set<std::string>{"l"} == grammar.first(std::vector<std::string>{"C"}));
		CHECK(std::set<std::string>{"m"} == grammar.first(std::vector<std::string>{"D"}));
	}

	SECTION("FOLLOW") {
		CHECK(std::set<std::string>{"$"} == grammar.follow("A"));
		CHECK(std::set<std::string>{"l"} == grammar.follow("B"));
		CHECK(std::set<std::string>{"$"} == grammar.follow("C"));
		CHECK(grammar.follow("D").empty());
	}
}

TEST_CASE("Grammar test 2", "[Grammar]") {
	REQUIRE("e" == EPSILON);
	Grammar grammar;
	std::string grammarString =
			"A -> L A' R\n"
			"A' -> A\n"
			"A' -> e\n"
			"L -> l\n"
			"R -> r\n";
	std::istringstream iss(grammarString);
	REQUIRE(grammar.loadGrammar(iss));

	SECTION("FIRST") {
		CHECK(std::set<std::string>{"l"} == grammar.first(std::vector<std::string>{"A"}));
		CHECK(std::set<std::string>{"l", "e"} == grammar.first(std::vector<std::string>{"A'"}));
		CHECK(std::set<std::string>{"l"} == grammar.first(std::vector<std::string>{"L"}));
		CHECK(std::set<std::string>{"r"} == grammar.first(std::vector<std::string>{"R"}));
	}
	SECTION("FOLLOW") {
		CHECK(std::set<std::string>{"$", "r"} == grammar.follow("A"));
		CHECK(std::set<std::string>{"r"} == grammar.follow("A'"));
		CHECK(std::set<std::string>{"l", "r"} == grammar.follow("L"));
		CHECK(std::set<std::string>{"$", "r"} == grammar.follow("R"));
	}
}