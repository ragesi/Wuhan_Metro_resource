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
//定义全局参数，线路不可到达的权值
const float maxValue = 200000;


/************************************************************
     结构体名称：Edge
	 功能描述：地图的边信息储存
	 作者：许鹏，王子越
*************************************************************/
struct Edge {
	// 结点位置
	int dest;
	// 权值
	int cost;
	// 边之间的指针
	Edge* link;
	// 两种构造函数
	Edge() {}
	Edge(int num, int weight) :dest(num), cost(weight), link(NULL) {}
	// 运算符重载
	bool operator !=(Edge& R)const
	{
		return (dest != R.dest) ? true : false;
	}
};

/************************************************************
	 结构体名称：Vertex
	 功能描述：地图的结点信息储存
	 作者：许鹏，王子越
*************************************************************/
struct Vertex {
	//顶点名字
	int data;
	//头指针
	Edge* adj;
};

/************************************************************
	 类名称：Graphlnk
	 功能描述：查询使用的地图主结构与功能集合
	 外部函数接口：构造函数，ShortestPath（计算最短路径),PrintShortestPath(打印最短路径)
	 作者：许鹏，王子越
*************************************************************/
class Graphlnk {
public:
	// 默认构造函数
	Graphlnk(int sz = Max);
	~Graphlnk();
	// 计算最短路径
	void ShortestPath(Graphlnk& G, int v, int dist[], int path[]);
	// 打印最短路径
	void PrintShortestPath(Graphlnk& G, int v, int last, int path[], CString& mypath);
	// 距离
	int distance;
	// 站点数
	int num;
	// 保存站点序号
	vector<int>station;
	vector<CString> PlaceInfor;
protected:
	// 邻接链表头结点表
	Vertex* NodeTable;
	// 从文件导入数据建立图
	void CreateGraphlnk();
	// 获取权值
	int getWeight(int v1, int v2);
	// 获取第一个邻居结点
	int getFirstNeighbor(int v);
	// 获取下一个邻居结点
	int getNextNeighbor(int v, int w);
	// 插入一个结点
	bool insertVertex(const int& vertex);
	// 插入一条边
	bool insertEdge(int v1, int v2, int cost);
	// 内联函数
	// 获取结点的数据data
	inline int getVlaue(int i) 
	{
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
	}
	// 获取结点的索引
	inline int getVertexPos(const int vertex) {
		for (int i = 0; i < numVertices; i++) {
			if (NodeTable[i].data == vertex)
				return i;
		}
		return -1;
	}
	// 图中最大节点数
	int maxVertices;
	// 当前边数
	int numEdges;
	// 当前顶点数
	int numVertices;
};
