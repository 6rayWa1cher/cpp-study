//
// Created by 6rayWa1cher on 08.04.2020.
//

#include <memory>
#include <sstream>
#include <iostream>
#include "doublelinkedlist.h"

namespace CatLinkedList {
    std::shared_ptr<Node2> push_back(const std::shared_ptr<Node2> &head, const std::shared_ptr<Node2> &last) {
        std::shared_ptr<Node2> curr = last;
        std::shared_ptr<Node2> out = nullptr;
        while (curr != head && curr->prev != head && curr->data < curr->prev->data) {
            if (out == nullptr) {
                out = last->prev;
            }
            swapElements(curr->prev->prev);
        }
        if (out == nullptr) {
            return last;
        } else {
            return out;
        }
    }

    std::shared_ptr<Node2> createDoubleLinkedList() {
        return std::make_shared<Node2>();
    }

    void addElement(const std::shared_ptr<Node2> &head, int data) {
        std::shared_ptr<Node2> newElem = std::make_shared<Node2>();
        newElem->next = head->next;
        newElem->data = data;
        head->next = newElem;
        newElem->prev = head;
        head->next = newElem;
    }

    std::shared_ptr<Node2> addElementAfter(const std::shared_ptr<Node2> &prev, int data) {
        std::shared_ptr<Node2> newElem = std::make_shared<Node2>();
        newElem->data = data;
        newElem->next = prev->next;
        if (newElem->next) newElem->next->prev = newElem;
        newElem->prev = prev;
        prev->next = newElem;
        return newElem;
    }

    void swapElements(std::shared_ptr<Node2> prev) {
        if (!prev) return;
        if (!(prev->next)) return;
        if (!(prev->next->next)) return;
        std::shared_ptr<Node2> e1 = prev->next, e2 = e1->next, tail = e2->next;
        // prev <-> e1 <-> e2 <-> tail
        // to
        // prev <-> e2 <-> e1 <-> tail
        prev->next = e2;
        e2->next = e1;
        e1->next = tail;
        if (tail) tail->prev = e1;
        e1->prev = e2;
        e2->prev = prev;
    }

    std::string to_str(const std::shared_ptr<Node2> &head, const std::string &delimiter) {
        std::ostringstream ss;
        for (std::shared_ptr<Node2> current = head->next; current != nullptr; current = current->next) {
            ss << current->data;
            if (current->next != nullptr) {
                ss << delimiter;
            }
        }
        return ss.str();
    }
}