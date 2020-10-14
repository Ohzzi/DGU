#include "bstree.h"
#include <iostream>

using namespace std;

template < class TE, class KF >																			// TE : tree element, KF : key field
BSTreeNode<TE, KF>::BSTreeNode(const TE &elem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)				// constructor
	: element(elem), left(leftPtr), right(rightPtr)
{
}

template < class TE, class KF >
BSTree <TE, KF>::BSTree()																				// constructor
	: root(0)
{
}

template <class TE, class KF>
BSTree<TE, KF>::~BSTree()																				// Destructor
{
	clear();
}

template <class TE, class KF>
void BSTree<TE, KF>::insert(const TE &newElement)														// Insert element
{
	insertSub(root, newElement);
}

template <class TE, class KF>
int BSTree<TE, KF>::retrieve(KF searchKey, TE &searchElement) const										// Retrieve element
{
	if (retrieveSub(root, searchKey, searchElement))
		return true;
	else return false;
}

template <class TE, class KF>
int BSTree<TE, KF>::remove(KF deleteKey)																// Remove element
{
	if (removeSub(root, deleteKey))
		return true;
	else
		return false;
}

template <class TE, class KF>
void BSTree<TE, KF>::writeKeys() const																	// Output keys
{
	writeKeysSub(root);
}

template <class TE, class KF>
void BSTree<TE, KF>::clear()																			// Clear tree
{
	clearSub(root);
	root = NULL;
}

template <class TE, class KF>
int BSTree<TE, KF>::empty() const																		// Tree is empty
{
	if (root == NULL)
		return true;
	else return false;
}

template <class TE, class KF>
int BSTree<TE, KF>::full() const																		// Tree is full
{
	return 0;
}

template <class TE, class KF>
void BSTree<TE, KF>::showStructure() const
{
	if (root == NULL)
	{
		cout << "Empty tree" << endl;
	}
	else
	{
		cout << endl;
		showSub(root, 1);
		cout << endl;
	}
}


template <class TE, class KF>
void BSTree<TE, KF>::insertSub(BSTreeNode<TE, KF> *&p, const TE &newElement)
{
	if (p == NULL)
		p = new BSTreeNode<TE, KF>(newElement, NULL, NULL); // base case
	else if (newElement.key() < p->element.key())
		insertSub(p->left, newElement);
	else if (newElement.key() > p->element.key())
		insertSub(p->right, newElement);
	// base case�� �� �� ���� Ű���� ���ؼ� ����� ���� �Ǵ� �����ʿ� �߰�
}

template <class TE, class KF>
int BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF> *p, KF searchKey, TE &searchElement) const
{
	if (p->element.key() == searchKey)
	{
		searchElement.setKey(searchKey);
		return true;
	} //element�� key�� searchKey�� ������ true ��ȯ
	else if (p->element.key() > searchKey&& p->left != NULL)
		retrieveSub(p->left, searchKey, searchElement);
	// element�� key�� �� ũ�� ����� ������ Ž��
	else if (p->element.key() < searchKey && p->right != NULL)
		retrieveSub(p->right, searchKey, searchElement);
	// element�� key�� �� ������ ����� �������� Ž��
	else return false;
	// �� �� Ž���Ϸ��� �ڽ� ��尡 NULL�̸� false�� ��ȯ
}

template <class TE, class KF>
int BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF> *&p, KF deleteKey)
{
	if (p->element.key() == deleteKey)
	{
		BSTreeNode<TE, KF>* tempPtr = p;
		cutRightmost(p, tempPtr);
		return true;
	} // ���� ã���� cutRightmost �Լ��� ���� Ʈ���� �ٽ� �������ְ� true�� ��ȯ
	else if (p->element.key() > deleteKey&& p->left != NULL)
		removeSub(p->left, deleteKey);
	else if (p->element.key() < deleteKey && p->right != NULL)
		removeSub(p->right, deleteKey);
	// ���� ��ġ���� ������ ���� �ڽĳ��� �Ѿ�� Ž���Ѵ�.
	else return false;
	// �� �� Ž���Ϸ��� �ڽ� ��尡 NULL�̸� not found �̹Ƿ� false ��ȯ
}

template <class TE, class KF>
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF> *&r, BSTreeNode<TE, KF> *&delPtr)
{
	if (r->left == NULL) // right child �� ��
	{
		r = r->right;
		delete delPtr;
	}
	else if (r->right == NULL) // left child �� ��
	{
		r = r->left;
		delete delPtr;
	}
	// 0 child or 1 child �� ��
	else
	{
		delPtr = delPtr->left;
		while (delPtr->right != NULL)
			delPtr = delPtr->right;
		r->element.setKey(delPtr->element.key());
		// ���� ������� �ߴ� ��忡 �� ����� ���� �ٱ⿡�� ���� ū ���� ������ش�
		removeSub(r->left, delPtr->element.key());
		// ����� ���� �ٱ⿡�� removeSub�� ���� ������� ���� ��带 �����ش�
	}
	// 2 child �� ��
}

template <class TE, class KF>
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF> *p) const
{
	if (p->left != NULL)
		writeKeysSub(p->left);
	cout << p->element.key() << ' ';
	if (p->right != NULL)
		writeKeysSub(p->right);
	// ����Լ��� �̿��ؼ� inorder�� ���
}

template <class TE, class KF>
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF> *p)
{
	if (p->left != NULL)
		clearSub(p->left);
	// ����� ���� �ٱ���� �����ش�
	if (p->right != NULL)
		clearSub(p->right);
	// ����� ������ �ٱ���� �����ش�
	if (p != NULL)
		delete p;
	// ��带 �����
}

template <class TE, class KF>
void BSTree<TE, KF>::showSub(BSTreeNode<TE, KF> *p, int level) const
{
	int i;

	if (p != NULL)
	{
		showSub(p->right, level + 1);
		for (i = 0; i < level; i++)
		{
			cout << '\t';
		}
		cout << " " << p->element.key();
		if ((p->left != 0) && (p->right != 0))
		{
			cout << "<";
		}
		else if (p->right != 0)
		{
			cout << "/";
		}
		else if (p->left != 0)
		{
			cout << "\\";
		}
		cout << endl;
		showSub(p->left, level + 1);
	}
}

 /*********************************************************************/
 /*                           In-Lab                                  */ 
 /*********************************************************************/
// In-lab operations
/*template <class TE, class KF>
int BSTree<TE, KF>::height() const																		// Height of tree
{
	//in-lab
}

template <class TE, class KF>
void BSTree<TE, KF>::writeLessThan(KF searchKey) const													// Output keys
{
	//in-lab
}


template <class TE, class KF>
int BSTree<TE, KF>::heightSub(BSTreeNode<TE, KF> *p) const
{
	//in-lab
}

template <class TE, class KF>
void BSTree<TE, KF>::writeLTSub(BSTreeNode<TE, KF> *p, KF searchKey) const
{
	//in-lab
};
*/