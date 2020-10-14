#include "OrganizationTree.h"
#include <iostream>
#include <algorithm>

using namespace std;

TreeNode::TreeNode(string name, TreeNode* child, TreeNode* sibling)
	:name(name), child(child), sibling(sibling)
{

}

Tree::Tree()
	: root(NULL), parent(NULL)
{

}

Tree::~Tree()
{
	clear();
}

void Tree::setCEO(string name)
{
	root = new TreeNode(name, NULL, NULL);
}

TreeNode* Tree::find(string name)
{
	if (root != NULL)
	{
		parent = root;
		return findSub(root, name);
	}
	else return 0;
}

TreeNode* Tree::findSub(TreeNode* p, string name)
{
	TreeNode* result = NULL;
	if (p->name == name)
	{
		return p;
	}
	else
	{
		if (p->sibling != NULL)
		{ 
			result = findSub(p->sibling, name);
			if (result != NULL) return result;
		}
		if (p->child != NULL)
		{
			parent = p;
			result = findSub(p->child, name);
			if (result != NULL) return result;
		}
	}
	return NULL;
}

void Tree::hire(string name1, string name2)
{
	TreeNode* superior = find(name1); // superior�� name1�� ���� ���
	if (superior != NULL)
	{
		if (findSub(root, name2) == NULL) // �������� name2�� ���� ��尡 ������
			hireSub(superior, name2); // hireSub�� ���� name2�� ���
	}
}

void Tree::hireSub(TreeNode* p, string name)
{
	if (p->child == NULL) // p�� ����Ű�� ��尡 ��� �־�� �� �ڸ��� name�� ��带 ����
		p->child = new TreeNode(name, NULL, NULL);
	else // �ƴϸ� p�� sibling���� ����
	{
		TreeNode* addPtr = p->child;
		while (addPtr->sibling != NULL)
		{
			addPtr = addPtr->sibling;
		}
		addPtr->sibling = new TreeNode(name, NULL, NULL);
	}
}

bool Tree::fire(string name)
{
	TreeNode* delPtr = find(name);
	if (delPtr != NULL)
	{
		fireSub(delPtr);
		return true;
	}
	else
		return false;
}

void Tree::fireSub(TreeNode* p)
{
	TreeNode* tmp = p;
	TreeNode* pre;
	if (tmp == parent->child) // p�� ù°�� ��
	{
		pre = parent;
		while (tmp->child != NULL) // p�� ���������� ����
		{
			tmp->name = tmp->child->name; // ���������� ������Ŵ
			pre = tmp;
			tmp = tmp->child;
		}
		while (tmp->sibling != NULL) // p�� ���� ��尡 ����
		{
			tmp->name = tmp->sibling->name; // ���� ��带 �ϳ��� �÷���
			pre = tmp;
			tmp = tmp->sibling;
		} // ������ ������
		if (pre->child == tmp) // �����Ϸ��� ��尡 ����� �ڽ� ����� ���
			pre->child = NULL;
		else if (pre->sibling == tmp) // �����Ϸ��� ��尡 ������ ���� ����� ���
			pre->sibling = NULL;
		delete tmp; // tmp�� ����
	}
	else // p�� ù°�� �ƴ� ��
	{
		if (tmp != root) // p�� CEO�� �ƴ� ��
		{
			if (tmp->child != NULL) // ���������� ����
			{
				pre = parent;
				while (tmp->child != NULL) // p�� ���������� ����
				{
					tmp->name = tmp->child->name; // ���������� ������Ŵ
					pre = tmp;
					tmp = tmp->child;
				}
				while (tmp->sibling != NULL) // p�� ���� ��尡 ����
				{
					tmp->name = tmp->sibling->name; // ���� ��带 �ϳ��� �÷���
					pre = tmp;
					tmp = tmp->sibling;
				} // ������ ������
				if (pre->child == tmp) // �����Ϸ��� ��尡 ����� �ڽ� ����� ���
					pre->child = NULL;
				else if (pre->sibling == tmp) // �����Ϸ��� ��尡 ������ ���� ����� ���
					pre->sibling = NULL;
			}
			else // ���������� �������� ���� ���
			{
				pre = parent->child;
				while (pre->sibling != tmp)
					pre = pre->sibling; // �����Ϸ��� ����� ���� ������ pre�� �Ű���
				pre->sibling = tmp->sibling; // �յ� ��带 ����
			}
			delete tmp;
		}
		else // p�� CEO�� ��
		{
			if (tmp->child == NULL) // ���������� ������
			{
				delete tmp;
				root = NULL; // �״�� ����
			}
			else // ���������� ������
			{
				swap(tmp->name, tmp->child->name); // CEO�� ���������� �ٲ���
				fireSub(tmp->child); // �ٲ� CEO�� �����ϴ� �Լ� ȣ��
			}
		}
	}
}

void Tree::print()
{
	printSub(root, 0);
}

void Tree::printSub(TreeNode *p, int level)
{
	if (p != NULL)
	{
		for (int i = 0; i < level; i++)
			cout << '+';
		cout << p->name << endl;
	}
	if (p->child != NULL)
		printSub(p->child, level + 1);
	if (p->sibling != NULL)
		printSub(p->sibling, level);
}

void Tree::clear()
{
	clearSub(root);
	root = NULL;
}

void Tree::clearSub(TreeNode* p)
{
	if (p != NULL)
	{
		clearSub(p->child);
		clearSub(p->sibling);
		delete p;
	}
}

bool Tree::isEmpty()
{
	return (root == NULL); // root�� NULL�̸� ��������Ƿ� true ��ȯ
}