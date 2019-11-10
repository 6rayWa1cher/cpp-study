//
// Created by Konstantin Grigoriev on 20/09/2019.
//

#include <iostream>
#include <vector>
#include <csignal>

void my_handler(int s) {
	printf("Caught signal %d\n", s);
	exit(1);
}

int main() {
	std::string str;
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	while (true) {
		std::cin >> str;
		std::cout << str << std::cin.eof();
	}

}
