// CBrowse.cpp: 实现文件
#include "pch.h"
#include"CLostAndFound.h"
#include"CSearchRoad.h"
#include "CLoginDlg.h"
#include "CBrowse.h"
#include "resource.h"
#include "MainFrm.h"
// CBrowse 对话框
IMPLEMENT_DYNAMIC(CBrowse, CDialogEx)
/************************************************************
	 函数名称：CBrowse
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
CBrowse::CBrowse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BROWSE, pParent)
	, m_list1(_T(""))
	, m_list3(_T(""))
	, m_list2(_T(""))
{
	//变量初始化
	m_one = 0;
	m_two = 1;
	m_three = 2;
	line.push_back(CString("1号线"));
	line.push_back(CString("2号线"));
	line.push_back(CString("3号线"));
	line.push_back(CString("4号线"));
	line.push_back(CString("6号线"));
	line.push_back(CString("7号线"));
	line.push_back(CString("8号线"));
	line.push_back(CString("11号线"));
	line.push_back(CString("阳逻线"));
}
/************************************************************
	 函数名称：CSearchRoad
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
CBrowse::~CBrowse()
{
}
/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void CBrowse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_list1);
	DDX_Text(pDX, IDC_EDIT6, m_list3);
	DDX_Text(pDX, IDC_EDIT5, m_list2);
}
BEGIN_MESSAGE_MAP(CBrowse, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CBrowse::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBrowse::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CBrowse::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CBrowse::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CBrowse::OnBnClickedButton6)
END_MESSAGE_MAP()
/************************************************************
	 函数名称：OnInitDialog
	 功能描述：初始化对话框
	 参数说明：无
	 返回值：bool型
	 作者：许鹏，王宇辰
*************************************************************/
BOOL CBrowse::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	//清空数据
	path.clear();
	m_list1 = m_list2 = m_list3 = CString("");
	//读取文件索引
	CMyFile mfile;
	CFile* file = new CFile();
	if (file->Open(CString("./res/lostandfind.txt"), CFile::modeRead | CFile::typeBinary))
	{
		mfile.ReadIndexFromFile(file, path);
		file->Close();
		delete file;
	}
	int size = path.size();
	//检测有无该失物招领启事，并且显示
	if (m_one <= size - 1)
	{
		m_list1 = Show(path[m_one]);
	}
	if (m_two <= size - 1)
	{
		m_list2 = Show(path[m_two]);
	}
	if (m_three <= size - 1)
	{
		m_list3 = Show(path[m_three]);
	}
	UpdateData(FALSE);
	//去除编辑框的全选操作
	CEdit* p = (CEdit*)GetDlgItem(IDC_EDIT5);
	p->SetFocus();
	p->SetSel(-1. - 1);
	return FALSE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
// CBrowse 消息处理程序
/************************************************************
	 函数名称：OnBnClickedButton2
	 功能描述：响应认领按钮按下操作
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CBrowse::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断是否为用户登录
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CWuhanMetroView* pView = (CWuhanMetroView*)pFrame->GetActiveView();
	//如果是游客登录
	if(pView->GetModel()==1)
	{ 
		MessageBox(L"请先登录后再认领！！", L"Warning！", MB_OK);
		return;
	}
	//如果是用户登录
	if (MessageBox(L"确定认领吗？", L"Tips", MB_YESNO) == IDYES)
	{
		//删除该目录
		CString temp;
		//该文件不存在
		if (path.size() <= m_one)
		{
			MessageBox(L"该招领启事不存在！", L"Warning！", MB_OK);
			return;
		}
		//文件存在，保存目录进行删除
		temp = path[m_one];
		path.erase(path.begin() + m_one);
		//处理信息
		Run(temp);
		m_list1 = CString("");
		UpdateData(0);
		//实现删除第一个的时候，如果后面没有信息了，这失物招领自动上移
		OnInitDialog();
	}
}
/************************************************************
	 函数名称：OnBnClickedButton3
	 功能描述：响应认领2按钮按下操作
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CBrowse::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断登录模式
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CWuhanMetroView* pView = (CWuhanMetroView*)pFrame->GetActiveView();
	//如果是游客登录
	if (pView->GetModel() == 1)
	{
		MessageBox(L"请先登录后再认领！！", L"Warning！", MB_OK);
		return;
	}
	//如果是用户登录
	if (MessageBox(L"确定认领吗？", L"Tips", MB_YESNO) == IDYES)
	{
		//删除该目录
		CString temp;
		//该文件不存在
		if (path.size() <= m_two)
		{
			MessageBox(L"该招领启事不存在！", L"Warning！", MB_OK);
			return;
		}
		//文件存在，保存目录进行删除
		temp = path[m_two];
		path.erase(path.begin() + m_two);
		//处理信息
		Run(temp);
		m_list2 = CString("");
		UpdateData(0);
		//实现删除第一个的时候，如果后面没有信息了，这失物招领自动上移
		OnInitDialog();
	}
}
/************************************************************
	 函数名称：OnBnClickedButton4
	 功能描述：响应认领3按钮按下操作
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CBrowse::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断登录模式
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CWuhanMetroView* pView = (CWuhanMetroView*)pFrame->GetActiveView();
	//如果是游客登录
	if (pView->GetModel() == 1)
	{
		MessageBox(L"请先登录后再认领！！", L"Warning！", MB_OK);
		return;
	}
	//如果是用户登录
	if (MessageBox(L"确定认领吗？", L"Tips", MB_YESNO) == IDYES)
	{
		//删除该目录
		CString temp;
		//该文件不存在
		if (path.size() <= m_three)
		{
			MessageBox(L"该招领启事不存在！", L"Warning！", MB_OK);
			return;
		}
		//文件存在，保存目录进行删除
		temp = path[m_three];
		path.erase(path.begin() + m_three);
		//处理信息
		Run(temp);
		m_list3 = CString("");
		UpdateData(0);
		//实现删除第一个的时候，如果后面没有信息了，这失物招领自动上移
		OnInitDialog();
	}
}
/************************************************************
	 函数名称：OnBnClickedButton5
	 功能描述：重绘编辑框的文字
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CBrowse::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//如果不是第一页
	if (m_one - 3 <= path.size() - 1)
	{
		m_one -= 3;
		m_two -= 3;
		m_three -= 3;
		//重绘对话框的数据
		OnInitDialog();
	}
	else {
		MessageBox(L"翻到第一页了哦", L"Tips", MB_OK);
	}
}
/************************************************************
	 函数名称：OnBnClickedButton6
	 功能描述：重绘编辑框的文字
	 参数说明：无
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CBrowse::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//否则就意味着没有内容了
	if (m_one + 3 <= path.size() - 1)
	{
		m_one += 3;
		m_two += 3;
		m_three += 3;
		//重绘对话框的数据
		OnInitDialog();
	}
	else {
		MessageBox(L"翻到底了哦", L"Tips", MB_OK);
	}
}
/************************************************************
	 函数名称：Show
	 功能描述：在编辑框中显示失物招领的内容
	 参数说明：无
	 返回值：CString
	 作者：许鹏，王宇辰
*************************************************************/
CString CBrowse::Show(CString p)
{
	CMyFile mfile;
	CFile* File = new CFile();
	CString temp_path = CString("./res/失物招领/") + p + CString(".txt");
	//如果成功打开失物招领文件夹
	if (File->Open(temp_path, CFile::modeRead))
	{
		//初始化信息
		CString time = CString("");
		int Line = 0, station = 0;
		CString s_name = CString(""), l_name = CString("");
		CString content = CString("");
		//读取文件信息
		mfile.ReadFile(File, content, time, Line, station);
		File->Close();
		delete File;
		//接下来读取站点
		CFile* file = new CFile();
		CString m;
		m.Format(_T("%d"), Line);
		CString path = CString("./res/information/") + m + CString(".txt");
		vector<CString>s_station;
		//如果成功打开information.txt
		if (file->Open(path, CFile::modeRead))
		{
			//读取站点信息
			mfile.ReadOneLineStationFromFile(file, s_station);
			file->Close();
			delete file;
			//获取站点
			s_name = s_station[station];
			//获取线路
			l_name = line[Line - 1];

			//显示到对话框内容
			CString result = CString("");
			result += (CString("时间：") + time + CString("\r\n"));
			result += (CString("线路：") + l_name + CString("   站点：") + s_name + CString("\r\n"));
			result += (CString("详细信息：") + content);
			return result;
		}
		else
		{
			MessageBox(L"该失物招领文件不存在！", L"Warning!", MB_OK);
			return CString("");
		}
	}
	else
	{
		MessageBox(L"该失物招领文件不存在！", L"Warning!", MB_OK);
		return CString("");
	}
}
/************************************************************
	 函数名称：Run
	 功能描述：处理失物招领信息
	 参数说明：CString型
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CBrowse::Run(CString temp)
{
	//重写索引文件
	CMyFile mfile;
	CFile* file = new CFile();
	//如果成功打开失物招领索引文件
	if (file->Open(CString("./res/lostandfind.txt"), CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary))
	{
		mfile.WriteFileToIndex(file, path);
		file->Close();
		delete file;
	}
	//准备移除文件
	CFile* File = new CFile();
	CString cstrLoadPathName;
	//获取路径
	mfile.GetPath(cstrLoadPathName);
	cstrLoadPathName += (CString("res\\失物招领\\") + temp + CString(".txt"));
	File->Remove(cstrLoadPathName);
	//如果成功打开当前编辑框内容的文档
	if (!File->Open(cstrLoadPathName, CFile::modeRead))
	{
		MessageBox(L"认领成功，请尽快取走物品！", L"Tips", MB_OK);
	}
	else
	{
		MessageBox(L"认领失败！", L"Tips", MB_OK);
		File->Close();
	}
	delete File;
}
