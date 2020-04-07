//
// Created by 6rayWa1cher on 07.04.2020.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../hw9/list.h"
#include "../hw10/list2.h"
#include "../hw10/doublelinkedlist.h"

TEST_CASE("Reverse a list", "[reverse]") {
    std::shared_ptr<IntNode> list = createIntList();
    SECTION("Empty") {
        CHECK_NOTHROW(reverse(list));
    }
    SECTION("Test 1") {
        for (int i = 0; i < 5; ++i) {
            addElement(list, 5 - i);
        }
        std::ostringstream ss;
        ss << list;
        REQUIRE("12345" == ss.str());
        reverse(list);
        ss.str("");
        ss.clear();
        ss << list;
        CHECK("54321" == ss.str());
    }
}

TEST_CASE("Remove the part", "[removePart]") {
    SECTION("Empty removal part") {
        std::shared_ptr<IntNode> list = createIntList();
        addElement(list, 3);
        addElement(list, 2);
        addElement(list, 1);
        std::ostringstream ss;
        ss << list;
        REQUIRE("123" == ss.str());
        std::shared_ptr<IntNode> remover = createIntList();
        CHECK_NOTHROW(removePart(list, remover));
        ss.str("");
        ss.clear();
        ss << list;
        CHECK("123" == ss.str());
    }
    SECTION("Test #1") {
        std::shared_ptr<IntNode> list = createIntList();
        for (int i = 0; i < 5; ++i) {
            addElement(list, 5 - i);
        }
        std::ostringstream ss;
        ss << list;
        REQUIRE("12345" == ss.str());
        std::shared_ptr<IntNode> remover = createIntList();
        for (int i = 3; i > 1; --i) {
            addElement(remover, i);
        }
        ss.str("");
        ss.clear();
        ss << remover;
        REQUIRE("23" == ss.str());
        CHECK_NOTHROW(removePart(list, remover));
        ss.str("");
        ss.clear();
        ss << list;
        CHECK("145" == ss.str());
        ss.str("");
        ss.clear();
        ss << remover;
        CHECK("23" == ss.str());
    }
    SECTION("Test #2") {
        std::shared_ptr<IntNode> list = createIntList();
        for (int i = 0; i < 5; ++i) {
            addElement(list, 5 - i);
        }
        std::ostringstream ss;
        ss << list;
        REQUIRE("12345" == ss.str());
        std::shared_ptr<IntNode> remover = createIntList();
        for (int i = 9; i > 1; --i) {
            addElement(remover, i);
        }
        ss.str("");
        ss.clear();
        ss << remover;
        REQUIRE("23456789" == ss.str());
        CHECK_NOTHROW(removePart(list, remover));
        ss.str("");
        ss.clear();
        ss << list;
        CHECK("12345" == ss.str());
        ss.str("");
        ss.clear();
        ss << remover;
        CHECK("23456789" == ss.str());
    }
}

TEST_CASE("Insert sort CatLinkedList", "[CatLinkedList::insertSort]") {
    SECTION("Empty list") {
        std::vector<int> list = {};
        std::shared_ptr<CatLinkedList::Node2> head = CatLinkedList::insertSort(list.cbegin(), list.cend());
        CHECK(CatLinkedList::to_str(head).empty());
    }
    SECTION("Test #1") {
        std::vector<int> list = {5, 4, 3, 2, 1};
        std::shared_ptr<CatLinkedList::Node2> head = CatLinkedList::insertSort(list.cbegin(), list.cend());
        CHECK("12345" == CatLinkedList::to_str(head));
    }
    SECTION("Test #2") {
        std::vector<int> list = {7, 4, 8, 10, 54};
        std::shared_ptr<CatLinkedList::Node2> head = CatLinkedList::insertSort(list.cbegin(), list.cend());
        CHECK("4 7 8 10 54" == CatLinkedList::to_str(head, " "));
    }
}