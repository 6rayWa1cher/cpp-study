//
// Created by 6rayWa1cher on 07.05.2020.
//

#include "../hw11/firstfollow.h"
#include <fstream>

int main() {
	Grammar grammar = Grammar();
	std::ifstream stream("../resources/hw11/samplegrammar1.txt");
	grammar.loadGrammar(stream);
	std::cout << grammar;
	std::cout << "========first========" << std::endl;
	grammar.printFirst(std::cout);
	std::cout << "========follow========" << std::endl;
	grammar.printFollow(std::cout);
	std::cout << std::endl << std::endl;

	// тестирование FIRST
	std::vector<std::string> alpha;
	alpha.push_back("E");
	std::cout << grammar.first(alpha);
	alpha.clear();

	alpha.push_back("E'");
	std::cout << grammar.first(alpha);
	alpha.clear();

	alpha.push_back("T");
	std::cout << grammar.first(alpha);
	alpha.clear();

	alpha.push_back("T'");
	std::cout << grammar.first(alpha);
	alpha.clear();

	alpha.push_back("F");
	std::cout << grammar.first(alpha);
	alpha.clear();

	alpha.push_back(")");
	std::cout << grammar.first(alpha);
	alpha.clear();

	alpha.push_back("id");
	std::cout << grammar.first(alpha);
	alpha.clear();

//    grammar.printFirst(std::cout);
//	std::cout << std::endl;
	// тестируем FOLLOW
	std::cout << grammar.follow(std::string("E"));
	std::cout << grammar.follow(std::string("E'"));
	std::cout << grammar.follow(std::string("T"));
	std::cout << grammar.follow(std::string("T'"));
	std::cout << grammar.follow(std::string("F"));

	return 0;
}