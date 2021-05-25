#pragma once

#include<vector>
#include"CMyFile.h"
using namespace std;
/************************************************************
	 类名称：CLostAndFound
	 功能描述：发布失物招领信息，并保存。
	 外部函数接口：无
	 作者：许鹏，王宇辰，吕希萌
*************************************************************/
// CLostAndFound 对话框
class CLostAndFound : public CDialogEx
{
	DECLARE_DYNAMIC(CLostAndFound)

public:
	CLostAndFound(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLostAndFound();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOST_FOUND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// //失物招领内容
	CString m_content;
	// //线路
	CComboBox m_line;
	// //站点
	//CComboBox m_station;
	// 捡到时间
	CDateTimeCtrl m_date;
	// 站点
	int m_station;
	// 站点
	CComboBox m_spot;
	//站点数组
	vector<CString>PlaceInfor;
	//记录下拉框信息
	vector<CString>s;
	//记录选择的站点名称
	CString name;
	// 文件数量名
	int num;
	//读取文件夹的索引
	vector<CString>path;
	int start;
	CButton lostandfound;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEdit1();
};
