#include"pch.h"
#include"Graphlnk.h"

/************************************************************
	 函数名称：Graphlnk
	 功能描述：图的默认构造函数
	 参数说明：默认建图大小
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
Graphlnk::Graphlnk(int sz)
{
	// 初始化信息
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	distance = 0;
	num = 0;
	NodeTable = new Vertex[maxVertices];
	// 读取文件
	// 此处可换成绝对路径
	CString FilePath = CString("./res/站点.txt");
	CFile* file = new CFile();
	if (file->Open(FilePath, CFile::modeRead))
	{
		CMyFile myfile;
		myfile.ReadAllStationFromFile(file, PlaceInfor);
		file->Close();
		delete file;
	}
	assert(NodeTable != NULL);
	// 初始化指针数组
	for (int i = 0; i < maxVertices; i++) 
	{
		NodeTable[i].adj = NULL;
	}
	CreateGraphlnk();
}

/************************************************************
	 函数名称：~Graphlnk
	 功能描述：图的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
Graphlnk::~Graphlnk() 
{
	for (int i = 0; i < numVertices; i++) 
	{
		// 依次释放邻接表所有节点
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
	 函数名称：getFirstNeighbor
	 功能描述：获取当前结点的第一个邻居
	 参数说明：当前结点序号
	 返回值：邻居结点序号
	 作者：许鹏，王子越
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
	 函数名称：getNextNeighbor
	 功能描述：获取当前结点的下一个邻居
	 参数说明：当前结点序号，当前结点的第一个邻居
	 返回值：下一个邻居结点序号
	 作者：许鹏，王子越
*************************************************************/
int Graphlnk::getNextNeighbor(int v, int w)
{
	if (v != -1) {
		Edge* p = NodeTable[v].adj;
		//找到邻居
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
	 函数名称：getWeight
	 功能描述：获取某条边的权值
	 参数说明：边的头尾结点
	 返回值：边权值
	 作者：许鹏，王子越
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
	 函数名称：insertVertex
	 功能描述：插入一个结点
	 参数说明：结点序号
	 返回值：插入是否成功
	 作者：许鹏，王子越
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
	 函数名称：insertEdge
	 功能描述：插入一条边
	 参数说明：边首节点，边尾结点，边权值
	 返回值：插入是否成功
	 作者：许鹏，王子越
*************************************************************/
bool Graphlnk::insertEdge(int v1, int v2, int weight)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		// 找到插入位置
		Edge* q, * p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) 
		{
			p = p->link;
		}
		if (p != NULL)
		{
			return false;
		}
		// 插入邻接表的两个位置
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
	 函数名称：CreateGraphlnk
	 功能描述：从文件中读入数据创建一个图
	 参数说明：无
	 返回值：无
	 注：采用ifstream读取文件，避免换行符干扰，不纳入文件读取类
	 作者：许鹏，王子越
*************************************************************/
void Graphlnk::CreateGraphlnk() 
{
	// 首站点
	int head = 0;
	// 尾站点
	int rear = 0;
	// 距离
	int distance = 0;
	// 读取的地铁站点号
	int num = 0;
	// 读取字符
	char k;
	// 打开文件
	const char* name = "路线规划.txt";
	ifstream infile(name, ios::in | ios::binary);
	if (!infile.is_open())
	{
		// 文件打开失败
		assert(0);
	}

	infile >> k;
	// 初始化站点
	while (k != '#') {
		while (k != ';' && k != '#')
		{
			num = num * 10 + k - 48;
			infile >> k;
		}
		// 插入站点
		insertVertex(num);
		num = 0;
		if (k != '#')
		{
			infile >> k;
		}
	}
	infile >> k;
	int count = 0;
	// 初始化边
	while (k != '#')
	{
		if (k == '(')
		{
			infile >> k;
			// 找到head
			while (k != ',')
			{
				head = (head * 10 + k - 48);
				infile >> k;
			}
			head = getVertexPos(head);
			// 找到rear
			infile >> k;
			while (k != ',')
			{
				rear = (rear * 10 + k - 48);
				infile >> k;
			}
			rear = getVertexPos(rear);
			// 找到距离distance
			infile >> k;
			while (k != ')')
			{
				distance = distance * 10 + k - 48;
				infile >> k;
			}
			//插入边
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
	 函数名称：ShortestPath
	 功能描述：计算某个点到全图点的最短路径
	 参数说明：图，起点，距离数组，路径数组
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void Graphlnk::ShortestPath(Graphlnk& G, int v, int  dist[], int path[]) 
{
	int n = G.numVertices;
	bool* S = new bool[n];
	int i, j, k;
	int w, min;
	// 初始化两个数组
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
	// 开始计算最短路径
	for (i = 0; i < n - 1; i++) {
		min = maxValue;
		int u = v;
		// 初始化访问，加入访问区
		for (j = 0; j < n; j++) {
			if (S[j] == false && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		// 若找到更短路径则更新
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
	 函数名称：PrintShortestPath
	 功能描述：打印某个点到终点的最短路径
	 参数说明：图，起点，终点，路径数组，待更改的路径变量
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void Graphlnk::PrintShortestPath(Graphlnk& G, int v, int last, int path[], CString& mypath) {
	// 保存当前路径使用的站点序号
	station.clear();
	// 判断是否起点和终点重合
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
		// 获取到路径
		while (last != v)
		{
			d[k++] = last;
			last = path[last];
		}
		// 载入站点信息，构造路径
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