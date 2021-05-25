#include"pch.h"
#include "Minheap.h"
#include<assert.h>

/************************************************************
	 �������ƣ�MinHeap
	 ������������С�ѹ��캯��1
	 ����˵����Ĭ�Ͻ��Ѵ�С
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
MinHeap::MinHeap(int sz)
{
	maxHeapSize = (Size < sz) ? sz : Size;
	head = new MSTEdgeNode[maxHeapSize];
	assert(head != NULL);
	currentSize = 0;
}

/************************************************************
	 �������ƣ�MinHeap
	 ������������С�ѹ��캯��2
	 ����˵����Ĭ�Ͻ��Ѵ�С���������
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
MinHeap::MinHeap(MSTEdgeNode arr[], int n)
{
	maxHeapSize = Size;
	head = new MSTEdgeNode[maxHeapSize];
	assert(head != NULL);
	// ���ݽ�����飬��ʼ���ѽ���С
	for (int i = 0; i < n; i++)
	{
		head[i] = arr[i];
	}
	currentSize = n;
	// ���ú��»��㷨���
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

/************************************************************
	 �������ƣ�siftDown
	 �����������»��㷨����
	 ����˵������㣬�յ�
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
void MinHeap::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	MSTEdgeNode temp = head[i];
	while (j <= m)
	{
		// �ж��Ƿ����㻬�����������������λ�ã���������
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
	 �������ƣ�siftUp
	 �����������ϻ��㷨����
	 ����˵�������
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
void MinHeap::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	MSTEdgeNode temp = head[j];
	while (j > 0)
	{
		// �ж��Ƿ����㻬�����������������λ�ã���������
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
	 �������ƣ�Insert
	 ����������������
	 ����˵�������
	 ����ֵ������ɹ����
	 ���ߣ�����������Խ
*************************************************************/
bool MinHeap::Insert(const MSTEdgeNode& x)
{
	if (currentSize == maxHeapSize)
	{
		return false;
	}
	head[currentSize] = x;
	// �����Ժ����µ�����λ��
	siftUp(currentSize);
	currentSize++;
	return true;
}

/************************************************************
	 �������ƣ�RemoveMin
	 �����������Ƴ����
	 ����˵�������
	 ����ֵ���Ƴ��ɹ����
	 ���ߣ�����������Խ
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
	// �Ƴ��Ժ󣬵�����λ��
	siftDown(0, currentSize - 1);
	return true;
}