#pragma once


// CEnrollDlg 对话框

/*************************
* 类名称：CEnrollDlg
* 类功能描述：注册界面对话框（IDD_ENROLL）的消息响应
* 外部函数接口：构造函数、消息响应函数
* 作者：王子越
**************************/
class CEnrollDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnrollDlg)

public:
	CEnrollDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEnrollDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENROLL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//用户名变量
	CString m_username;

	//密码变量
	CString m_password;

	//再次输入密码的变量
	CString m_againpassword;

	afx_msg void OnBnClickedOk();

	//判断输入信息是否正确
	bool IsCorrect();
};
