//
// Created by 6rayWa1cher on 07.05.2020.
//

#ifndef EDUSANDBOX_FIRSTFOLLOW_H
#define EDUSANDBOX_FIRSTFOLLOW_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <utility>

const std::string EPSILON = "e";

std::ostream& operator<<(std::ostream& stream, const std::set<std::string>& terminals);

class NotLL1Grammar : std::exception {
	std::string stackWord;
	std::string inputTerminal;

	explicit operator std::string() const;

public:
	NotLL1Grammar(std::string stackWord, std::string inputTerminal);
};

enum SaCellStackOperation {
	STACK_NOP, REP, POP
};

enum SaCellInputOperation {
	INPUT_NOP, RET, ADV
};

enum SaCellReturn {
	CONTINUE, ACCEPT, REJECT
};

class SaCell {
public:
	SaCellInputOperation inputOperation = INPUT_NOP;
	SaCellStackOperation stackOperation = STACK_NOP;
	SaCellReturn saCellReturn = REJECT;
	int stackOperationValue;

	SaCell();

	SaCell(SaCellInputOperation inputOperation, SaCellStackOperation stackOperation,
	       SaCellReturn saCellReturn, int stackOperationValue);

	explicit operator std::string() const;

	bool operator<(const SaCell& rhs) const;

	bool operator>(const SaCell& rhs) const;

	bool operator<=(const SaCell& rhs) const;

	bool operator>=(const SaCell& rhs) const;
};

class Grammar {
private:
	std::string startNonTerminal;
	std::map<std::string, std::vector<std::vector<std::string>>> grammar; // словарь для хранения грамматики: ключ - нетерминал, значение - множество правых частей правил, каждая из которых - множество строк (терминалов/нетерминалов)
	std::map<std::string, std::set<std::string>> firstForG; // словарь для хранения значений FIRST для всех терминалов и нетерминалов грамматики: ключ - терминал/нетерминал, значение - множество терминалов
	std::map<std::string, std::set<std::string>> followForG; // словарь для хранения значений FOLLOW для всех нетерминалов грамматики: ключ - нетерминал, значение - множество терминалов
	std::vector<std::pair<std::string, std::vector<std::string>>> enumeratedRules;
	std::map<std::string, std::map<std::string, std::set<SaCell>>> saTable;
	std::set<std::string> terminals;
	std::set<std::string> nonTerminals;

	bool initFirstWithTerminalsAndEpsilon();

	bool initFirstWithNonTerminals();

	bool initFollow();

	bool calculateFollow();

    bool isTerminal(const std::string &word);

    bool isNonTerminal(const std::string &word);

public:
    const std::string &getStartNonTerminal() const;

    const std::map<std::string, std::vector<std::vector<std::string>>> &getGrammar() const;

	const std::map<std::string, std::set<std::string>>& getFirstForG() const;

	const std::map<std::string, std::set<std::string>>& getFollowForG() const;

	Grammar();

	~Grammar();

	bool loadGrammar(std::istream& stream);

	bool buildSATable();

	void printSATable(std::ostream& stream);

	void printFirst(std::ostream& stream);

	void printFollow(std::ostream& stream);

	bool parse(std::istream& stream);

	std::set<std::string> first(const std::vector<std::string>&);

	std::set<std::string> follow(const std::string&);
};

std::ostream &operator<<(std::ostream &stream, const Grammar &g);

#endif //EDUSANDBOX_FIRSTFOLLOW_H
