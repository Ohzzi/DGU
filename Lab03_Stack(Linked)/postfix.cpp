/*
 ----------------------------
 * Name: Oh Ji Hoon
 * Last modified: 2019-10-7
 * content: Calculator
 ----------------------------
*/
#include "stacklnk.cpp"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

#define _Maxname 20

int Calcul(char* postfix);  //this is function which calculate postfix
int main(void)
{
   char post[_Maxname];                //this is array that allocated the character of postfix

   cout << "This is calculator" << endl;
   cout << "Please input the postfix: ";
   cin >> post;                         //save the postfix on post array

   cout << "result: " << Calcul(post) << endl;   //Show the result
   system("pause");
   return 0;   
}

int Calcul(char* postfix)
{
	Stack<int> stack(8); // stack 선언
	int num1, num2, result;
	int i = 0;
	do
	{
		if (isdigit(postfix[i]))
		{
			stack.push(postfix[i] - '0'); // postfix의 i번째가 숫자이면 stack에 넣는다.
			// 이때 postfix[i]는 char 이므로 '0'을 빼서 숫자로 만든다.
		}
		else if (!isdigit(postfix[i]))
		{
			num1 = stack.pop();
			num2 = stack.pop(); // 연산자를 만나면 stack에서 숫자를 꺼내서 num1, num2에 저장한다.
			switch (postfix[i])
			{
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num2 - num1; // num1을 먼저 꺼냈으므로 num2에서 num1을 뺀다.
				break;
			case '*':
				result = num1 * num2;
				break;
			case '/':
				if (num1 != 0) {
					result = num2 / num1; // 마찬가지로 num2에서 num1을 나눈다.
				}
				else {
					cout << "나눌 수 없습니다!" << endl;
					result = 0;
				}
				break;
			default:
				cout << "incorrect input" << endl;
				break;
			}
			stack.push(result); // stack에 저장된 result를 반환
		}
		i++;
	} while (postfix[i] != NULL); // postfix[i]가 NULL이면 실행을 종료한다.
	return stack.pop();
}