//
// Created by 6rayWa1cher on 04.02.2020.
//

#include "dispersion.h"

double calculateDispersion(std::vector<int>::iterator start, std::vector<int>::iterator end) {
	if (start == end) {
		return 0;
	}
	double subtrahend = 0;
	int elementCount = 0;
	for (auto i = start; i != end; i++, elementCount++) {
		subtrahend += *i;
	}
	subtrahend /= elementCount;
	double subresult = 0;
	for (auto i = start; i != end; i++) {
		subresult += (*i - subtrahend) * (*i - subtrahend);
	}
	return subresult / elementCount;
}
