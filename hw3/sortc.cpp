//
// Created by 6rayWa1cher on 03.10.2019.
//

#include "sortc.h"

void swap(int &a, int &b) {
    int z = a;
    a = b;
    b = z;
}

void bubbleSort(std::vector<int> &vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        for (size_t j = 0; j + 1 < vector.size(); ++j) {
            if (vector.at(j) > vector.at(j + 1)) {
                swap(vector[j], vector[j + 1]);
            }
        }
    }
}
