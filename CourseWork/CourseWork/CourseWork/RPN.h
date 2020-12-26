#ifndef __RPN

#define __RPN

#include "String.h"
#include "Stack.h"
#include <cmath>
#include <stdexcept>

#define M_PI 3.14159265358979323846
#define EPS 1e-15

typedef int ssize_t;

/*
'p' - pi
'e' - exp
'_' - -
's' - sin
'c' - cos
't' - tg
'g' - ctg
'o' - log
'l' - ln
'q' - sqrt
'a' - abs
*/


//getting priority of operation
int priority(char);

//get first left character which is differnt from 'space' (from index)
ssize_t leftCharacter(String str, size_t index);

//get first right character which is differnt from 'space' (from index)
size_t rightCharacter(String str, size_t index);

//printing string with show position of mistake
void printErrorPosition(String, size_t);

//Reverse Polish Notation
class RPN {
public:
	//constructor from infix to postfix reverse polish notation
	explicit RPN(String);

	//checking expression for mistakes
	static bool isCorrect(String);

	//counting result of expression
	double count() const;
private:
	//checking expression for incorrect commands and symbols
	static bool isCorrectParts(String str);

	//transforming correct expression to reverse postfix notation
	void transform(String);

	String result;		//string for postfix notation expression
};

#endif 

