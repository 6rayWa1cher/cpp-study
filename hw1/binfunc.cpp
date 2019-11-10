//
// Created by Konstantin Grigoriev on 12/09/2019.
//

#include <iostream>
#include "binfunc.h"

void printBinary(int m) {
	unsigned int number = m;
	std::string sb;
	while (number != 0) {
		sb = std::to_string(number & 0b1u) + sb; // NOLINT(performance-inefficient-string-concatenation)
		number >>= 1u;
	}
	std::cout << sb << std::endl;
}

