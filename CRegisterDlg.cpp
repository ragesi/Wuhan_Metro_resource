// CRegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "CRegisterDlg.h"
#include "afxdialogex.h"


// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


/**************************
* 函数名称：OnBnClickedOk
* 函数功能：响应“确定”按键的消息
* 参数：无
* 返回值：无
* 作者：王子越
***************************/
void CRegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


/************************
* 函数名称：IsMatch
* 函数功能：判断用户输入与注册信息是否一致
* 参数：无
* 返回值：bool型
* 作者：王子越
*************************/
bool CRegisterDlg::IsMatch()
{
	CFile* file = new CFile();
	CString FilePath = (CString)"./res/UserInfo/" + m_username + (CString)".txt";
	
	//若文件存在，即用户名存在
	if (file->Open(FilePath, CFile::modeRead))
	{
		int size = file->GetLength();
		char* buffer = new char[size + 1];
		file->Read(buffer, size * sizeof(char));
		CString username, password;
		int num = 0;//记录当前读取的是用户名还是密码

		for (int i = 0; i < size; ++i)
		{
			//读取用户名
			if (buffer[i] != '#' && num == 0)
				username += (CString)buffer[i];
			//读取密码
			else if (buffer[i] != '#' && num == 1)
				password += (CString)buffer[i];
			//用户名读取完成
			else if (buffer[i] == '#' && num == 0)
				++num;
			//密码读取完成
			else if (buffer[i] == '#' && num == 1)
				break;
		}

		if (username == m_username && password == m_password)
		{
			MessageBox(L"登录成功，欢迎回来", L"Message", MB_OK);
			file->Close();
			delete file;
			return true;
		}
		else
		{
			MessageBox(L"用户名或密码不符，请重新输入", L"Message", MB_OK);
			file->Close();
			delete file;
			return false;
		}
	}

	//若文件不存在，即用户名不存在
	else
	{
		MessageBox(L"用户名不存在，请重新输入", L"Message", MB_OK);
		delete file;
		return false;
	}
}


/**********************
* 函数名称：Clean
* 函数功能：清除控件中的用户名与密码
* 参数：无
* 返回值：无
* 作者：王子越
***********************/
void CRegisterDlg::Clean()
{
	m_username = "";
	m_password = "";
}

