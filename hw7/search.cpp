//
// Created by 6rayWa1cher on 04.02.2020.
//

#include "search.h"
#include <cmath>
#include <limits>

bool approxEquals(double a, double b) {
	return abs(a - b) < 0.0000001;
}

double searchNearest(std::vector<double>::iterator start, std::vector<double>::iterator end, double r) {
	double currentReturn = std::numeric_limits<double>::infinity();
	for (auto i = start; i != end; i++) {
		double curr = *i;
		if (abs(curr - r) < abs(currentReturn - r) && !approxEquals(curr, r)) {
			currentReturn = curr;
		}
	}
	return currentReturn;
}
