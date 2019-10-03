//
// Created by Konstantin Grigoriev on 13/09/2019.
//

#include "vectorfunc.h"

int minIndex(std::vector<int> vector) {
    int min = vector.at(0);
    int min_index = 0;
    int vectorNumber;
    for (size_t i = 0; i < vector.size(); ++i) {
        vectorNumber = vector.at(i);
        if (min > vectorNumber) {
            min = vectorNumber;
            min_index = i;
        }
    }
    return min_index;
}

std::vector<int> calcExpress(int n) {
    if (n <= 0) {
        std::vector<int> empty(0);
        return empty;
    }
    std::vector<int> out;
    for (int i = 1; i <= n; ++i) {
        int val = 0;
        for (int j = 0; j <= i; ++j) {
            val += (i + j) * (i + j);
        }
        out.push_back(val);
    }
    return out;
}

bool isPalindrome(std::vector<int> vector) {
    if (vector.empty()) {
        return true;
    }
    for (size_t i = 0, j = vector.size() - 1; i <= j; ++i, --j) {
        if (vector.at(i) != vector.at(j)) {
            return false;
        }
    }
    return true;
}

std::vector<int> calcDnaStats(std::vector<char> vector) {
    int currG = 0, currC = 0;
    std::vector<int> out(vector.size());
    for (size_t i = 0; i < vector.size(); ++i) {
        out[i] = currG - currC;
        switch (vector.at(i)) {
            case 'G':
                currG++;
                break;
            case 'C':
                currC++;
                break;
            default:
                break;
        }
    }
    return out;
}

