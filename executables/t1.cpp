//
// Created by Konstantin Grigoriev on 20/09/2019.
//

#include <iostream>
#include <vector>
#include <csignal>

void funct(char *str) {
	int i, j = 0, s = 1;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ') {
			str[j] = str[i];
			s = 1;
			j++;
		} else if (str[i] == ' ' && s != 0) {
			str[j] = str[i];
			j++;
			s = 0;
		}
	}
	str[j] = '\0';
}

int main() {
	char str[] = "abc zzz    dd   zz";
	funct(str);
	std::cout << std::string(str) << '!';
}
