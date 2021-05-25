#pragma once


// CLineInformation 对话框

class CLineInformation : public CDialogEx
{
	DECLARE_DYNAMIC(CLineInformation)

public:
	CLineInformation(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLineInformation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LineInformation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//线路选择控件值
	CString m_line;
	//CComboBox m_road;
	CString m_LineInformation;

	//线路选择消息响应函数
	afx_msg void OnLine();

	//站点选择控件值
	CString m_road;

	//标识打开文件线路的变量
	CString A;

	//调节输出字体大小变量对象
	CFont my_Font;

	//调节输出字体大小的函数
	virtual BOOL OnInitDialog();

	//确认按键消息响应函数
	afx_msg void OnBnClickedOk();
};
