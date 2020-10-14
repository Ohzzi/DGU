#include "wtgraph.h"
#include <iostream>

using namespace std;

WtGraph::WtGraph(int maxNumber)
	:maxSize(maxNumber), size(0), vertexList(new Vertex[maxNumber]),
	adjMatrix(new int[maxNumber * maxNumber]), pathMatrix(new int[maxNumber * maxNumber]) // 동적 할당
{
	for (int i = 0; i < maxSize * maxSize; i++)
	{
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt; // 모두 0으로 초기화
	}
}

WtGraph::~WtGraph()
{
	delete[] vertexList, adjMatrix, pathMatrix;
}

int WtGraph::index(char* v) const
{
	string str = v;
	for (int i = 0; i < size; i++)
	{
		if (str == vertexList[i].label)
			return i + 1; // i=0이면 false값이므로 i+1을 반환
	}
	cout << "There is not correct vertex " << v << endl;
	return 0;
}

int& WtGraph::edge(int row, int col)
{
	int index = row * maxSize + col;
	return adjMatrix[index];
}

int WtGraph::empty() const
{
	if (size == 0) return 1;
	else return 0;
}

int WtGraph::full() const
{
	if (size == maxSize) return 1;
	else return 0;
}

void WtGraph::insertVertex(Vertex newVertex)
{
	if (!full()) // 조건 : 그래프가 가득 차 있지 않다
	{
		string str = newVertex.label;
		for (int i = 0; i < size; i++)
			if (str == vertexList[i].label)
			{
				vertexList[i] = newVertex;
				return;
			} // 정점이 이미 그래프에 존재하면 해당 정점을 갱신한다
		vertexList[size] = newVertex;
		size++;
	}
}

void WtGraph::insertEdge(char* v1, char* v2, int wt)
{
	if (wt > 0 && wt < infiniteEdgeWt && index(v1) && index(v2))
	{
		int	indexv1 = index(v1) - 1, indexv2 = index(v2) - 1;
		edge(indexv1, indexv2) = wt;
		edge(indexv2, indexv1) = wt;
	}
	computePaths();
}

int WtGraph::retrieveVertex(char* v, Vertex& vData) const
{
	string str = v;
	for (int i = 0; i < size; i++)
	{
		if (str == vertexList[i].label)
		{
			vData = vertexList[i];
			return 1;
		}
	}
	return 0;
}

int WtGraph::edgeWeight(char* v1, char* v2, int& wt)
{
	if (index(v1) && index(v2))
	{
		int indexv1 = index(v1) - 1, indexv2 = index(v2) - 1;
		wt = edge(indexv1,indexv2);
		return 1;
	}
}

void WtGraph::removeVertex(char* v)
{
	int remindex = index(v) - 1;
	if (remindex != -1)
	{
		for (int i = remindex; i < size - 1; i++)
			vertexList[i] = vertexList[i + 1]; // 정점을 하나씩 당겨줌
		for (int i = 0; i < size; i++)
		{
			for (int j = remindex; j < size - 1; j++)
				edge(i, j) = edge(i, j + 1);
		} // 삭제하려는 행 정리
		for (int i = 0; i < size; i++)
		{
			for (int j = remindex; j < size - 1; j++)
				edge(j, i) = edge(j + 1, i);
		} // 삭제하려는 열 정리
		size--;
	}
	computePaths();
}

void WtGraph::removeEdge(char* v1, char* v2)
{
	int indexv1 = index(v1) - 1, indexv2 = index(v2) - 1;
	if (indexv1 != -1 && indexv2 != -1)
	{
		edge(indexv1, indexv2) = infiniteEdgeWt;
		edge(indexv2, indexv1) = infiniteEdgeWt;
	}
	computePaths();
}

void WtGraph::clear()
{
	for (int i = 0; i < maxSize * maxSize; i++) 
	{
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt;
	}
	size = 0;
}

void WtGraph::computePaths()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (j == k || i == j || i == k);
				else if (edge(j, i) != infiniteEdgeWt && edge(i, k) != infiniteEdgeWt)
				{
					if (edge(j, i) + edge(i, k) < edge(j, k))
						pathMatrix[j * maxSize + k] = edge(j, i) + edge(i, k);
					else pathMatrix[j * maxSize + k] = edge(j, k);
				}
				else pathMatrix[j * maxSize + k] = edge(j, k);
			}
		}
	}
}

void WtGraph::showStructure()
{
	int wt,
		row, col;

	if (size == 0)
		cout << "Empty graph" << endl;
	else
	{
		cout << endl << "Vertex list : " << endl;
		for (row = 0; row < size; row++)
			cout << row << '\t' << vertexList[row].label << endl;

		cout << endl << "Edge matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = adjMatrix[row * maxSize + col];
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}

		cout << endl << "Path matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = pathMatrix[row * maxSize + col];
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}
	}
}