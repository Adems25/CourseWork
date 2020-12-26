#include "interface.h"

//printing information about commands
void menu() {
	std::cout << "Enter 'c' for checking expression." << std::endl;
	std::cout << "Enter 'r' for counting value of expression." << std::endl;
	std::cout << "Enter 'e' for exit." << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
}

//removing extra characters from std::cin
void clearBuffer() {
	while (true) {
		if (std::cin.peek() == EOF)
			return;

		if (std::cin.peek() == '\n') {
			std::cin.get();
			return;
		}

		std::cin.get();
	}
}

//action choice: checking / counting / exit
char chooseAction() {
	char c;
	while (true) {
		std::cout << "Choose option: ";
		std::cin >> c;
		clearBuffer();
		std::cout << std::endl;
		switch (c) {
		case 'c':
		case 'r':
		case 'e':
			return c;
		default:
			std::cout << "Incorrect value, try again." << std::endl;
		}
	}
}

//expression choice: new / old
char chooseExpression() {
	char c;
	while (true) {
		std::cout << "If you want use old expression type 'o'." << std::endl;
		std::cout << "If you want use new expression type 'n'." << std::endl;
		std::cout << "Choose option: ";
		std::cin >> c;
		clearBuffer();
		std::cout << std::endl;

		switch (c) {
		case 'o':
		case 'n':
			return c;
		default:
			std::cout << "Incorrect value, try again." << std::endl;
		}
	}
}