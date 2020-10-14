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
	// base case가 될 때 까지 키값을 비교해서 노드의 왼쪽 또는 오른쪽에 추가
}

template <class TE, class KF>
int BSTree<TE, KF>::retrieveSub(BSTreeNode<TE, KF> *p, KF searchKey, TE &searchElement) const
{
	if (p->element.key() == searchKey)
	{
		searchElement.setKey(searchKey);
		return true;
	} //element의 key와 searchKey가 같으면 true 반환
	else if (p->element.key() > searchKey&& p->left != NULL)
		retrieveSub(p->left, searchKey, searchElement);
	// element의 key가 더 크면 노드의 왼쪽을 탐색
	else if (p->element.key() < searchKey && p->right != NULL)
		retrieveSub(p->right, searchKey, searchElement);
	// element의 key가 더 작으면 노드의 오른쪽을 탐색
	else return false;
	// 이 때 탐색하려는 자식 노드가 NULL이면 false를 반환
}

template <class TE, class KF>
int BSTree<TE, KF>::removeSub(BSTreeNode<TE, KF> *&p, KF deleteKey)
{
	if (p->element.key() == deleteKey)
	{
		BSTreeNode<TE, KF>* tempPtr = p;
		cutRightmost(p, tempPtr);
		return true;
	} // 값을 찾으면 cutRightmost 함수를 통해 트리를 다시 정리해주고 true를 반환
	else if (p->element.key() > deleteKey&& p->left != NULL)
		removeSub(p->left, deleteKey);
	else if (p->element.key() < deleteKey && p->right != NULL)
		removeSub(p->right, deleteKey);
	// 값이 일치하지 않으면 다음 자식노드로 넘어가서 탐색한다.
	else return false;
	// 이 때 탐색하려는 자식 노드가 NULL이면 not found 이므로 false 반환
}

template <class TE, class KF>
void BSTree<TE, KF>::cutRightmost(BSTreeNode<TE, KF> *&r, BSTreeNode<TE, KF> *&delPtr)
{
	if (r->left == NULL) // right child 일 때
	{
		r = r->right;
		delete delPtr;
	}
	else if (r->right == NULL) // left child 일 때
	{
		r = r->left;
		delete delPtr;
	}
	// 0 child or 1 child 일 때
	else
	{
		delPtr = delPtr->left;
		while (delPtr->right != NULL)
			delPtr = delPtr->right;
		r->element.setKey(delPtr->element.key());
		// 원래 지우려고 했던 노드에 그 노드의 왼쪽 줄기에서 가장 큰 값을 덮어씌워준다
		removeSub(r->left, delPtr->element.key());
		// 노드의 왼쪽 줄기에서 removeSub를 통해 덮어씌워준 원본 노드를 지워준다
	}
	// 2 child 일 때
}

template <class TE, class KF>
void BSTree<TE, KF>::writeKeysSub(BSTreeNode<TE, KF> *p) const
{
	if (p->left != NULL)
		writeKeysSub(p->left);
	cout << p->element.key() << ' ';
	if (p->right != NULL)
		writeKeysSub(p->right);
	// 재귀함수를 이용해서 inorder로 출력
}

template <class TE, class KF>
void BSTree<TE, KF>::clearSub(BSTreeNode<TE, KF> *p)
{
	if (p->left != NULL)
		clearSub(p->left);
	// 노드의 왼쪽 줄기들을 지워준다
	if (p->right != NULL)
		clearSub(p->right);
	// 노드의 오른쪽 줄기들을 지워준다
	if (p != NULL)
		delete p;
	// 노드를 지운다
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