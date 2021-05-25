// Cchangepassword.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "Cchangepassword.h"
#include "afxdialogex.h"


// Cchangepassword 对话框

IMPLEMENT_DYNAMIC(Cchangepassword, CDialogEx)
/************************************************************
	 函数名称：Cchangepassword
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
Cchangepassword::Cchangepassword(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHA_PASSWORD, pParent)
	, m_password(_T(""))
{

}
/************************************************************
	 函数名称：~Cchangepassword
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
Cchangepassword::~Cchangepassword()
{
}
/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void Cchangepassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_password);
}


BEGIN_MESSAGE_MAP(Cchangepassword, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cchangepassword::OnBnClickedOk)
END_MESSAGE_MAP()


// Cchangepassword 消息处理程序

/************************************************************
	 函数名称：OnBnClickedOk
	 功能描述：更新密码
	 参数说明：无
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void Cchangepassword::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	CDialogEx::OnOK();
}
