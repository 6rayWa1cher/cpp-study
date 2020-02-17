//
// Created by 6rayWa1cher on 04.02.2020.
//

#include "sequence.h"

int getNumberOfElementsInSeq(std::vector<int>::iterator left, std::vector<int>::iterator end) {
	auto iter = left;
	int val = *left;
	int out = 0;
	while (iter != end && *iter == val) {
		iter++;
		out++;
	}
	return out;
}

std::vector<int> getBorderDistances(std::vector<int> v) {
	std::vector<int> out(v.size());
	auto curr = v.begin();
	auto end = v.end();
	int seqStartPos = 0;
	int leftInSeq = -1;
	double midElementPos = 0.0;
	for (int i = 0; i < v.size(); i++, curr++, leftInSeq--) {
		if (leftInSeq < 0) {
			seqStartPos = i;
			leftInSeq = getNumberOfElementsInSeq(curr, end) - 1;
			midElementPos = (seqStartPos + (double) leftInSeq + seqStartPos) / 2.0;
		}
		if (i < midElementPos) {
			out[i] = i - seqStartPos;
		} else {
			out[i] = leftInSeq;
		}
	}
	return out;
}
