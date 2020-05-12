//
// Created by 6rayWa1cher on 07.05.2020.
//

#include "firstfollow.h"
#include "../hw3/stringops.h"
#include <iostream>
#include <utility>
#include <sstream>
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
		const size_t arrowPosition = line.find(" -> ");
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
		enumeratedRules.emplace_back(leftPart, rightPartSplit);
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

std::set<std::string> chain(const std::set<std::string>& set1, const std::set<std::string>& set2) {
	std::set<std::string> out;
	std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(out, out.begin()));
	return out;
}

std::vector<std::string> chain(const std::vector<std::string>& vector1, const std::vector<std::string>& vector2) {
	std::vector<std::string> out;
	out.insert(out.begin(), vector1.begin(), vector1.end());
	out.insert(out.end(), vector2.begin(), vector2.end());
	return out;
}

bool Grammar::buildSATable() {
	for (const std::string& word : chain(chain(nonTerminals, terminals), std::set<std::string>{"$"})) {
		for (const std::string& term : chain(terminals, std::set<std::string>{"$"})) {
			saTable.emplace(word, std::map<std::string, std::set<SaCell>>());
			saTable[word].emplace(term, std::set<SaCell>());
		}
	}
	for (int i = 0; i < enumeratedRules.size(); ++i) {
		const auto& pair = enumeratedRules[i];
		const std::string& leftPart = pair.first;
		const std::vector<std::string> rightPart = pair.second;
		const std::set<std::string> rightPartFirst = first(rightPart);
		const std::set<std::string> firstTerminals = filtered(rightPartFirst, [this](const std::string& w) {
			return isTerminal(w);
		});
		for (const std::string& terminal : firstTerminals) {
			saTable[leftPart][terminal].emplace(
					SaCell(SaCellInputOperation::RET, SaCellStackOperation::REP, SaCellReturn::CONTINUE, i));
		}
		if (rightPartFirst.find(EPSILON) != rightPartFirst.end()) {
			for (const std::string& term : follow(leftPart)) {
				saTable[leftPart][term].emplace(
						SaCell(SaCellInputOperation::RET, SaCellStackOperation::REP, SaCellReturn::CONTINUE, i));
			}
		}
	}
	for (const std::string& term : terminals) {
		saTable[term][term].emplace(
				SaCell(SaCellInputOperation::ADV, SaCellStackOperation::POP, SaCellReturn::CONTINUE, 0));
	}
	saTable["$"]["$"].emplace(
			SaCell(SaCellInputOperation::INPUT_NOP, SaCellStackOperation::STACK_NOP, SaCellReturn::ACCEPT, 0));
	bool isLL1 = true;
	for (auto& pair1 : saTable) {
		for (auto& pair2 : pair1.second) {
			std::set<SaCell>& cells = pair2.second;
			if (cells.size() >= 2) {
				isLL1 = false;
			}
//			else if (cells.empty()) {
//				cells.emplace(SaCell(SaCellInputOperation::INPUT_NOP, SaCellStackOperation::STACK_NOP, SaCellReturn::REJECT, 0));
//			}
		}
	}
	return isLL1;
}

void printSpaceNTimes(std::ostream& stream, unsigned int n) {
	for (int i = 0; i < n; ++i) stream << ' ';
}

void Grammar::printSATable(std::ostream& stream) {
	for (int i = 0; i < enumeratedRules.size(); ++i) {
		const std::string& leftPart = enumeratedRules[i].first;
		std::stringstream rightPartConcat;
		for (const std::string& item : enumeratedRules[i].second) {
			rightPartConcat << item << ' ';
		}
		stream << i + 1 << ". " << leftPart << " -> " << rightPartConcat.str() << std::endl;
	}
	stream << std::endl;
	std::map<std::string, unsigned int> columnWidth;
	unsigned int firstColumnWidth = 0;
	for (const auto& pair1 : saTable) {
		for (const auto& pair2 : pair1.second) {
			const std::string& columnName = pair2.first;
			if (columnWidth.find(columnName) == columnWidth.end()) {
				columnWidth.emplace(columnName, std::max(columnName.size(), (unsigned int) 4));
			}
			unsigned int cellSize = 0;
			for (const auto& item : pair2.second) {
				cellSize += std::string(item).size();
			}
			columnWidth[columnName] = std::max(columnWidth[columnName], cellSize);
		}
	}
	for (const auto& pair1 : saTable) {
		firstColumnWidth = std::max(firstColumnWidth, pair1.first.size());
	}
	unsigned int lineWidth = firstColumnWidth + 1;
	printSpaceNTimes(stream, firstColumnWidth + 1);
	std::vector<std::string> columnOrder;
	columnOrder.insert(columnOrder.begin(), terminals.begin(), terminals.end());
	columnOrder.emplace_back("$");
	for (const std::string& columnName : columnOrder) {
		unsigned int thisColumnWidth = columnWidth[columnName];
		lineWidth += thisColumnWidth + 1;
		stream << columnName;
		printSpaceNTimes(stream, thisColumnWidth - columnName.size() + 1);
	}
	stream << std::endl;
	for (int i = 0; i < lineWidth; ++i) stream << '-';
	stream << std::endl;
	std::vector<std::string> rowOrder;
	for (const auto& pair : enumeratedRules) {
		if (std::find(rowOrder.begin(), rowOrder.end(), pair.first) == rowOrder.end()) {
			rowOrder.emplace_back(pair.first);
		}
	}
	rowOrder.insert(rowOrder.end(), terminals.begin(), terminals.end());
	rowOrder.emplace_back("$");
	for (const std::string& rowName : rowOrder) {
		const auto& pair1 = saTable.at(rowName);
		stream << rowName;
		printSpaceNTimes(stream, firstColumnWidth - rowName.size() + 1);
		for (const std::string& columnName : columnOrder) {
			const std::map<std::string, std::set<SaCell>>& tableRow = pair1;
			bool first = true;
			unsigned int size = 0;
			for (const SaCell& item : tableRow.at(columnName)) {
				if (!first) {
					stream << ';';
					size += 1;
				}
				stream << std::string(item);
				size += std::string(item).size();
				first = false;
			}
			printSpaceNTimes(stream, columnWidth[columnName] - size + 1);
		}
		stream << std::endl;
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

SaCell::operator std::string() const {
	std::stringstream ss;
	bool useComma = false;
	switch (this->stackOperation) {
		case STACK_NOP:
			break;
		case REP:
			useComma = true;
			ss << "R" << this->stackOperationValue + 1;
			break;
		case POP:
			useComma = true;
			ss << "P";
			break;
	}
	switch (this->inputOperation) {
		case INPUT_NOP:
			break;
		case RET:
			if (useComma) ss << ',';
			ss << "R";
			useComma = true;
			break;
		case ADV:
			if (useComma) ss << ',';
			ss << "A";
			useComma = true;
			break;
	}
	switch (this->saCellReturn) {
		case CONTINUE:
			break;
		case ACCEPT:
			if (useComma) ss << ',';
			ss << "Accept";
			break;
		case REJECT:
			break;
	}
	return ss.str();
}

SaCell::SaCell(const SaCellInputOperation inputOperation, const SaCellStackOperation stackOperation,
               const SaCellReturn saCellReturn, const int stackOperationValue) : inputOperation(inputOperation),
                                                                                 stackOperation(stackOperation),
                                                                                 saCellReturn(saCellReturn),
                                                                                 stackOperationValue(
		                                                                                 stackOperationValue) {}

bool SaCell::operator<(const SaCell& rhs) const {
	if (inputOperation < rhs.inputOperation)
		return true;
	if (rhs.inputOperation < inputOperation)
		return false;
	if (stackOperation < rhs.stackOperation)
		return true;
	if (rhs.stackOperation < stackOperation)
		return false;
	if (saCellReturn < rhs.saCellReturn)
		return true;
	if (rhs.saCellReturn < saCellReturn)
		return false;
	return stackOperationValue < rhs.stackOperationValue;
}

bool SaCell::operator>(const SaCell& rhs) const {
	return rhs < *this;
}

bool SaCell::operator<=(const SaCell& rhs) const {
	return !(rhs < *this);
}

bool SaCell::operator>=(const SaCell& rhs) const {
	return !(*this < rhs);
}
