//
// Created by Konstantin Grigoriev on 27/09/2019.
//

#include "numcast.h"
#include <math.h>

const int max_num_system = 26 + 10;

std::string numCast(int num, int to_system) {
	if (to_system >= max_num_system) {
		return std::string();
	}
	std::string out;
	unsigned int raw = num >= 0 ? num : -num;
	unsigned int n;
	while (raw > 0) {
		n = raw % to_system;
		if (n < 10) {
			out = std::to_string(n) + out;
		} else {
			out = static_cast<char>('A' + (n - 10)) + out;
		}
		raw = raw / to_system;
	}
	out = (num < 0 ? "-" : "") + out;
	return out;
}

int numCast(const std::string num, const int from_system) {
	int out = 0;
	unsigned degree = num.size() - 1;
	for (char c : num) {
		if (c == '-') {

		} else if (c <= '9') {
			out += (c - '0') * static_cast<int>(pow(from_system, degree));
		} else {
			out += (c - 'A' + 10) * static_cast<int>(pow(from_system, degree));
		}
		--degree;
	}
	if (num[0] == '-') {
		out *= -1;
	}
	return out;
}
