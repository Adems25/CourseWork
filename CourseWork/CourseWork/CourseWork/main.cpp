#include <iostream>

#include "String.h"
#include "interface.h"
#include "RPN.h"

int main() {
	char c;
	String str;
	while (true) {
		menu();
		c = chooseAction();
		switch (c) {
		case 'c':
			std::cout << "Enter expression: " << std::endl;
			std::cin >> str;
			str.size();
			if (RPN::isCorrect(str))
				std::cout << "Expression is correct." << std::endl;
			break;
		case 'r':
			c = chooseExpression();

			if (c == 'n') {
				std::cout << "Enter expression: " << std::endl;
				std::cin >> str;
			}
			else
				if (str.size() == 0) {
					std::cout << "Old expression is absent.\nEnter new expression: " << std::endl;
					std::cin >> str;
				}
			if (RPN::isCorrect(str))
				std::cout << "Count of exspression: " << RPN(str).count() << std::endl;
			break;
		case 'e':
			std::cout << "Program is over." << std::endl;
			return 0;
		}
	}

	return 0;
}

