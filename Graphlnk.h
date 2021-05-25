#pragma once
#define  Max  100
#include <cstddef>
#include<assert.h>
#include<iostream>
#include<fstream>
#include"Minheap.h"
#include <afxwin.h>
#include"CMyFile.h"
#include"pch.h"
using namespace std;
//����ȫ�ֲ�������·���ɵ����Ȩֵ
const float maxValue = 200000;


/************************************************************
     �ṹ�����ƣ�Edge
	 ������������ͼ�ı���Ϣ����
	 ���ߣ�����������Խ
*************************************************************/
struct Edge {
	// ���λ��
	int dest;
	// Ȩֵ
	int cost;
	// ��֮���ָ��
	Edge* link;
	// ���ֹ��캯��
	Edge() {}
	Edge(int num, int weight) :dest(num), cost(weight), link(NULL) {}
	// ���������
	bool operator !=(Edge& R)const
	{
		return (dest != R.dest) ? true : false;
	}
};

/************************************************************
	 �ṹ�����ƣ�Vertex
	 ������������ͼ�Ľ����Ϣ����
	 ���ߣ�����������Խ
*************************************************************/
struct Vertex {
	//��������
	int data;
	//ͷָ��
	Edge* adj;
};

/************************************************************
	 �����ƣ�Graphlnk
	 ������������ѯʹ�õĵ�ͼ���ṹ�빦�ܼ���
	 �ⲿ�����ӿڣ����캯����ShortestPath���������·��),PrintShortestPath(��ӡ���·��)
	 ���ߣ�����������Խ
*************************************************************/
class Graphlnk {
public:
	// Ĭ�Ϲ��캯��
	Graphlnk(int sz = Max);
	~Graphlnk();
	// �������·��
	void ShortestPath(Graphlnk& G, int v, int dist[], int path[]);
	// ��ӡ���·��
	void PrintShortestPath(Graphlnk& G, int v, int last, int path[], CString& mypath);
	// ����
	int distance;
	// վ����
	int num;
	// ����վ�����
	vector<int>station;
	vector<CString> PlaceInfor;
protected:
	// �ڽ�����ͷ����
	Vertex* NodeTable;
	// ���ļ��������ݽ���ͼ
	void CreateGraphlnk();
	// ��ȡȨֵ
	int getWeight(int v1, int v2);
	// ��ȡ��һ���ھӽ��
	int getFirstNeighbor(int v);
	// ��ȡ��һ���ھӽ��
	int getNextNeighbor(int v, int w);
	// ����һ�����
	bool insertVertex(const int& vertex);
	// ����һ����
	bool insertEdge(int v1, int v2, int cost);
	// ��������
	// ��ȡ��������data
	inline int getVlaue(int i) 
	{
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
	}
	// ��ȡ��������
	inline int getVertexPos(const int vertex) {
		for (int i = 0; i < numVertices; i++) {
			if (NodeTable[i].data == vertex)
				return i;
		}
		return -1;
	}
	// ͼ�����ڵ���
	int maxVertices;
	// ��ǰ����
	int numEdges;
	// ��ǰ������
	int numVertices;
};
