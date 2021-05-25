// CSearchRoad.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "CSearchRoad.h"
#include "afxdialogex.h"
#include "Graphlnk.h"


// CSearchRoad 对话框

IMPLEMENT_DYNAMIC(CSearchRoad, CDialogEx)
/************************************************************
	 函数名称：CSearchRoad
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
CSearchRoad::CSearchRoad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCH_ROAD, pParent)
	, m_distance(_T(""))
	, m_cost(_T(""))
	, m_path(_T(""))
	, m_num(_T(""))
	, m_s_line(0)
	, m_e_line(0)
{

}

/************************************************************
	 函数名称：CSearchRoad
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
CSearchRoad::~CSearchRoad()
{
}

/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void CSearchRoad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_distance);
	DDX_Text(pDX, IDC_EDIT2, m_cost);
	DDX_Text(pDX, IDC_EDIT3, m_path);
	DDX_Control(pDX, IDC_COMBO1, m_s_l);
	DDX_Control(pDX, IDC_COMBO2, m_s_s);
	DDX_Control(pDX, IDC_COMBO3, m_e_l);
	DDX_Control(pDX, IDC_COMBO4, m_e_s);
	DDX_Text(pDX, IDC_EDIT4, m_num);
	DDX_CBIndex(pDX, IDC_COMBO1, m_s_line);
	DDX_CBIndex(pDX, IDC_COMBO3, m_e_line);
}


BEGIN_MESSAGE_MAP(CSearchRoad, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchRoad::OnBnClickedSearchRoad)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSearchRoad::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSearchRoad::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CSearchRoad 消息处理程序

/************************************************************
	 函数名称：OnBnClickedSearchRoad
	 功能描述：响应查询按钮按下操作
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void CSearchRoad::OnBnClickedSearchRoad()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int p = m_s_s.GetCurSel();
	int q = m_e_s.GetCurSel();
	//判断是否输入站点
	if (p != -1 && q != -1)
	{
		Graphlnk G(211);
		int m[211], n[211];
		for (int i = 0; i < 211; i++) {
			m[i] = n[i] = maxValue;
		}
		int start, end;
		// 找出当前选择站点对应的序号start和end
		for (int i = 0; i < 211; i++)
		{
			if (G.PlaceInfor[i] == s[p])
			{
				start = i;
			}
			if (G.PlaceInfor[i] == e[q])
			{
				end = i;
			}
		}
		// 找到最短路径并且打印
		CString path = CString("");
		G.ShortestPath(G, start, n, m);
		G.PrintShortestPath(G, start, end, m, path);
		// 打印其他信息
		distance = n[end] * 2;
		m_cost.Format(_T("%d"), Cost(distance));
		m_distance.Format(_T("%d"), distance);
		m_num.Format(_T("%d"), Transform(G.station));
		m_path = path;
	}
	else
	{
		MessageBox(L"您还未输入线路数据！", L"Warning", MB_OK);
		return;
	}
	UpdateData(FALSE);
}

/************************************************************
	 函数名称：OnCbnSelchangeCombo1
	 功能描述：起点线路下拉框选择时对应的站点要发生变化
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void CSearchRoad::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//读取站点信息
	UpdateData(1);
	CFile* File = new CFile();
	CString a;
	if (m_s_line == start)
	{
		a.Format(_T("%d"), start - 1);
	}
	else
	{
		a.Format(_T("%d"), m_s_line - 1);
	}
	CString path = CString("./res/information/") + a + CString(".txt");
	vector<CString>station;
	if (File->Open(path, CFile::modeRead))
	{
		CMyFile myfile;
		myfile.ReadOneLineStationFromFile(File, station);
		File->Close();
		delete File;
		s = station;
		//填入信息
		m_s_s.ResetContent();
		for (int i = 0; i < station.size(); i++)
		{
			m_s_s.AddString(station[i]);
		}

	}
	else
	{
		//重置所有信息，防止使用前一次输入的数据进行查询
		m_s_s.ResetContent();
		//变成“请输入”时不弹出对话框
		if (a != CString("-1"))
		{
			MessageBox(L"线路信息不存在！", L"Warning", MB_OK);
		}
		return;
	}

}
/************************************************************
	 函数名称：OnCbnSelchangeCombo3
	 功能描述：终点线路下拉框选择时对应的站点要发生变化
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void CSearchRoad::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	//读取站点信息
	UpdateData(1);
	CFile* File = new CFile();
	CString a;
	if (m_e_line == end)
	{
		a.Format(_T("%d"), end - 1);
	}
	else
	{
		a.Format(_T("%d"), m_e_line - 1);
	}
	CString path = CString("./res/information/") + a + CString(".txt");
	vector<CString>station;
	if (File->Open(path, CFile::modeRead))
	{
		CMyFile myfile;
		myfile.ReadOneLineStationFromFile(File, station);
		File->Close();
		delete File;
		e = station;
		//填入信息
		m_e_s.ResetContent();
		for (int i = 0; i < station.size(); i++)
		{
			m_e_s.AddString(station[i]);
		}

	}
	else
	{
		//重置所有信息，防止使用前一次输入的数据进行查询
		m_e_s.ResetContent();
		if (a != CString("-1"))
		{
			MessageBox(L"线路信息不存在！", L"Warning", MB_OK);
		}
		return;
	}

}

/************************************************************
	 函数名称：Transform
	 功能描述：计算换乘数
	 参数说明：最短路径中的涉及的站点数组
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
int CSearchRoad::Transform(vector<int> a)
{
	vector <vector<int>> b;
	b.resize(211);

	int count = 0;
	for (int i = 0; i < a.size(); i++)
	{
		// 所有换乘站
		if (a[i] == 42 || a[i] == 91 || a[i] == 52 || a[i] == 39 || a[i] == 30
			|| a[i] == 45 || a[i] == 71 || a[i] == 93 || a[i] == 28 || a[i] == 34 || a[i] == 32
			|| a[i] == 92 || a[i] == 124 || a[i] == 62 || a[i] == 19 || a[i] == 59 || a[i] == 38
			|| a[i] == 35 || a[i] == 65 || a[i] == 170 || a[i] == 156 || a[i] == 129 || a[i] == 60
			|| a[i] == 120 || a[i] == 29 || a[i] == 67)
		{
			// 出发点或者终点在换乘点上都不算换乘
			if (i != 0 && i != a.size() - 1)
			{
				if (GetLineNum(a[i - 1]) != GetLineNum(a[i + 1]))
				{
					count++;
				}
			}
		}
	}
	return count;
}

/************************************************************
	 函数名称：Cost
	 功能描述：计算花费
	 参数说明：路径长度
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
int CSearchRoad::Cost(int a)
{
	if (a == 0)
	{
		return 0;
	}
	else if (a <= 4)
	{
		return 2;
	}
	else if (a <= 8)
	{
		return 3;
	}
	else if (a <= 12)
	{
		return 4;
	}
	else if (a <= 18)
	{
		return 5;
	}
	else if (a <= 24)
	{
		return 6;
	}
	else if (a <= 32)
	{
		return 7;
	}
	else if (a <= 40)
	{
		return 8;
	}
	else if (a <= 50)
	{
		return 9;
	}
	else if(a<=70)
	{
		return 10;
	}
	else if (a <= 90)
	{
		return 11;
	}
	else if (a <= 110)
	{
		return 12;
	}
	else if (a <= 130) 
	{
		return 13;
	}
	else if (a <= 150)
	{
		return 14;
	}
	else if (a <= 170)
	{
		return 15;
	}
	else if (a <= 190)
	{
		return 16;
	}
	else if (a <= 210)
	{
		return 17;
	}
	else if (a <= 230)
	{
		return 18;
	}
	return -1;
}

/************************************************************
	 函数名称：GetLineNum
	 功能描述：获取某个站点所在的线路
	 参数说明：站点序号
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
int CSearchRoad::GetLineNum(int a)
{
	//根据站点文档进行更改
	if (a >= 1 && a <= 13)
	{
		return 11;
	}
	else if ((a >= 14 && a <= 50) || a == 182)
	{
		return 2;
	}
	else if (a >= 51 && a <= 72)
	{
		return 3;
	}
	else if (a >= 73 && a <= 102)
	{
		return 1;
	}
	else if (a >= 103 && a <= 136)
	{
		return 4;
	}
	else if (a >= 137 && a <= 158)
	{
		return 6;
	}
	else if (a >= 159 && a <= 177)
	{
		return 7;
	}
	else if ((a >= 178 && a <= 181) || a == 162 || (a >= 185 && a <= 193) || (a >= 195 && a <= 198) || a == 200 || a == 201)
	{
		return 8;
	}
	else if (a == 71 || (a >= 202 && a <= 211) || a == 194 || a == 184 || a == 199 || a == 183)
	{
		return 21;
	}
	else
		return -1;
}