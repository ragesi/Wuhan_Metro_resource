#pragma once

#include <assert.h>

#define Size 300

/************************************************************
	 结构体名称：MSTEdgeNode
	 功能描述：最小堆结点
	 作者：许鹏，王子越
*************************************************************/
struct MSTEdgeNode
{
	int tail, head;
	int key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
	// 重载操作符
	bool operator <=(MSTEdgeNode& R)
	{
		return key < R.key;
	}
	bool operator >=(MSTEdgeNode& R)
	{
		return key >= R.key;
	}
	bool operator >(MSTEdgeNode& R)
	{
		return key > R.key;
	}
};

/************************************************************
	 类名称：MinHeap
	 功能描述：最小堆
	 外部函数接口：构造函数，析构函数，Insert，RemoveMin，IsEmpty，IsFull
	 作者：许鹏，王子越
*************************************************************/
class MinHeap
{
public:
	//两种构造函数
	MinHeap(int sz = Size);
	MinHeap(MSTEdgeNode arr[], int n);
	// 插入元素
	bool Insert(const MSTEdgeNode& x);
	// 删除元素
	bool RemoveMin(MSTEdgeNode& x);
	// 析构函数
	~MinHeap()
	{
		delete[] head;
	}
	// 判断是否为空
	inline bool IsEmpty()const
	{
		return (currentSize == 0) ? true : false;
	}
	// 判断是否为满
	inline bool IsFull()const
	{
		return (currentSize == maxHeapSize) ? true : false;
	}

private:
	MSTEdgeNode* head;
	//当前元素大小
	int currentSize;
	//最大堆大小
	int maxHeapSize;
	// 下滑算法
	void siftDown(int start, int m);
	// 上滑算法
	void siftUp(int start);
};