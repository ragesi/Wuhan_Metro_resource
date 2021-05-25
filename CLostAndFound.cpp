// CLostAndFound.cpp: 实现文件
#include "pch.h"
#include "Wuhan_Metro.h"
#include "CLostAndFound.h"
#include "afxdialogex.h"
#include"CMyFile.h"
using namespace std;
// CLostAndFound 对话框
IMPLEMENT_DYNAMIC(CLostAndFound, CDialogEx)
/************************************************************
	 函数名称：CLostAndFound
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
CLostAndFound::CLostAndFound(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOST_FOUND, pParent)
	, m_content(_T(""))
	, m_station(0)
{
	num = 0;
}
/************************************************************
	 函数名称：CLostAndFound
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
CLostAndFound::~CLostAndFound()
{
}
/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void CLostAndFound::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_content);
	DDX_Control(pDX, IDC_COMBO1, m_line);
	DDX_Control(pDX, IDC_COMBO2, m_spot);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_CBIndex(pDX, IDC_COMBO2, m_station);
	DDX_Control(pDX, IDCANCEL, lostandfound);
}
BEGIN_MESSAGE_MAP(CLostAndFound, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLostAndFound::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CLostAndFound::OnCbnSelchangeCombo1)
	//ON_EN_CHANGE(IDC_EDIT1, &CLostAndFound::OnEnChangeEdit1)
END_MESSAGE_MAP()
// CLostAndFound 消息处理程序
/************************************************************
	 函数名称：OnBnClickedButton1
	 功能描述：响应保存按钮按下操作
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CLostAndFound::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取站点信息
	int line = m_line.GetCurSel();
	int station = m_spot.GetCurSel();
	CString Line, Station;
	// 检查是否选择站点
	Line.Format(_T("%d"), line);
	Station.Format(_T("%d"), station);
	//如果未选择站点信息，弹出提醒对话框
	if (line == -1 || station == -1) 
	{
		MessageBox(L"请选择站点信息！", L"Warning", MB_OK);
		return;
	}
	// 获取文件目录(进行信息初始化)
	path.clear();
	CFile* m_l = new CFile();
	//打开失物招领索引文件成功
	if (m_l->Open(CString("./res/lostandfind.txt"), CFile::modeRead | CFile::typeBinary))
	{
		CMyFile myfile;
		myfile.ReadIndexFromFile(m_l, path);
		m_l->Close();
		delete m_l;

	}
	//保证num为可写入的最大值
	if (path.size() != 0)
	{
		num = _ttoi(path[path.size() - 1]) + 1;
	}
	//获取时间
	UpdateData(1);
	CTime Time;
	CString szDate;
	CDateTimeCtrl* pCtrl = &this->m_date;
	DWORD dwResult = pCtrl->GetTime(Time);
	if (dwResult == GDT_VALID)
	{
		szDate = Time.Format(TEXT("%Y/%m/%d"));
	}
	if (m_content.IsEmpty())  //判断是否为空
	{
		MessageBox(L"请输入详细信息", L"Warning", MB_OK);
		return;

	}
	for (int i = 0;i < m_content.GetLength();i++)
	{
		if (m_content.GetAt(i) == '#')
		{
			MessageBox(L"请勿输入#字符！", L"Warning", MB_OK);
			return;
		}
	}

	//写入文件
	CString cstrLoadPathName;
	CMyFile mfile;
	mfile.GetPath(cstrLoadPathName);
	//写入索引文件
	CString p;
	p.Format(_T("%d"), num);
	//获取索引文件路径和目录文件路径
	CString Name = cstrLoadPathName + CString("res\\lostandfind.txt");
	cstrLoadPathName = cstrLoadPathName + CString("res\\失物招领\\") + p + CString(".txt");
	path.push_back(p);
	CFile* File = new CFile();
	if (File->Open(Name, CFile::modeCreate | CFile::typeBinary | CFile::modeReadWrite))
	{
		//写入索引文件
		CMyFile file;
		file.WriteFileToIndex(File,path);
		File->Close();
	    delete File;
	}
	//如果未打开文件
	else
	{
		MessageBox(L"未打开索引文件！", L"Tips", MB_OK);
		return;
	}
	//创建失物招领启事，并且写入信息
	CFile* file = new CFile();
	if (file->Open(cstrLoadPathName, CFile::modeCreate | CFile::typeBinary | CFile::modeReadWrite))
	{
		//写入失物招领信息
		CMyFile File;
		File.WriteInformation(file, szDate,Line,Station,m_content);
		//判断失物招领中是否有非法字符
		MessageBox(L"发布成功！", L"Tips", MB_OK);
		file->Close();
		delete file;
	}
	else
	{
		MessageBox(L"未打开文件！", L"Tips", MB_OK);
		return;
	}
	m_content = CString("");
	UpdateData(0);
}
/************************************************************
	 函数名称：OnCbnSelchangeCombo1
	 功能描述：选择捡到物品线路下拉框选择时对应的站点要发生变化
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CLostAndFound::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取下拉框1选中的行
	//读取站点信息
	UpdateData(1);
	CFile* File = new CFile();
	CString a;
	int m_road = m_line.GetCurSel();
	if (m_road == start)
	{
		a.Format(_T("%d"), start - 1);
	}
	else
	{
		a.Format(_T("%d"), m_road - 1);
	}
	CString path = CString("./res/information/") + a + CString(".txt");
	vector<CString>station;
	if (File->Open(path, CFile::modeRead))
	{
		// 读取某条线站点信息到数组
		CMyFile myfile;
		myfile.ReadOneLineStationFromFile(File, station);
		File->Close();
		delete File;
		s = station;
		//填入信息
		m_spot.ResetContent();
		for (int i = 0; i < station.size(); i++)
		{
			m_spot.AddString(station[i]);
		}

	}
	else
	{

		MessageBox(L"线路信息不存在！", L"Warning", MB_OK);
		return;
	}
}

