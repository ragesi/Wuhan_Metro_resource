#include"pch.h"
#include "Minheap.h"
#include<assert.h>

/************************************************************
	 函数名称：MinHeap
	 功能描述：最小堆构造函数1
	 参数说明：默认建堆大小
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
MinHeap::MinHeap(int sz)
{
	maxHeapSize = (Size < sz) ? sz : Size;
	head = new MSTEdgeNode[maxHeapSize];
	assert(head != NULL);
	currentSize = 0;
}

/************************************************************
	 函数名称：MinHeap
	 功能描述：最小堆构造函数2
	 参数说明：默认建堆大小，结点数组
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
MinHeap::MinHeap(MSTEdgeNode arr[], int n)
{
	maxHeapSize = Size;
	head = new MSTEdgeNode[maxHeapSize];
	assert(head != NULL);
	// 根据结点数组，初始化堆结点大小
	for (int i = 0; i < n; i++)
	{
		head[i] = arr[i];
	}
	currentSize = n;
	// 设置好下滑算法起点
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

/************************************************************
	 函数名称：siftDown
	 功能描述：下滑算法建堆
	 参数说明：起点，终点
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void MinHeap::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	MSTEdgeNode temp = head[i];
	while (j <= m)
	{
		// 判断是否满足滑动条件，满足则调整位置，否则跳过
		if (j<m && head[j]>head[j + 1])j++;
		if (temp <= head[j])break;
		else
		{
			head[i] = head[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	head[i] = temp;
}

/************************************************************
	 函数名称：siftUp
	 功能描述：上滑算法建堆
	 参数说明：起点
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void MinHeap::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	MSTEdgeNode temp = head[j];
	while (j > 0)
	{
		// 判断是否满足滑动条件，满足则调整位置，否则跳过
		if (head[i] <= temp)break;
		else
		{
			head[j] = head[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	head[j] = temp;
}

/************************************************************
	 函数名称：Insert
	 功能描述：插入结点
	 参数说明：结点
	 返回值：插入成功情况
	 作者：许鹏，王子越
*************************************************************/
bool MinHeap::Insert(const MSTEdgeNode& x)
{
	if (currentSize == maxHeapSize)
	{
		return false;
	}
	head[currentSize] = x;
	// 插入以后，重新调整堆位置
	siftUp(currentSize);
	currentSize++;
	return true;
}

/************************************************************
	 函数名称：RemoveMin
	 功能描述：移除结点
	 参数说明：结点
	 返回值：移除成功情况
	 作者：许鹏，王子越
*************************************************************/
bool MinHeap::RemoveMin(MSTEdgeNode& x)
{
	if (!currentSize)
	{
		return false;
	}
	x = head[0];
	head[0] = head[currentSize - 1];
	currentSize--;
	// 移除以后，调整堆位置
	siftDown(0, currentSize - 1);
	return true;
}