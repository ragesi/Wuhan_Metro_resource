// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "CRegisterDlg.h"
#include "CEnrollDlg.h"
#include "CMyFile.h"
#include"Cperinformation.h"
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
	Model = 1;
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_VISITOR, &CLoginDlg::OnBnClickedVisitor)
	ON_BN_CLICKED(IDC_REGISTER, &CLoginDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDC_ENROLL, &CLoginDlg::OnBnClickedEnroll)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


/************************
* 函数名称：OnBnClickedVisitor
* 函数功能：消息“游客”按键的响应
* 传参：无
* 返回值：无
* 作者：王子越
*************************/
void CLoginDlg::OnBnClickedVisitor()
{
	// TODO: 在此添加控件通知处理程序代码
	//游客模式
	Model = 1;

	CDialogEx::OnOK();
}


/**************************
* 函数名称：OnBnClickedRegister
* 函数功能：消息“登录”按键的响应
* 传参：无
* 返回值：无
* 作者：王子越
***************************/
void CLoginDlg::OnBnClickedRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	//登录模式
	Model = 2;

	CRegisterDlg registerDlg;
	while (registerDlg.DoModal() == IDOK)
	{
		//若用户名与密码输入正确，则关闭登录界面，进入地图界面
		if (registerDlg.IsMatch())
		{
			//获取登录的用户信息
			Username = registerDlg.m_username;
			Password = registerDlg.m_password;

			CDialogEx::OnOK();
			break;
		}
		//用户重新输入
		else registerDlg.Clean();
	}
}


/**************************
* 函数名称：OnBnClickedEnroll
* 函数功能：消息“注册”按键的响应
* 传参：无
* 返回值：无
* 作者：王子越
***************************/
void CLoginDlg::OnBnClickedEnroll()
{
	// TODO: 在此添加控件通知处理程序代码
	CEnrollDlg enrollDlg;
	while (enrollDlg.DoModal() == IDOK)
	{
		if (enrollDlg.IsCorrect())
		{
			//获取文件路径
			CString EnrollPath = (CString)"./res/UserInfo/" + enrollDlg.m_username + (CString)".txt";
			CFile* file = new CFile();
			if (file->Open(EnrollPath, CFile::modeWrite | CFile::modeCreate))
			{
				CMyFile File;
				File.WriteUserNameAndPassSWordToFile(file, enrollDlg.m_username, enrollDlg.m_password);
				file->Close();
				delete file;
			}
			MessageBox(L"用户创建成功", L"Message", MB_OK);
			break;
		}
	}
}


/**************************
* 函数名称：OnBnClickedCancel
* 函数功能：消息“取消”按键的响应
* 传参：无
* 返回值：无
* 作者：王子越
***************************/
void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//退出程序
	exit(0);
	CDialogEx::OnCancel();
}


/**************************
* 函数名称：GetModel
* 函数功能：获取Model
* 传参：无
* 返回值：Model的值,1为游客模式，2为登录模式
* 作者：王子越
***************************/
int CLoginDlg::GetModel()
{
	return Model;
}


/**************************
* 函数名称：GetUserInfo
* 函数功能：获取用户的用户名与密码信息
* 传参：两个CString值，用于保存用户名与密码
* 返回值：无
* 作者：王子越
***************************/
void CLoginDlg::GetUserInfo(CString& m_username, CString& m_password)
{
	m_username = Username;
	m_password = Password;
}