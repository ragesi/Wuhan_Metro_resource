#pragma once


// Cperinformation 对话框
/************************************************************
	 类名称：Cperinformation
	 功能描述：进行用户个人信息的查询与修改
	 外部函数接口：无
	 作者：许鹏，石博雅
*************************************************************/
class Cperinformation : public CDialogEx
{
	DECLARE_DYNAMIC(Cperinformation)

public:
	Cperinformation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cperinformation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PER_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//用户姓名
	CString m_name;
	//用户密码
	CString m_password;
	//用户年龄
	CString m_age;
	//用户性别
	CComboBox m_sex;
	//常用起点线路
	CComboBox m_start1;
	//常用起点站点
	CComboBox m_start2;
	//常用终点线路
	CComboBox m_end1;
	//常用终点站点
	CComboBox m_end2;
	//修改密码控件
	CButton m_changepassword;
	//起始线路选择
	int start;
	//终点线路选择
	int end;
	// 终点站线路
	int m_end;
	// 起点路线
	int m_start;
	// 记录是否正确的输入了个人信息
	bool flag;
	//初始化
	virtual BOOL OnInitDialog();
	//保存个人信息
	afx_msg void OnBnClickedOk();
	//修改密码函数
	afx_msg void OnBnClickedButton1();
	CString password;
	//常用起点对应函数
	afx_msg void OnCbnSelchangeCombo2();
	//常用终点对应函数
	afx_msg void OnCbnSelchangeCombo4();
};
