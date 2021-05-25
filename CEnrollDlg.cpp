// CEnrollDlg.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "CEnrollDlg.h"
#include "afxdialogex.h"


// CEnrollDlg 对话框

IMPLEMENT_DYNAMIC(CEnrollDlg, CDialogEx)

CEnrollDlg::CEnrollDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENROLL, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
	, m_againpassword(_T(""))
{

}

CEnrollDlg::~CEnrollDlg()
{
}

void CEnrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_againpassword);
}


BEGIN_MESSAGE_MAP(CEnrollDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEnrollDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEnrollDlg 消息处理程序


/************************
* 函数名称：OnBnClickedOk()
* 函数功能：响应“确定”按键的消息
* 传参：无
* 返回值：无
* 作者：王子越
*************************/
void CEnrollDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


/***********************
* 函数名称：IsCorrect()
* 函数功能：判断用户输入的是否符合规范
* 传参：无
* 返回值：bool型
* 作者：王子越
************************/
bool CEnrollDlg::IsCorrect()
{
	if (m_username.GetLength() < 1 || m_username.GetLength() > 9)
	{
		MessageBox(L"用户名长度不符，请重新输入", L"Message", MB_OK);
		m_username = "";
		return false;
	}
	else if (m_password.GetLength() < 4 || m_password.GetLength() > 16)
	{
		MessageBox(L"密码长度不符，请重新输入", L"Message", MB_OK);
		m_password = "";
		return false;
	}
	for (int i = 0; i < m_username.GetLength(); ++i)
	{
		char temp = m_username[i];
		if ((temp < '0' || temp>'9') && (temp < 'A' || temp>'Z') && (temp < 'a' || temp>'z'))
		{
			MessageBox(L"用户名不符合规范，请重新输入", L"Message", MB_OK);
			m_username = "";
			return false;
		}
	}

	//判断用户名是否已存在
	CString FilePath = (CString)"./res/UserInfo/" + m_username + (CString)".txt";
	CFile* file = new CFile();
	if (file->Open(FilePath, CFile::modeRead))
	{
		MessageBox(L"用户名已存在，请重新输入", L"Message", MB_OK);
		file->Close();
		delete file;
		file = nullptr;
		m_username = "";
		return false;
	}
	if(file!=nullptr) delete file;

	//检查密码输入是否符合规范
	if (m_password.GetLength() != m_againpassword.GetLength())
	{
		MessageBox(L"两次密码输入不符，请重新输入", L"Message", MB_OK);
		m_password = "";
		m_againpassword = "";
		return false;
	}
	for (int i = 0; i < m_password.GetLength(); ++i)
	{
		char temp = m_password[i];
		if ((temp < '0' || temp>'9') && (temp < 'A' || temp>'Z') && (temp < 'a' || temp>'z'))
		{
			MessageBox(L"密码不符合规范，请重新输入", L"Message", MB_OK);
			m_password = "";
			m_againpassword = "";
			return false;
		}
	}
	for (int i = 0; i < m_password.GetLength(); ++i)
	{
		if (m_password[i] != m_againpassword[i])
		{
			MessageBox(L"两次密码输入不符，请重新输入", L"Message", MB_OK);
			m_password = "";
			m_againpassword = "";
			return false;
		}
	}
	return true;
}