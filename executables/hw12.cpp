//
// Created by 6rayWa1cher on 13.05.2020.
//

#include "../hw11_12/firstfollow.h"
#include <fstream>

int main() {
	Grammar grammar = Grammar();
	std::ifstream stream("../resources/hw12/samplegrammar1.txt");
	grammar.loadGrammar(stream);
	std::cout << grammar;
	std::cout << "========first========" << std::endl;
	grammar.printFirst(std::cout);
	std::cout << "========follow========" << std::endl;
	grammar.printFollow(std::cout);
	std::cout << std::endl << std::endl;
	grammar.buildSATable();
	grammar.printSATable(std::cout);
}