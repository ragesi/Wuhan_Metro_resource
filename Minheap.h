#pragma once

#include <assert.h>

#define Size 300

/************************************************************
	 �ṹ�����ƣ�MSTEdgeNode
	 ������������С�ѽ��
	 ���ߣ�����������Խ
*************************************************************/
struct MSTEdgeNode
{
	int tail, head;
	int key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
	// ���ز�����
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
	 �����ƣ�MinHeap
	 ������������С��
	 �ⲿ�����ӿڣ����캯��������������Insert��RemoveMin��IsEmpty��IsFull
	 ���ߣ�����������Խ
*************************************************************/
class MinHeap
{
public:
	//���ֹ��캯��
	MinHeap(int sz = Size);
	MinHeap(MSTEdgeNode arr[], int n);
	// ����Ԫ��
	bool Insert(const MSTEdgeNode& x);
	// ɾ��Ԫ��
	bool RemoveMin(MSTEdgeNode& x);
	// ��������
	~MinHeap()
	{
		delete[] head;
	}
	// �ж��Ƿ�Ϊ��
	inline bool IsEmpty()const
	{
		return (currentSize == 0) ? true : false;
	}
	// �ж��Ƿ�Ϊ��
	inline bool IsFull()const
	{
		return (currentSize == maxHeapSize) ? true : false;
	}

private:
	MSTEdgeNode* head;
	//��ǰԪ�ش�С
	int currentSize;
	//���Ѵ�С
	int maxHeapSize;
	// �»��㷨
	void siftDown(int start, int m);
	// �ϻ��㷨
	void siftUp(int start);
};