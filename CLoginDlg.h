#pragma once


// CLoginDlg 对话框

/*********************
* 类名称：CLoginDlg
* 类功能描述：选择登录方式对话框(IDD_LOGIN)的消息响应
* 类接口：构造函数、消息响应函数
* 作者：王子越
**********************/
class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//游客按键的消息响应函数
	afx_msg void OnBnClickedVisitor();

	//登录按键的消息响应函数
	afx_msg void OnBnClickedRegister();

	//注册按键的消息响应函数
	afx_msg void OnBnClickedEnroll();

	//取消按键的消息响应函数
	afx_msg void OnBnClickedCancel();

	//返回Model变量的值
	int GetModel();

	//获取用户密码等信息
	void GetUserInfo(CString& m_username, CString& m_password);

private:
	//定义枚举类型表示不同模式
	int Model;

	CString Username;
	CString Password;
};

