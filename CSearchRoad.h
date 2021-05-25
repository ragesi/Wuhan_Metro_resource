#pragma once
#include"CMyFile.h"
using namespace std;

// CSearchRoad 对话框

/************************************************************
	 类名称：CSearchRoad
	 功能描述：查询窗口对应的类，执行查询操作并且显示对应信息
	 外部函数接口：无
	 作者：许鹏，王子越
*************************************************************/
class CSearchRoad : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchRoad)

public:
	CSearchRoad(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSearchRoad();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_ROAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//计算换乘数
	int Transform(vector<int>);
	//计算价钱
	int Cost(int);
	//获取站点所在线路
	int GetLineNum(int);
	DECLARE_MESSAGE_MAP()
public:
	// 距离
	CString m_distance;
	// 价钱
	CString m_cost;
	CString m_path;
	// 出发线路
	CComboBox m_s_l;
	// 出发站点
	CComboBox m_s_s;
	// 终点线路
	CComboBox m_e_l;
	// 终点站点
	CComboBox m_e_s;
	// 线路起点选择
	int start;
	// 线路终点选择
	int end;
	// 起始站点名
	CString s_station;
	vector<CString> s;
	// 终点站点名
	CString e_station;
	vector<CString> e;
	// 距离
	int distance;
	// 站点数
	int num;
	// 换乘数
	CString m_num;
	int m_s_line;
	int m_e_line;
	afx_msg void OnBnClickedSearchRoad();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo3();
};
