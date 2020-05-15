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
	SECTION("SATABLE") {
		REQUIRE(grammar.buildSATable());
		const std::map<std::string, std::map<std::string, std::set<SaCell>>>& saTable = grammar.getSaTable();
		CHECK(SaCell(RET, REP, CONTINUE, 0) == *(saTable.at("A").at("t").begin()));
		CHECK(SaCell(RET, REP, CONTINUE, 3) == *(saTable.at("D").at("m").begin()));
		CHECK(SaCell(RET, REP, CONTINUE, 1) == *(saTable.at("B").at("t").begin()));
		CHECK(SaCell(RET, REP, CONTINUE, 2) == *(saTable.at("C").at("l").begin()));
		CHECK(SaCell(ADV, POP, CONTINUE, 0) == *(saTable.at("m").at("m").begin()));
		CHECK(SaCell(ADV, POP, CONTINUE, 0) == *(saTable.at("l").at("l").begin()));
		CHECK(SaCell(ADV, POP, CONTINUE, 0) == *(saTable.at("t").at("t").begin()));
		CHECK(SaCell(INPUT_NOP, STACK_NOP, ACCEPT, 0) == *(saTable.at("$").at("$").begin()));
	}
	SECTION("PARSE") {
		REQUIRE(grammar.buildSATable());
		iss.clear();
		iss.str("t l");
		CHECK(grammar.parse(iss));
		iss.clear();
		iss.str("l t");
		CHECK_FALSE(grammar.parse(iss));
		iss.clear();
		iss.str("m");
		CHECK_FALSE(grammar.parse(iss));
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
	SECTION("SATABLE") {
		REQUIRE(grammar.buildSATable());
		const std::map<std::string, std::map<std::string, std::set<SaCell>>>& saTable = grammar.getSaTable();
		CHECK(SaCell(RET, REP, CONTINUE, 0) == *(saTable.at("A").at("l").begin()));
		CHECK(SaCell(RET, REP, CONTINUE, 2) == *(saTable.at("A'").at("r").begin()));
		CHECK(SaCell(RET, REP, CONTINUE, 1) == *(saTable.at("A'").at("l").begin()));
		CHECK(SaCell(RET, REP, CONTINUE, 4) == *(saTable.at("R").at("r").begin()));
		CHECK(SaCell(ADV, POP, CONTINUE, 0) == *(saTable.at("r").at("r").begin()));
		CHECK(SaCell(ADV, POP, CONTINUE, 0) == *(saTable.at("l").at("l").begin()));
		CHECK(SaCell(INPUT_NOP, STACK_NOP, ACCEPT, 0) == *(saTable.at("$").at("$").begin()));
	}
	SECTION("PARSE") {
		REQUIRE(grammar.buildSATable());
		iss.clear();
		iss.str("l l r r");
		CHECK(grammar.parse(iss));
		iss.clear();
		iss.str("l l r r r");
		CHECK_FALSE(grammar.parse(iss));
		iss.clear();
		iss.str("");
		CHECK_FALSE(grammar.parse(iss));
	}
}