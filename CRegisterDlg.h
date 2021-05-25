#pragma once


// CRegisterDlg 对话框

/*********************
* 类名称：CRegisterDlg
* 类功能描述：登录界面对话框(IDD_REGISTER)的消息响应
* 类接口：构造函数、消息响应函数
* 作者：王子越
**********************/
class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//用户名控件变量
	CString m_username;

	//密码控件变量
	CString m_password;

	//“确定”按键的消息响应函数
	afx_msg void OnBnClickedOk();

	//判断用户名与密码是否匹配
	bool IsMatch();

	//清除控件值
	void Clean();
};
