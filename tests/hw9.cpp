//
// Created by 6rayWa1cher on 10.03.2020.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw9/persons.h"
#include "../hw9/list.h"
#include "../hw9/hw9_utils.h"

TEST_CASE("Search for address test", "[findAddress]") {
	std::shared_ptr<Node> list = createList();

	addElement(list, std::make_shared<TGUPerson>("Ivanov", "Petrova 1-23"));

	addElement(list, std::make_shared<TGUPerson>("Petrov", "Ivanova 4-5"));

	SECTION("In list") {
		CHECK("Petrova 1-23" == findAddress(list, "Ivanov"));
	}

	SECTION("Not in list") {
		CHECK(findAddress(list, "McCloud").empty());
	}
}

TEST_CASE("IntList", "[IntNode]") {
	std::shared_ptr<IntNode> list = createIntList();

	addElement(list, 42);
	addElement(list, 15);
	std::ostringstream ss;
	ss << list;
	REQUIRE("1542" == ss.str());
}

TEST_CASE("Lists equal check", "[listCompare]") {
	SECTION("Both empty") {
		std::shared_ptr<IntNode> l1 = createIntList(), l2 = createIntList();
		CHECK(listCompare(l1, l2));
	} SECTION("One empty, other not empty") {
		std::shared_ptr<IntNode> l1 = createIntList(), l2 = createIntList();
		addElement(l1, 42);
		CHECK_FALSE(listCompare(l1, l2));
	} SECTION("Both not empty") {
		std::shared_ptr<IntNode> l1 = createIntList(), l2 = createIntList();
		addElement(l1, 42);
		addElement(l2, 42);
		REQUIRE(listCompare(l1, l2));
		addElement(l1, 1337);
		REQUIRE_FALSE(listCompare(l1, l2));
	}
}

TEST_CASE("Swap elements", "[swapElements]") {
	SECTION("Incorrect swaps") {
		std::shared_ptr<IntNode> list = createIntList();
		swapElements(list);
		addElement(list, 2);
		swapElements(list);
		addElement(list, 1);
		std::ostringstream ss;
		ss << list;
		REQUIRE("12" == ss.str());
	} SECTION("Swap without tail") {
		std::shared_ptr<IntNode> list = createIntList();
		addElement(list, 2);
		addElement(list, 1);
		swapElements(list);
		std::ostringstream ss;
		ss << list;
		REQUIRE("21" == ss.str());
	} SECTION("Swap with tail") {
		std::shared_ptr<IntNode> list = createIntList();
		addElement(list, 3);
		addElement(list, 2);
		addElement(list, 1);
		swapElements(list);
		std::ostringstream ss;
		ss << list;
		REQUIRE("213" == ss.str());
	}
}

TEST_CASE("Bubble sort", "[bubbleSort]") {
	SECTION("No work") {
		std::shared_ptr<IntNode> list = createIntList();
		bubbleSort(list);
		addElement(list, 2);
		bubbleSort(list);
		addElement(list, 1);
		std::ostringstream ss;
		ss << list;
		REQUIRE("12" == ss.str());
	} SECTION("Sorting") {
		std::shared_ptr<IntNode> list = createIntList();
		addElement(list, 1);
		addElement(list, 2);
		addElement(list, 3);
		std::ostringstream ss;
		ss << list;
		REQUIRE("321" == ss.str());
		ss.str("");
		ss.clear();
		bubbleSort(list);
		ss << list;
		REQUIRE("123" == ss.str());
	}
}