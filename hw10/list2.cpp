//
// Created by 6rayWa1cher on 07.04.2020.
//

#include <sstream>
#include "list2.h"

std::string to_str(const std::shared_ptr<IntNode> &head, const std::string &delimiter = "") {
    std::ostringstream ss;
    for (std::shared_ptr<IntNode> current = head->next; current != nullptr; current = current->next) {
        ss << current->data;
        if (current->next != nullptr) {
            ss << delimiter;
        }
    }
    return ss.str();
}

int length(const std::shared_ptr<IntNode> &head) {
    int i = 0;
    for (std::shared_ptr<IntNode> curr = head->next; curr != nullptr; curr = curr->next, i++);
    return i;
}

void reverse(const std::shared_ptr<IntNode> &head) {
    int list_length = length(head);
    for (int i = 0; i < list_length; i++) {
        std::shared_ptr<IntNode> prev = head;
        for (int j = 0; j + i + 1 < list_length; j++) {
            swapElements(prev);
            prev = prev->next;
        }
    }
}

void removePart(const std::shared_ptr<IntNode> &list1, const std::shared_ptr<IntNode> &list2) {
    for (std::shared_ptr<IntNode> prev1 = list1, start1 = list1->next;
         start1 != nullptr; start1 = start1->next, prev1 = prev1->next) {
        bool exited = false;
        std::shared_ptr<IntNode> prev1_ = start1, curr1_ = start1, curr2 = list2->next;
        for (; curr1_ && curr2; curr1_ = curr1_->next, curr2 = curr2->next, prev1_ = prev1_->next) {
            if (curr1_->data != curr2->data) {
                exited = true;
                break;
            }
        }
        if (!(!curr1_ && curr2) && !exited && prev1_ != start1) {
            prev1->next = curr1_;
            break;
        }
    }
}

