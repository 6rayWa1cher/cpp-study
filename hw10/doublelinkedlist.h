//
// Created by 6rayWa1cher on 08.04.2020.
//

#ifndef EDUSANDBOX_DOUBLELINKEDLIST_H
#define EDUSANDBOX_DOUBLELINKEDLIST_H

#include <memory>

namespace CatLinkedList {
    struct Node2 {
        std::shared_ptr<Node2> prev;
        std::shared_ptr<Node2> next;
        int data;
    };


    std::shared_ptr<Node2> createDoubleLinkedList();

    void addElement(const std::shared_ptr<Node2> &head, int data);

    std::string to_str(const std::shared_ptr<Node2> &head, const std::string &delimiter = "");

    void swapElements(std::shared_ptr<Node2> prev);

    std::shared_ptr<Node2> addElementAfter(const std::shared_ptr<Node2> &prev, int data);

    std::shared_ptr<Node2> push_back(const std::shared_ptr<Node2> &head, const std::shared_ptr<Node2> &last);

    template<class InputIt>
    std::shared_ptr<Node2> insertSort(InputIt first, InputIt last) {
        std::shared_ptr<Node2> head = createDoubleLinkedList();
        std::shared_ptr<Node2> curr_out = head;
        for (InputIt curr = first; curr != last; curr++) {
            curr_out = addElementAfter(curr_out, *curr);
            curr_out = push_back(head, curr_out);
        }
        return head;
    }

}
#endif //EDUSANDBOX_DOUBLELINKEDLIST_H
