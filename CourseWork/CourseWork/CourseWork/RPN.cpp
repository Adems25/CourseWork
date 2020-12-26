#include "RPN.h"

//getting priority of operation
int priority(char c) {
	if (c == '^')
		return 2;
	else if (c == '*' || c == '/')
		return 1;
	else if (c == '+' || c == '-')
		return 0;
	return -1;
}

//get first left character which is differnt from 'space' (from index)
ssize_t leftCharacter(String str, size_t index) {
	ssize_t i;
	for (i = index - 1; i >= 0 && str[i] == ' '; i--);
	return i;
}

//get first right character which is differnt from 'space' (from index)
size_t rightCharacter(String str, size_t index) {
	size_t i;
	size_t n = str.size();
	for (i = index + 1; i <= n && str[i] == ' '; i++);
	return i;
}

//printing string with show position of mistake
void printErrorPosition(String str, size_t index) {
	index--;
	size_t n = str.size();

	std::cout << str;
	std::cout << std::endl;
	size_t i;
	for (i = 0; i < index; i++)
		std::cout << ' ';
	std::cout << '^';
	for (i++; i < n; i++)
		std::cout << ' ';
	std::cout << std::endl;
}

//constructor from infix to postfix reverse polish notation
RPN::RPN(String str) {
	if (isCorrect(str))
		transform(str);
	else
		throw std::invalid_argument("String is incorrect.");
}


//checking expression for incorrect commands and symbols
bool RPN::isCorrectParts(String str) {
	size_t n = str.size();

	for (size_t i = 0; i < n; i++)
		if (!(str[i] >= '0' && str[i] <= '9' || str[i] == '.'
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^'
			|| str[i] == '(' || str[i] == ')' || str[i] == ' '))
			if (str[i] == 'e' || i + 1 < n && str[i] == 'p' && str[++i] == 'i') {
				if (!(i + 1 == n || str[i + 1] == ' ' ||
					str[i] < 'A' || str[i] > 'Z' ||
					str[i] < 'a' || str[i] > 'z')) {
					std::cout << "Incorrect command in position " << i + 1 << ":" << std::endl;
					printErrorPosition(str, i + 1);
					return false;
				}
			}
			else {
				bool isWrongCommand = false;
				switch (str[i]) {
				case 's':
					if (i + 2 >= n)
						isWrongCommand = true;
					else if (str[i + 1] == 'i' && str[i + 2] == 'n')
						i += 2;
					else
						if (i + 3 < n && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't')
							i += 3;
						else isWrongCommand = true;
					break;
				case 'c':
					if (i + 2 >= n)
						isWrongCommand = true;
					else if (str[i + 1] == 'o' && str[i + 2] == 's'
						|| str[i + 1] == 't' && str[i + 2] == 'g')
						i += 2;
					else isWrongCommand = true;
					break;
				case 't':
					if (i + 1 >= n)
						isWrongCommand = true;
					else if (str[i + 1] == 'g')
						i += 1;
					else isWrongCommand = true;
					break;
				case 'l':
					if (i + 1 >= n)
						isWrongCommand = true;
					else if (str[i + 1] == 'n')
						i += 1;
					else if (i + 2 < n && str[i + 1] == 'o' && str[i + 2] == 'g')
						i += 2;
					else isWrongCommand = true;
					break;
				case 'a':
					if (i + 2 >= n)
						isWrongCommand = true;
					else if (str[i + 1] == 'b' && str[i + 2] == 's')
						i += 2;
					else isWrongCommand = true;
					break;
				default:
					std::cout << "Incorrect symbol in position " << i + 1 << ":" << std::endl;
					printErrorPosition(str, i + 1);
					return false;
				}
				if (isWrongCommand || !(i + 1 == n || str[i + 1] == ' ' ||
					str[i] < 'A' || str[i] > 'Z' ||
					str[i] < 'a' || str[i] > 'z')) {
					std::cout << "Incorrect command in position " << i + 1 << std::endl;
					printErrorPosition(str, i + 1);
					return false;
				}
			}
	return true;
}

//checking expression for mistakes
bool RPN::isCorrect(String str) {
	Stack<size_t> stack;
	size_t n = str.size();

	if (!isCorrectParts(str))
		return false;

	for (size_t i = 0; i < n; i++)
		if (str[i] == '.' || str[i] >= '0' && str[i] <= '9' || str[i] == 'p' || str[i] == 'e') { //begin of the number
			ssize_t indexLeft = leftCharacter(str, i);
			if (indexLeft >= 0)
				if (str[indexLeft] == ')') {
					std::cout << "Missed operator in position " << indexLeft + 2 << ":" << std::endl;
					printErrorPosition(str, indexLeft + 2);
					return false;
				}
				else if (str[indexLeft] >= '0' && str[indexLeft] <= '9' || str[indexLeft] == '.'
					|| str[indexLeft] == 'i' || str[indexLeft] == 'e') {
					std::cout << "Extra operand in position " << i + 1 << ":" << std::endl;
					printErrorPosition(str, i + 1);
					return false;
				}

			if (str[i] >= '0' && str[i] <= '9')
				for (i += 1; i < n && str[i] >= '0' && str[i] <= '9'; i++); //iterate all digits before point if any

			if (i != n)
				if (str[i] == '.') {
					size_t indexRight = rightCharacter(str, i);
					if (indexRight < n && str[indexRight] == '.') {
						std::cout << "Extra point in position " << indexRight + 1 << ":" << std::endl;
						printErrorPosition(str, indexRight + 1);
						return false;
					}
					i += 1;   //skip point
					for (; i < n && str[i] >= '0' && str[i] <= '9'; i++); //iterate all digits after point if any
				}
				else if (str[i] == 'e')
					i += 1;
				else if (str[i] == 'p')
					i += 2;
			size_t indexRight = (i == n ? n : rightCharacter(str, i - 1)); //searsh right notspace from the last symbol of number  

			if (indexRight < n && str[indexRight] == '(') {
				std::cout << "Missed operator in position " << i + 1 << ":" << std::endl;
				printErrorPosition(str, i + 1);
				return false;
			}
			else
				i--;		//return old symbol if it's not '('
		}
		else if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')')
			if (!stack.empty())
				stack.pop();
			else {
				std::cout << "Missing opening bracket for closing in position " << i + 1 << std::endl;
				printErrorPosition(str, i + 1);
				return false;
			}
		else if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '-') {
			ssize_t indexLeft = leftCharacter(str, i);

			if (indexLeft < 0)
				if (str[i] == '-')
					continue;
				else {
					std::cout << "Missed operand before operator in position " << i + 1 << ":" << std::endl;
					printErrorPosition(str, i + 1);
					return false;
				}

			if (!(str[indexLeft] == '.' || str[indexLeft] >= '0' && str[indexLeft] <= '9' ||
				str[indexLeft] == 'i' || str[indexLeft] == 'e' ||
				str[indexLeft] == ')' ||
				(str[i] == '-' && str[indexLeft] == '('))) {
				std::cout << "Missed operand before operator in position " << i + 1 << ":" << std::endl;
				printErrorPosition(str, i + 1);
				return false;
			}

			size_t indexRight = rightCharacter(str, i);

			if (indexRight >= n ||
				!(str[indexRight] == '.' || str[indexRight] >= '0' && str[indexRight] <= '9' ||
					str[indexRight] == '(' ||
					str[indexRight] == 's' || str[indexRight] == 'c' || str[indexRight] == 't'
					|| str[indexRight] == 'l' || str[indexRight] == 'e'
					|| str[indexRight] == 'p' || str[indexRight] == 'a')) {
				std::cout << "Missed operand in position " << i + 2 << ":" << std::endl;
				printErrorPosition(str, i + 2);
				return false;
			}

		}
		else if (str[i] == 's' || str[i] == 'c' || str[i] == 't'
			|| str[i] == 'l' || str[i] == 'a') {
			ssize_t indexLeft = leftCharacter(str, i);

			if (str[i] == 't' || str[i] == 'l' && str[i + 1] == 'n')
				i += 1;
			else if (str[i] == 's' && str[i + 1] == 'q')
				i += 3;
			else
				i += 2;

			if (indexLeft < 0)
				continue;

			if (!(str[indexLeft] == '(' || str[indexLeft] == '^' ||
				str[indexLeft] == '+' || str[indexLeft] == '-' ||
				str[indexLeft] == '*' || str[indexLeft] == '/')) {
				std::cout << "Missed operand before operator in position " << i + 1 << ":" << std::endl;
				printErrorPosition(str, i + 1);
				return false;
			}
			
			size_t indexRight = rightCharacter(str, i);

			if (indexRight >= n ||
				!(str[indexRight] == '.' || str[indexRight] >= '0' && str[indexRight] <= '9' ||
					str[indexRight] == '(' ||
					str[indexRight] == 's' || str[indexRight] == 'c' || str[i] == 't'
					|| str[i] == 'l' || str[i] == 'e' || str[i] == 'p' || str[i] == 'a')) {
				std::cout << "Missed operand in position " << i + 2 << ":" << std::endl;
				printErrorPosition(str, i + 2);
				return false;
			}
		}

	if (!stack.empty()) {
		std::cout << "Missed closing brake for brake in position " << stack.top() + 1 << ":" << std::endl;
		printErrorPosition(str, stack.top() + 1);
		return false;
	}

	return true;
}

//transforming correct expression to reverse postfix notation
void RPN::transform(String str) {
	str.eraseSpaces();

	Stack<char> stack;

	size_t n = str.size();
	for (size_t i = 0; i < n; i++) {
		if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
			for (i; str[i] >= '0' && str[i] <= '9' || str[i] == '.'; i++)
				result.push_back(str[i]);
			result.push_back(' ');
			i -= 1;		//cursor to the last digit / point
		}
		else if (str[i] == 'e')
			result.push_back('e');
		else if (str[i] == 'p') {
			result.push_back('p');
			i += 1;		//skip 'i'
		}
		else if (str[i] == '-' && (i == 0 || str[i - 1] == '('))
			stack.push('_');
		else if (str[i] == 's') {
			if (str[i + 1] == 'i') {
				stack.push('s');
				i += 2;
			}
			else if (str[i + 1] == 'q') {
				stack.push('q');
				i += 3;
			}
		}
		else if (str[i] == 'c') {
			if (str[i + 1] == 'o') {
				stack.push('c');
				i += 2;
			}
			else if (str[i + 1] == 't') {
				stack.push('g');
				i += 2;
			}
		}
		else if (str[i] == 't') {
			stack.push('t');
			i += 1;		//skip 'g'
		}
		else if (str[i] == 'l') {
			if (str[i + 1] == 'o') {
				stack.push('o');
				i += 2;
			}
			else if (str[i + 1] == 'n') {
				stack.push('l');
				i += 1;
			}
		}
		else if (str[i] == 'a') {
			stack.push('a');
			i += 2;
		}
		else if (str[i] == '(')
			stack.push('(');
		else if (str[i] == ')') {
			while (stack.top() != '(') {
				result.push_back(stack.pop());
			}
			stack.pop();
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
			while (!stack.empty()
				&& (stack.top() == 's' || stack.top() == 'c'
					|| stack.top() == 't' || stack.top() == 'g'
					|| stack.top() == 'o' || stack.top() == 'l'
					|| stack.top() == 'q' || stack.top() == 'a'
					|| stack.top() == '_'
					|| ((stack.top() == '+' || stack.top() == '-' || stack.top() == '*'
						|| stack.top() == '/' || stack.top() == '^') &&
						priority(stack.top()) >= priority(str[i])))) {
				result.push_back(stack.pop());
			}
			stack.push(str[i]);
		}
	}
	while (!stack.empty())
		result.push_back(stack.pop());
}

//counting result of expression
double RPN::count() const {
	Stack<double> stack;
	size_t n = result.size();
	for (size_t i = 0; i < result.size(); i++)
		if (result[i] >= '0' && result[i] <= '9') {
			double number = 0;
			for (; i < n && result[i] >= '0' && result[i] <= '9'; i++)
				number = number * 10 + (result[i] - '0');
			if (i < n && result[i] == '.') {
				int divisor = 1;
				for (i++; i < n && result[i] >= '0' && result[i] <= '9'; i++) {
					number = number * 10 + (result[i] - '0');
					divisor *= 10;
				}
				number /= divisor;
			}
			if (i < n && !result[i] == '.')
				i--;		//cursor to last number
			stack.push(number);
		}
		else if (result[i] == 'e')
			stack.push(exp(1));
		else if (result[i] == 'p')
			stack.push(M_PI);
		else if (result[i] == 's' || result[i] == 'c'
			|| result[i] == 't' || result[i] == 'g'
			|| result[i] == 'o' || result[i] == 'l'
			|| result[i] == 'q' || result[i] == 'a'
			|| result[i] == '_') {
			double x = stack.pop();
			switch (result[i]) {
			case 's':
				stack.push(sin(x));
				break;
			case 'c':
				stack.push(cos(x));
				break;
			case 't':
				stack.push(tan(x));
				break;
			case 'g':
				stack.push(1 / tan(x));
				break;
			case 'o':
				stack.push(log10(x));
				break;
			case 'l':
				stack.push(log(x));
				break;
			case 'q':
				stack.push(sqrt(x));
				break;
			case 'a':
				stack.push(abs(x));
				break;
			case '_':
				stack.push(-x);
				break;
			}
		}
		else if (result[i] == '+' || result[i] == '-'
			|| result[i] == '*' || result[i] == '/'
			|| result[i] == '^') {
			double b = stack.pop();
			double a = stack.pop();
			switch (result[i]) {
			case'+':
				stack.push(a + b);
				break;
			case '-':
				stack.push(a - b);
				break;
			case '*':
				stack.push(a * b);
				break;
			case '/':
				stack.push(a / b);
				break;
			case '^':
				stack.push(pow(a, b));
				break;
			}
		}

	return (abs(stack.top()) < EPS ? 0 : stack.pop());
}

