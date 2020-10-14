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
	Stack<int> stack(8); // stack ����
	int num1, num2, result;
	int i = 0;
	do
	{
		if (isdigit(postfix[i]))
		{
			stack.push(postfix[i] - '0'); // postfix�� i��°�� �����̸� stack�� �ִ´�.
			// �̶� postfix[i]�� char �̹Ƿ� '0'�� ���� ���ڷ� �����.
		}
		else if (!isdigit(postfix[i]))
		{
			num1 = stack.pop();
			num2 = stack.pop(); // �����ڸ� ������ stack���� ���ڸ� ������ num1, num2�� �����Ѵ�.
			switch (postfix[i])
			{
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num2 - num1; // num1�� ���� �������Ƿ� num2���� num1�� ����.
				break;
			case '*':
				result = num1 * num2;
				break;
			case '/':
				if (num1 != 0) {
					result = num2 / num1; // ���������� num2���� num1�� ������.
				}
				else {
					cout << "���� �� �����ϴ�!" << endl;
					result = 0;
				}
				break;
			default:
				cout << "incorrect input" << endl;
				break;
			}
			stack.push(result); // stack�� ����� result�� ��ȯ
		}
		i++;
	} while (postfix[i] != NULL); // postfix[i]�� NULL�̸� ������ �����Ѵ�.
	return stack.pop();
}