#include "String.h"

//default constructor
String::String() : n(0), capacity(_CAPACITY) {
	arr = new char[capacity];
}

//copy constructor
String::String(const String& other) : n(other.n), capacity(other.capacity) {
	arr = new char[capacity];
	if (n != 0)
		for (size_t i = 0; i < n; i++)
			arr[i] = other.arr[i];
}

//constructor from array of chars
String::String(const char* from) {
	for (n = 0; from[n] != '\0'; n++);

	capacity = CAPACITY(n + 1);
	arr = new char[capacity];
	for (size_t i = 0; i <= n; i++)
		arr[i] = from[i];
}

//get element in i position
char& String::operator[](size_t i) {
	return arr[i];
}

//get copy of element in i position
char String::operator[](size_t i) const {
	return arr[i];
}

//push character in the end of string
void String::push_back(char c) {
	if (n == capacity) {
		char* new_array = new char[capacity + _CAPACITY];
		for (size_t i = 0; i < n; i++)
			new_array[i] = arr[i];
		delete[] arr;
		arr = new_array;
	}
	arr[n++] = c;
}

//size of string
size_t String::size() const {
	return n;
}

//clear string
void String::clear() {
	if (n != 0) {
		delete arr;
		capacity = _CAPACITY;
		arr = new char[capacity];
		n = 0;
	}
}

//deleting spaces from string
void String::eraseSpaces() {
	for (size_t i = 0; i < n; i++)
		if (arr[i] == ' ') {
			for (size_t j = i; j < n; j++)
				arr[j] = arr[j + 1];
			n--;
			i--;
		}
}

//overloading of operator input from stream
std::istream& operator>>(std::istream& is, String& string) {
	char buffer[256];
	is.getline(buffer, 255);
	string.clear();
	string.n = is.gcount();
	string.capacity = CAPACITY(string.n);
	string.arr = new char[string.capacity];
	for (size_t i = 0; i < string.n; i++)
		string.arr[i] = buffer[i];
	if (string.n != 0 && string.arr[string.n - 1] == '\0')
		string.n--;
	else
		string.arr[string.n] = '\0';
	return is;
}

//overloading of operator output to stream
std::ostream& operator<<(std::ostream& os, const String& string) {
	for (size_t i = 0; i < string.n; i++)
		os << string.arr[i];
	return os;
}