// Cperinformation.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "Cperinformation.h"
#include "afxdialogex.h"
#include"CMyFile.h"
#include"Cchangepassword.h"
#include "MainFrm.h"
#include "Wuhan_MetroView.h"
#include "CLoginDlg.h"

// Cperinformation 对话框

IMPLEMENT_DYNAMIC(Cperinformation, CDialogEx)
/************************************************************
	 函数名称：Cperinformation
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
Cperinformation::Cperinformation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PER_INFORMATION, pParent)
	, m_name(_T(""))
	, m_password(_T(""))
	, m_age(_T(""))
{
	flag = true;
}
/************************************************************
	 函数名称：~Cperinformation
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
Cperinformation::~Cperinformation()
{
}
/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void Cperinformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_age);
	DDX_Control(pDX, IDC_COMBO1, m_sex);
	DDX_Control(pDX, IDC_COMBO2, m_start1);
	DDX_Control(pDX, IDC_COMBO3, m_start2);
	DDX_Control(pDX, IDC_COMBO4, m_end1);
	DDX_Control(pDX, IDC_COMBO5, m_end2);
	DDX_Control(pDX, IDC_BUTTON1, m_changepassword);
}


BEGIN_MESSAGE_MAP(Cperinformation, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cperinformation::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Cperinformation::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Cperinformation::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, &Cperinformation::OnCbnSelchangeCombo4)
END_MESSAGE_MAP()


// Cperinformation 消息处理程序


/************************************************************
	 函数名称：OnInitDialog
	 功能描述：初始化对话框,显示已注册用户的各个信息
	 参数说明：无
	 返回值：bool型
	 作者：许鹏，石博雅
*************************************************************/
BOOL Cperinformation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//调用CString用户名
	CString user;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CWuhanMetroView* pView = (CWuhanMetroView*)pFrame->GetActiveView();
	user = pView->GetUsername();
	CMyFile mfile;
	CFile* file = new CFile();
	CString cstrLoadPathName;
	//获取路径
	mfile.GetPath(cstrLoadPathName);
	cstrLoadPathName += (CString("res\\UserInfo\\") + user + CString(".txt"));
	if (file->Open(cstrLoadPathName, CFile::modeReadWrite | CFile::typeBinary))
	{
		CString name = CString("");
		CString age = CString("");
		int sex = 0, s = 0, p = 0, q = 0, r = 0, t = 0;
		//读取用户信息
		mfile.ReadUserFile(file, name, password, age, sex, s, p, q, r, t);
		file->Close();
		delete file;
		start = end = -2;
		// 文件有对应信息
		if (age != CString(""))
		{
			//常用起点对应函数
			start = t;
			OnCbnSelchangeCombo2();
			end = p;
			//常用终点对应函数
			OnCbnSelchangeCombo4();
			//获取用户性别、常用起点、常用终点
			m_start1.SetCurSel(t);
			m_start2.SetCurSel(s);
			m_end1.SetCurSel(p);
			m_end2.SetCurSel(q);
			m_sex.SetCurSel(sex);
			m_age = age;
			m_end = p;
		}
		m_name = name;
		m_password = password;
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		UpdateData(false);
	}
	else {
	MessageBox(L"文件打开失败！", L"Message", MB_OK);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
/************************************************************
	 函数名称：OnBnClickedOk
	 功能描述：消息“保存”按键的响应，保存用户信息
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void Cperinformation::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//调用CString用户名
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CWuhanMetroView* pView = (CWuhanMetroView*)pFrame->GetActiveView();
	CString user = pView->GetUsername();
	CMyFile mfile;
	CFile* file = new CFile();
	CString cstrLoadPathName;
	//获取路径
	mfile.GetPath(cstrLoadPathName);
	cstrLoadPathName += (CString("res\\UserInfo\\") + user + CString(".txt"));
	UpdateData(TRUE);
	// 检查是否点击保存了密码
	CString title = CString("");
	m_changepassword.GetWindowTextW(title);
	if (title == CString("保存密码"))
	{
		MessageBox(L"请保存密码！", L"Warning！！！", MB_OK);
		flag = false;
		return;
	}
	// 查看输入的年龄是否合法
	int flag = 0;
	for (int i = 0; i < m_age.GetLength(); i++)
	{
		char a = m_age[i];
		if (a < '0' || a>'9')
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		MessageBox(L"请重新输入年龄", L"Warning！！！", MB_OK);
		flag = false;
		return;
	}
	if (file->Open(cstrLoadPathName, CFile::modeCreate | CFile::modeWrite))
	{
		USES_CONVERSION;
		//转为CString
		CString a1, a2, a3, a4, a5, temp = CString("#");
		int qidian1 = m_start1.GetCurSel();
		int qidian2 = m_start2.GetCurSel();
		int zhongdian1 = m_end1.GetCurSel();
		int zhongdian2 = m_end2.GetCurSel();
		int sex1 = m_sex.GetCurSel();
		a1.Format(_T("%d"), qidian1);
		a2.Format(_T("%d"), qidian2);
		a3.Format(_T("%d"), zhongdian1);
		a4.Format(_T("%d"), zhongdian2);
		a5.Format(_T("%d"), sex1);
		if (qidian1 == -1 || qidian2 == -1 || zhongdian1 == -1 || zhongdian2 == -1 || sex1 == -1||m_age==CString(""))
		{
			CMyFile File;
			File.WriteUserNameAndPassSWordToFile(file, m_name, password);
			MessageBox(L"请填好所有信息！", L"Warning！！！", MB_OK);
			file->Close();
			delete file;
			UpdateData(false);
			flag = false;
		}
		else
		{
			CMyFile File;
			File.WriteUseFile(file, m_name, password, m_age, a5, a1, a2, a3, a4, temp);
			MessageBox(L"文件保存成功！", L"Message", MB_OK);
			file->Close();
			delete file;
			UpdateData(false);
			flag = true;
		}
	}
	else {
		MessageBox(L"文件保存失败！", L"Message", MB_OK);
		delete file;
		flag = false;
	}
}
/************************************************************
	 函数名称：OnCbnSelchangeCombo2
	 功能描述：常用起点对应函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void Cperinformation::OnCbnSelchangeCombo2()
{
	//读取站点信息
	UpdateData(1);
	CFile* File = new CFile();
	CString a;
	int m = m_start1.GetCurSel();
	if (start != -2&&start !=-1)
	{
		//从文件读入的时候
		a.Format(_T("%d"), start - 1);
		start = -1;
	}
	else
	{
		//手动修改的时候
		a.Format(_T("%d"), m-1);
	}
	CString path = CString("./res/information/") + a + CString(".txt");
	vector<CString>station;
	if (File->Open(path, CFile::modeRead))
	{
		CMyFile myfile;
		myfile.ReadOneLineStationFromFile(File, station);
		File->Close();
		delete File;

		//填入信息
		m_start2.ResetContent();
		for (int i = 0; i < station.size(); i++)
		{
			m_start2.AddString(station[i]);
		}

	}
	else
	{

		MessageBox(L"线路信息不存在！", L"Warning", MB_OK);
		return;
	}

}
/************************************************************
	 函数名称：OnCbnSelchangeCombo4
	 功能描述：常用终点对应函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void Cperinformation::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
	//读取站点信息
	UpdateData(TRUE);
	CFile* File = new CFile();
	CString a;
	int m = m_end1.GetCurSel();
	if (end != -1&&end!=-2)
	{
		a.Format(_T("%d"), end - 1);
		end = -1;
	}
	else
	{
		a.Format(_T("%d"), m-1);
	}
	CString path = CString("./res/information/") + a + CString(".txt");
	vector<CString>station;
	if (File->Open(path, CFile::modeRead))
	{
		CMyFile myfile;
		myfile.ReadOneLineStationFromFile(File, station);
		File->Close();
		delete File;

		//填入信息
		m_end2.ResetContent();
		for (int i = 0; i < station.size(); i++)
		{
			m_end2.AddString(station[i]);
		}
	}
	else
	{
		delete File;
		MessageBox(L"线路信息不存在！", L"Warning", MB_OK);
		return;
	}
}
/************************************************************
	 函数名称：OnBnClickedButton1
	 功能描述：消息“修改密码”响应函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void Cperinformation::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString title = CString("");
	m_changepassword.GetWindowTextW(title);
	if (title == CString("修改密码"))
	{
		Cchangepassword dlg;
		dlg.DoModal();
		if (password != dlg.m_password)
		{
			MessageBox(L"密码错误！！！", L"Warning!", MB_OK);
			return;
		}
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		m_changepassword.SetWindowTextW(CString("保存密码"));
	}
	else
	{
		UpdateData(1);
		password = m_password;
		if (m_password.GetLength() < 4 || m_password.GetLength() > 16)
		{
			MessageBox(L"密码长度不符，请重新输入", L"Message", MB_OK);
			return;
		}
		for (int i = 0; i < m_password.GetLength(); ++i)
		{
			char temp = m_password[i];
			if ((temp < '0' || temp>'9') && (temp < 'A' || temp>'Z') && (temp < 'a' || temp>'z'))
			{
				MessageBox(L"密码不符合规范，请重新输入", L"Message", MB_OK);
				m_password = "";
				return;
			}
		}
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
		m_changepassword.SetWindowTextW(CString("修改密码"));
		UpdateData(0);
	}
}

