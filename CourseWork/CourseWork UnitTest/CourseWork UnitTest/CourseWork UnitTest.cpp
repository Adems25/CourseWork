#include "pch.h"
#include "CppUnitTest.h"
#include "../../CourseWork/CourseWork/Stack.h"
#include "../../CourseWork/CourseWork/String.h"
#include "../../CourseWork/CourseWork/String.cpp"
#include "../../CourseWork/CourseWork/RPN.h"
#include "../../CourseWork/CourseWork/RPN.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CourseWorkUnitTest
{
	TEST_CLASS(CourseWorkUnitTest)
	{
	public:
		TEST_METHOD(TestStack) {
			Stack<char> stack;
			const size_t N = 26;

			//push
			for (size_t i = 0; i < N; i++)
				stack.push('A' + i);

			//top
			Assert::AreEqual(stack.top(), 'Z');

			//pop
			for (size_t i = 0; i < N; i++)
				Assert::AreEqual(stack.pop(), char('Z' - i));
			Assert::IsTrue(stack.empty());

			//clear + empty
			for (size_t i = 0; i < N; i++)
				stack.push('A' + i);
			stack.clear();
			Assert::IsTrue(stack.empty());
		}

		TEST_METHOD(TestString) {
			const size_t N = 26;

			//default constructor
			String string;
			Assert::AreEqual(string.size(), 0u);

			//push_back
			for (size_t i = 0; i < N; i++)
				string.push_back('A' + i);
			for (size_t i = 0; i < N; i++)
				Assert::AreEqual(string[i], char('A' + i));

			Assert::AreEqual(string.size(), N);

			//erase
			for (size_t i = 0; i < N - 1; i += 2) {
				string[i] = ' ';
				string[i + 1] = '!';
			}
			Assert::AreEqual(string.size(), N);
			for (size_t i = 0; i < N; i++) {
				if (i % 2 == 0)
					Assert::AreEqual(string[i], ' ');
				else
					Assert::AreEqual(string[i], '!');
			}
			string.eraseSpaces();
			Assert::AreEqual(string.size(), N / 2);

			//copy constructor
			String string2(string);
			for (size_t i = 0; i < N / 2; i++)
				Assert::AreEqual(string2[i], '!');
			Assert::AreEqual(string2.size(), N / 2);

			//clear
			string.clear();
			Assert::AreEqual(string.size(), 0u);

			//stream input 
			std::ofstream file1;
			file1.open("test.txt");
			file1 << "abcdef";
			file1.close();

			std::ifstream file2;
			file2.open("test.txt");
			file2 >> string2;
			file2.close();

			for (size_t i = 0; i < 6; i++)
				Assert::AreEqual(string2[i], char('a' + i));
			Assert::AreEqual(string2.size(), 6u);

			//stream output 
			std::ofstream file3;
			file3.open("test2.txt");
			file3 << string2;
			file3.close();

			std::ifstream file4;
			file4.open("test2.txt");

			char c;
			for (size_t i = 0; i < 6; i++) {
				file4 >> c;
				Assert::AreEqual(c, char('a' + i));
			}
			file4.close();
		}

		TEST_METHOD(TestRPN) {
			
			Assert::AreEqual(priority('*'), priority('/'));
			Assert::AreEqual(priority('+'), priority('-'));
			Assert::IsFalse(priority('*') == priority('^'));
			Assert::IsFalse(priority('*') < priority('-'));
			Assert::IsTrue(priority('/') >= priority('+'));

			
			Assert::AreEqual(leftCharacter("123 7 5 6", 6), 4);
			Assert::AreEqual(leftCharacter("123   *  7 5 6", 6), 2);

			Assert::AreEqual(rightCharacter("123 7 5 6", 0), 1u);
			Assert::AreEqual(rightCharacter("123   *  7 5 6", 2), 6u);

			Assert::IsTrue(RPN::isCorrect("1+2"));
			Assert::IsTrue(RPN::isCorrect("2+4*9-(6+24/3)+12^2 + (-6*32)"));
			Assert::IsTrue(RPN::isCorrect("sin(3*pi/2) * ln5 - tg(0)*e"));
			Assert::IsTrue(RPN::isCorrect("(((sin(pi) + 0.5) - 2. * 19.8)* .3)"));
			Assert::IsTrue(RPN::isCorrect("(-12 * cos (pi/4) - ctg(pi/3))^5 + log(9)"));
			Assert::IsTrue(RPN::isCorrect("sqrt (abs(cos(19)^2 - sin(19)^2))"));

			//isCorrectParts in isCorrect
			Assert::IsTrue(RPN::isCorrect("sin(8)"));
			Assert::IsTrue(RPN::isCorrect("sin(tg(18))"));
			Assert::IsTrue(RPN::isCorrect("ln5 + tg(0)*e"));
			Assert::IsFalse(RPN::isCorrect("sinus(12)"));
			Assert::IsFalse(RPN::isCorrect("absolut(12) + 3"));
			Assert::IsFalse(RPN::isCorrect("14 - sqr(abs(5))"));

			//count (transform + constructor)
			Assert::IsTrue(abs(RPN("123 + 7*3 - 5.6^2").count()- 112.64) < EPS);
			Assert::IsTrue(abs(RPN("sin(9)^2+cos(9)^2").count() - 1.0) < EPS);
			Assert::IsTrue(abs(RPN("sin(pi/6) + ln(e) + tg(0)").count() - 1.5) < EPS);
			Assert::IsTrue(abs(RPN("(ctg(5) * tg(5))*(log(10)*abs(12-13))").count() - 1.0) < EPS);
			Assert::IsTrue(abs(RPN("sqrt(6^2+8^2)").count() - 10.0) < EPS);
		}
	};
}
