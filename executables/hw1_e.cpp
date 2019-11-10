//
// Created by Konstantin Grigoriev on 12/09/2019.
//
#include <iostream>
#include "../hw1/primefunc.h"
#include "../hw1/binfunc.h"

int main() {
	int inp, arg;
	while (true) {
		std::cout << "Таск>";
		std::cin >> inp;
		if (inp == 0) {
			return 0;
		}
		switch (inp) {
			case 1:
				std::cout << "Аргумент>";
				std::cin >> arg;
				std::cout << isPrime(arg) << std::endl;
				break;
			case 2:
				std::cout << "Аргумент>";
				std::cin >> arg;
				printPrimes(arg);
				break;
			case 3:
				std::cout << "Аргумент>";
				std::cin >> arg;
				printPrimesRev(arg);
				break;
			case 4:
				std::cout << "Аргумент>";
				std::cin >> arg;
				printBinary(arg);
				break;
			default:
				std::cout << "nya?" << std::endl;
				break;
		}
	}
}