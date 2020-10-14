#include "exprtree.h"
#include <iostream>
using namespace std;

//----------------------------------- pre-lab ---------------------------------------

char* prefix = new char[20];

ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode* leftPtr, ExprTreeNode* rightPtr)
	:element(elem), left(leftPtr), right(rightPtr)
{
	// ExprTreeNode의 constructor
}

ExprTree::ExprTree()
	: root(NULL)
{
	// ExprTree의 constructor
}

ExprTree::~ExprTree()
{
	clear(); // ExprTree의 destructor
}

void ExprTree::build()
{
	cin >> prefix;
	buildSub(root);
}

void ExprTree::buildSub(ExprTreeNode*& p)
{
	while (*prefix)
	{
		p = new ExprTreeNode(*prefix, NULL, NULL);
		if (isdigit(*prefix) == 0) // isdigit가 0이면 숫자가 아님
		{
			prefix++; // prefix++ => prefix 배열의 다음 element를 가리킴
			buildSub(p->left);
			prefix++;
			buildSub(p->right);
			return;
		}
		else return;
	}
}

void ExprTree::expression() const
{
	exprSub(root);
}

void ExprTree::exprSub(ExprTreeNode *p) const
{
	if (p != NULL)
	{
		if (isdigit(p->element) == 0) // 만약 p->element가 연산자면 괄호로 묶어주어야 한다
			cout << '(';
		exprSub(p->left);
		cout << p->element;
		exprSub(p->right);
		if (isdigit(p->element) == 0) // 만약 p->element가 연산자면 괄호로 묶어주어야 한다
			cout << ')';
	}
}

float ExprTree::evaluate() const
{
	return evaluateSub(root);
}

float ExprTree::evaluateSub(ExprTreeNode* p) const
{
	if (isdigit(p->element) == 0) // p->element가 문자인 경우
	{
		switch (p->element)
		{
		case '+':
			return evaluateSub(p->left) + evaluateSub(p->right);
			break;
		case '-':
			return evaluateSub(p->left) - evaluateSub(p->right);
			break;
		case '*':
			return evaluateSub(p->left) * evaluateSub(p->right);
			break;
		case '/':
			return evaluateSub(p->left) / evaluateSub(p->right);
			break;
		default:
			return 0;
			break;
		}
	}
	else
		return p->element - '0';
	// 입력받은 p->element는 char이므로 0의 ASCII 코드를 빼 주어야 float으로 변환했을 때 원래의 숫자값이 나옴
}

void ExprTree::clear()
{
	clearSub(root);
	root = NULL;
}

void ExprTree::clearSub(ExprTreeNode* p) 
{
	if (p != NULL) {
		clearSub(p->left);
		clearSub(p->right);
		delete p;
	}
}

void ExprTree::showStructure() const
{
	if (root == NULL)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}

void ExprTree::showSub(ExprTreeNode* p, int level) const
{
	int i;
	if (p != NULL)
	{
		showSub(p->right, level + 1);
		for (i = 0; i < level; i++)
			cout << '\t';
		cout << " " << p->element;
		if ((p->left != 0) && (p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showSub(p->left, level + 1);
	}
}

//----------------------------------- in-lab ---------------------------------------
