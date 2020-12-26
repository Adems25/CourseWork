#ifndef __INTERFACE_

#define __INTERFACE_

#include <iostream>

//printing information about commands
void menu();

//removing extra characters from std::cin
void clearBuffer();

//action choice: checking / counting / exit
char chooseAction();

//expression choice: new / old
char chooseExpression();

#endif