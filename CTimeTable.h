#pragma once


// CTimeTable 对话框

/*********************************************************
* 类名称：CTimeTable
* 类功能描述：时刻表界面对话框(IDD_TIMETABLE)的消息响应
* 类接口：构造函数、消息响应函数
* 作者：王子越、杜慧琳
**********************************************************/
class CTimeTable : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeTable)

public:
	// 标准构造函数
	CTimeTable(CWnd* pParent = nullptr);  
	//标准析构函数
	virtual ~CTimeTable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMEABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//线路控件值
	CString m_road;
	//显示时刻表的控件变量
	CString m_timetable;
	//确认查询控件消息响应函数
	afx_msg void OnBnClickedOk();
};
