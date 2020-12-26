#ifndef __STRING

#define __STRING

#include <iostream>

#define _CAPACITY 100u
#define CAPACITY(n) ((n / _CAPACITY + 1)*_CAPACITY)

class String {
public:
	String();				//default constructor
	String(const String&);	//copy constructor
	String(const char*);	//constructor from array of chars
	~String() { clear(); }	

	char& operator[](size_t);	//get element in i position
	char operator[](size_t) const;	//get copy of element in i position

	void push_back(char c);		//push character in the end of string

	size_t size() const;	//size of string
	void clear();			//clear string

	void eraseSpaces();		//deleting spaces from string

	//overloading of operator input from stream
	friend std::istream& operator>>(std::istream&, String&);

	//overloading of operator output to stream
	friend std::ostream& operator<<(std::ostream&, const String&);
private:
	char* arr;			//array of characters
	size_t n;			//count of array's elements (count in fact)
	size_t capacity;	//capacity of array (count in theory)
};

#endif 