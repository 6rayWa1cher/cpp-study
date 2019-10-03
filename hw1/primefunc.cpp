//
// Created by Konstantin Grigoriev on 12/09/2019.
//

#include <iostream>
#include "primefunc.h"

bool isPrime(const int num) {
    if (num <= 1) return false;
    for (int i = 2; i < num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

void printPrimes(const int m) {
    bool firstPrint = true;
    for (int candidate = 2; candidate <= m; ++candidate) {
        if (isPrime(candidate)) {
            if (firstPrint) {
                std::cout << candidate;
                firstPrint = false;
            } else {
                std::cout << ", " << candidate;
            }
        }
    }
    std::cout << std::endl;
}

void printPrimesRev(const int m) {
    bool firstPrint = true;
    for (int candidate = m; candidate >= 2; --candidate) {
        if (isPrime(candidate)) {
            if (firstPrint) {
                std::cout << candidate;
                firstPrint = false;
            } else {
                std::cout << ", " << candidate;
            }
        }
    }
    std::cout << std::endl;
}