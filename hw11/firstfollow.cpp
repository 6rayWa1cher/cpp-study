//
// Created by 6rayWa1cher on 07.05.2020.
//

#include "firstfollow.h"
#include "../hw3/stringops.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>

Grammar::Grammar() = default;

Grammar::~Grammar() = default;

bool Grammar::loadGrammar(std::istream& stream) {
	// Вставляем код задачи 5.1.1
	// 1. считываем грамматику и записываем ее в grammar
	// 2. если считать не удалось, то возвращаем false
	std::string line;
	bool first = true;
	int i = 1;
	while (std::getline(stream, line)) {
		if (line.empty()) continue;
		const unsigned int arrowPosition = line.find(" -> ");
		if (arrowPosition == std::string::npos) {
			std::cerr << "No error in line no." << i << " :" << line;
			return false;
		}
		std::string leftPart = line.substr(0, arrowPosition);
		std::string rightPart = line.substr(arrowPosition + 4);
		std::vector<std::string> rightPartSplit = split(rightPart, ' ');
		if (grammar.find(leftPart) == grammar.end()) {
			grammar.emplace(leftPart, std::vector<std::vector<std::string>>());
			nonTerminals.insert(leftPart);
		}
		std::vector<std::vector<std::string>>& collectionOfRightParts = grammar[leftPart];
		collectionOfRightParts.push_back(rightPartSplit);
		if (first) {
			startNonTerminal = leftPart;
			first = false;
		}
		++i;
	}
	for (const auto& pair : grammar) {
		for (const auto& rightPart : pair.second) {
			for (const std::string& word : rightPart) {
				if (nonTerminals.find(word) == nonTerminals.end() && word != EPSILON) {
					terminals.insert(word);
				}
			}
		}
	}
	if (!initFirstWithTerminalsAndEpsilon()) return false;
	if (!initFirstWithNonTerminals()) return false;
	if (!calculateFollow()) return false;

	return true;
}

std::ostream& operator<<(std::ostream& stream, const Grammar& g) {
	stream << "Start: " << g.getStartNonTerminal() << std::endl;
	for (const auto& pair : g.getGrammar()) {
		for (const auto& rightPart : pair.second) {
			stream << pair.first << " -> ";
			for (auto it = rightPart.begin(); it != rightPart.end(); it++) {
				stream << *it;
				if (it + 1 != rightPart.end()) {
					stream << " ";
				}
			}
			stream << std::endl;
		}
	}
	return stream;
}


bool Grammar::initFirstWithTerminalsAndEpsilon() {
	// Вставляем код задачи 5.1.2
	// Если все в порядке, возвращаем true, иначе - false
	for (const std::string& term : terminals) {
		firstForG.emplace(term, std::set<std::string>());
		firstForG[term].insert(term);
	}
	for (const std::string& nonTerm : nonTerminals) {
		firstForG.emplace(nonTerm, std::set<std::string>());
	}
	const std::vector<std::string> epsilonRightPart = {EPSILON};
	for (const auto& pair : grammar) {
		for (const auto& rightPart : pair.second) {
			if (rightPart == epsilonRightPart) {
				firstForG[pair.first].insert(EPSILON);
			}
		}
	}
	return true;
}

void Grammar::printFirst(std::ostream& stream) {
	for (auto& pair : firstForG) {
		if (pair.second.empty()) continue;
		stream << pair.first << " = " << pair.second;
	}
}

std::vector<std::string>
filtered(const std::vector<std::string>& str, const std::function<bool(std::string)>& predicate) {
	std::vector<std::string> result(str.size());
	for (const std::string& word: str) {
		if (predicate(word)) {
			result.push_back(word);
		}
	}
	return result;
}

std::set<std::string> filtered(const std::set<std::string>& str, const std::function<bool(std::string)>& predicate) {
	std::set<std::string> result;
	for (const std::string& word: str) {
		if (predicate(word)) {
			result.insert(word);
		}
	}
	return result;
}

std::set<std::string> Grammar::first(const std::vector<std::string>& str) {
	std::set<std::string> result;

	if (str == std::vector<std::string>{EPSILON}) {
		result.insert(EPSILON);
	} else if (str.size() == 1 && str[0] != EPSILON) {
		return firstForG[str[0]];
	} else {
		size_t i = 0;
		for (const std::string& word : str) {
			std::set<std::string> f = first(std::vector<std::string>{word});
			std::set<std::string> fFiltered = filtered(f, [this](const std::string& w) {
				return isTerminal(w);
			});
			result.insert(fFiltered.begin(), fFiltered.end());
			if (i + 1 == str.size() && f.find(EPSILON) != f.end()) {
				result.insert(EPSILON);
				break;
			}
			if (f.find(EPSILON) == f.end()) {
				break;
			}
			++i;
		}
	}

	return result;
}

std::set<std::string> difference_new(const std::set<std::string>& big, const std::set<std::string>& breaker) {
	std::set<std::string> result;
	std::set_difference(big.begin(), big.end(), breaker.begin(), breaker.end(),
	                    std::inserter(result, result.begin()));
	return result;
}

std::set<std::string> operator-(const std::set<std::string>& big, const std::set<std::string>& breaker) {
	return difference_new(big, breaker);
}

bool Grammar::initFirstWithNonTerminals() {
	// Вставляем код задачи 5.1.4
	// Если все в порядке, возвращаем true, иначе - false
	bool changed = true;
	std::vector<std::string> epsilonRightPart{EPSILON};
	while (changed) {
		changed = false;
		for (const auto& pair : grammar) {
			for (const auto& rightPart : pair.second) {
				const std::string& leftPart = pair.first;
				if (rightPart == epsilonRightPart) continue;
				std::set<std::string> f = first(rightPart);
				std::set<std::string>& set = firstForG[leftPart];
				std::set<std::string> diffResult = f - set;
				if (!diffResult.empty()) {
					set.insert(f.begin(), f.end());
					changed = true;
				}
			}
		}
	}
	return true;
}

bool Grammar::initFollow() {
	// Вставляем код задачи 5.2.1
	// Если все в порядке, возвращаем true, иначе - false
	for (const std::string& leftPart : nonTerminals) {
		followForG.emplace(leftPart, std::set<std::string>());
	}
	followForG[startNonTerminal].insert("$");
	return true;
}

bool Grammar::calculateFollow() {
	initFollow();

	bool changed = true;
	std::vector<std::string> betaBuffer(16);
	while (changed) {
		changed = false;
		for (const auto& pair : grammar) {
			const std::string& leftPart = pair.first;
			for (const std::vector<std::string>& rightPart : pair.second) {
				for (auto it = rightPart.begin(); it != rightPart.end(); ++it) {
					const std::string& word = *it;
					if (!isNonTerminal(word)) continue;
					betaBuffer.clear();
					std::copy(it + 1, rightPart.end(), std::inserter(betaBuffer, betaBuffer.begin()));
					const std::set<std::string> firstSet = first(betaBuffer);
					const std::set<std::string> newFirst = firstSet - std::set<std::string>{EPSILON};
					if (!(newFirst - followForG[word]).empty()) {
						changed = true;
					}
					followForG[word].insert(newFirst.begin(), newFirst.end());
					if (!changed && (betaBuffer.empty() || firstSet.find(EPSILON) != firstSet.end())) {
						const std::set<std::string>& newFollow = followForG[leftPart];
						if (!(newFollow - followForG[word]).empty()) {
							changed = true;
						}
						followForG[word].insert(newFollow.begin(), newFollow.end());
					}
				}
			}
		}
	}

	return true;
}

std::set<std::string> Grammar::follow(const std::string& word) {
	if (!isNonTerminal(word)) {
		return std::set<std::string>();
	}
	return followForG[word];
}

const std::string& Grammar::getStartNonTerminal() const {
	return startNonTerminal;
}

const std::map<std::string, std::vector<std::vector<std::string>>>& Grammar::getGrammar() const {
	return grammar;
}

const std::map<std::string, std::set<std::string>>& Grammar::getFirstForG() const {
	return firstForG;
}

const std::map<std::string, std::set<std::string>>& Grammar::getFollowForG() const {
	return followForG;
}

bool Grammar::isTerminal(const std::string& word) {
	if (word == EPSILON) return false;
	return terminals.find(word) != terminals.end();
}

bool Grammar::isNonTerminal(const std::string& word) {
	if (word == EPSILON) return false;
	return nonTerminals.find(word) != nonTerminals.end();
}

void Grammar::printFollow(std::ostream& stream) {
	for (const auto& pair : followForG) {
		const std::string& leftPart = pair.first;
		const std::set<std::string>& rightPart = pair.second;
		stream << leftPart << " = " << rightPart;
	}
}

std::ostream& operator<<(std::ostream& stream, const std::set<std::string>& res) {
	auto p = res.begin();
	stream << "[";
	while (p != res.end()) {
		stream << p->c_str();
		p++;
		if (p != res.end()) stream << " ";
	}
	stream << "]" << std::endl;

	return stream;
}