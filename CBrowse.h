#pragma once

#include<vector>
#include"Wuhan_MetroView.h"
#include"CLoginDlg.h"
using namespace std;
// CBrowse 对话框
/************************************************************
	 类名称：CBrowse
	 功能描述：浏览失物招领的信息，可以认领。
	 外部函数接口：无
	 作者：许鹏，王宇辰
*************************************************************/
class CBrowse : public CDialogEx
{
	DECLARE_DYNAMIC(CBrowse)

public:
	CBrowse(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBrowse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BROWSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 失物招领1
	CString m_list1;
	// 失物招领2
	//CEdit m_list2;
	// 失物招领3
	CString m_list3;
	// 记录失物招领文件索引
	vector<CString>path;
	vector<CString>line;
	// 显示失物招领内容
	CString Show(CString a);
	// 处理失物招领信息
	void Run(CString temp);
	// 记录每个框的序号
	int m_one, m_two, m_three;
	// 失物招领3
	//CString m_list3;
	CString m_list2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	virtual BOOL OnInitDialog();
};
