#pragma once


// Cchangepassword 对话框
/************************************************************
	 类名称：Cchangepassword
	 功能描述：用户修改密码
	 外部函数接口：无
	 作者：许鹏，石博雅
*************************************************************/
class Cchangepassword : public CDialogEx
{
	DECLARE_DYNAMIC(Cchangepassword)

public:
	Cchangepassword(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cchangepassword();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHA_PASSWORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_password;
	//用户确定密码正确响应函数
	afx_msg void OnBnClickedOk();
};
