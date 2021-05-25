#include"pch.h"
#include"Graphlnk.h"

/************************************************************
	 �������ƣ�Graphlnk
	 ����������ͼ��Ĭ�Ϲ��캯��
	 ����˵����Ĭ�Ͻ�ͼ��С
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
Graphlnk::Graphlnk(int sz)
{
	// ��ʼ����Ϣ
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	distance = 0;
	num = 0;
	NodeTable = new Vertex[maxVertices];
	// ��ȡ�ļ�
	// �˴��ɻ��ɾ���·��
	CString FilePath = CString("./res/վ��.txt");
	CFile* file = new CFile();
	if (file->Open(FilePath, CFile::modeRead))
	{
		CMyFile myfile;
		myfile.ReadAllStationFromFile(file, PlaceInfor);
		file->Close();
		delete file;
	}
	assert(NodeTable != NULL);
	// ��ʼ��ָ������
	for (int i = 0; i < maxVertices; i++) 
	{
		NodeTable[i].adj = NULL;
	}
	CreateGraphlnk();
}

/************************************************************
	 �������ƣ�~Graphlnk
	 ����������ͼ��Ĭ����������
	 ����˵������
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
Graphlnk::~Graphlnk() 
{
	for (int i = 0; i < numVertices; i++) 
	{
		// �����ͷ��ڽӱ����нڵ�
		Edge* p = NodeTable[i].adj;
		while (p != NULL) 
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}

/************************************************************
	 �������ƣ�getFirstNeighbor
	 ������������ȡ��ǰ���ĵ�һ���ھ�
	 ����˵������ǰ������
	 ����ֵ���ھӽ�����
	 ���ߣ�����������Խ
*************************************************************/
int Graphlnk::getFirstNeighbor(int v)
{
	if (v != -1) {
		Edge* p = NodeTable[v].adj;
		if (p != NULL) 
		{
			return p->dest;
		}
	}
	return -1;
}

/************************************************************
	 �������ƣ�getNextNeighbor
	 ������������ȡ��ǰ������һ���ھ�
	 ����˵������ǰ�����ţ���ǰ���ĵ�һ���ھ�
	 ����ֵ����һ���ھӽ�����
	 ���ߣ�����������Խ
*************************************************************/
int Graphlnk::getNextNeighbor(int v, int w)
{
	if (v != -1) {
		Edge* p = NodeTable[v].adj;
		//�ҵ��ھ�
		while (p != NULL && p->dest != w) 
		{
			p = p->link;
		}
		if (p != NULL && p->link != NULL) 
		{
			return p->link->dest;
		}
	}
	return -1;
}

/************************************************************
	 �������ƣ�getWeight
	 ������������ȡĳ���ߵ�Ȩֵ
	 ����˵�����ߵ�ͷβ���
	 ����ֵ����Ȩֵ
	 ���ߣ�����������Խ
*************************************************************/
int Graphlnk::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL) 
		{
			return p->cost;
		}
	}
	return maxValue;
}

/************************************************************
	 �������ƣ�insertVertex
	 ��������������һ�����
	 ����˵����������
	 ����ֵ�������Ƿ�ɹ�
	 ���ߣ�����������Խ
*************************************************************/
bool Graphlnk::insertVertex(const int& vertex) 
{
	if (numVertices == maxVertices)
	{
		return false;
	}
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

/************************************************************
	 �������ƣ�insertEdge
	 ��������������һ����
	 ����˵�������׽ڵ㣬��β��㣬��Ȩֵ
	 ����ֵ�������Ƿ�ɹ�
	 ���ߣ�����������Խ
*************************************************************/
bool Graphlnk::insertEdge(int v1, int v2, int weight)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		// �ҵ�����λ��
		Edge* q, * p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) 
		{
			p = p->link;
		}
		if (p != NULL)
		{
			return false;
		}
		// �����ڽӱ������λ��
		p = new Edge;
		q = new Edge;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

/************************************************************
	 �������ƣ�CreateGraphlnk
	 �������������ļ��ж������ݴ���һ��ͼ
	 ����˵������
	 ����ֵ����
	 ע������ifstream��ȡ�ļ������⻻�з����ţ��������ļ���ȡ��
	 ���ߣ�����������Խ
*************************************************************/
void Graphlnk::CreateGraphlnk() 
{
	// ��վ��
	int head = 0;
	// βվ��
	int rear = 0;
	// ����
	int distance = 0;
	// ��ȡ�ĵ���վ���
	int num = 0;
	// ��ȡ�ַ�
	char k;
	// ���ļ�
	const char* name = "·�߹滮.txt";
	ifstream infile(name, ios::in | ios::binary);
	if (!infile.is_open())
	{
		// �ļ���ʧ��
		assert(0);
	}

	infile >> k;
	// ��ʼ��վ��
	while (k != '#') {
		while (k != ';' && k != '#')
		{
			num = num * 10 + k - 48;
			infile >> k;
		}
		// ����վ��
		insertVertex(num);
		num = 0;
		if (k != '#')
		{
			infile >> k;
		}
	}
	infile >> k;
	int count = 0;
	// ��ʼ����
	while (k != '#')
	{
		if (k == '(')
		{
			infile >> k;
			// �ҵ�head
			while (k != ',')
			{
				head = (head * 10 + k - 48);
				infile >> k;
			}
			head = getVertexPos(head);
			// �ҵ�rear
			infile >> k;
			while (k != ',')
			{
				rear = (rear * 10 + k - 48);
				infile >> k;
			}
			rear = getVertexPos(rear);
			// �ҵ�����distance
			infile >> k;
			while (k != ')')
			{
				distance = distance * 10 + k - 48;
				infile >> k;
			}
			//�����
			insertEdge(head, rear, distance);
			head = 0;
			rear = 0;
			distance = 0;
			infile >> k;
		}
	}
	infile.close();
}

/************************************************************
	 �������ƣ�ShortestPath
	 ��������������ĳ���㵽ȫͼ������·��
	 ����˵����ͼ����㣬�������飬·������
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
void Graphlnk::ShortestPath(Graphlnk& G, int v, int  dist[], int path[]) 
{
	int n = G.numVertices;
	bool* S = new bool[n];
	int i, j, k;
	int w, min;
	// ��ʼ����������
	for (i = 0; i < n; i++) 
	{
		dist[i] = G.getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] < maxValue) {
			path[i] = v;
		}
		else {
			path[i] = -1;
		}
		S[v] = true;
		dist[v] = 0;
	}
	// ��ʼ�������·��
	for (i = 0; i < n - 1; i++) {
		min = maxValue;
		int u = v;
		// ��ʼ�����ʣ����������
		for (j = 0; j < n; j++) {
			if (S[j] == false && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		// ���ҵ�����·�������
		for (k = 0; k < n; k++) {
			w = G.getWeight(u, k);
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k]) {
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}

}

/************************************************************
	 �������ƣ�PrintShortestPath
	 ������������ӡĳ���㵽�յ�����·��
	 ����˵����ͼ����㣬�յ㣬·�����飬�����ĵ�·������
	 ����ֵ����
	 ���ߣ�����������Խ
*************************************************************/
void Graphlnk::PrintShortestPath(Graphlnk& G, int v, int last, int path[], CString& mypath) {
	// ���浱ǰ·��ʹ�õ�վ�����
	station.clear();
	// �ж��Ƿ������յ��غ�
	if (last == v)
	{
		mypath += PlaceInfor[v];
		mypath += "-->";
		mypath += PlaceInfor[v];
		num += 1;
		station.push_back(v + 1);
	}
	else 
	{
		int i, k = 0, n = G.numVertices;
		int* d = new int[n];
		int temp = last;
		// ��ȡ��·��
		while (last != v)
		{
			d[k++] = last;
			last = path[last];
		}
		// ����վ����Ϣ������·��
		mypath += PlaceInfor[v];
		mypath += "-->";
		station.push_back(v + 1);
		num += 1;
		while (k > 0 && temp != v) 
		{
			k--;
			mypath += PlaceInfor[d[k]];
			num += 1;
			station.push_back(d[k] + 1);
			if (k != 0) {
				mypath += "-->";
			}
		}
		delete[]d;
	}
}