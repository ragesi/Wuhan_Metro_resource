
// Wuhan_MetroView.h: CWuhanMetroView 类的接口
//

#pragma once
#include "Wuhan_MetroDoc.h"


class CWuhanMetroView : public CView
{
protected: // 仅从序列化创建
	CWuhanMetroView() noexcept;
	DECLARE_DYNCREATE(CWuhanMetroView)

// 特性
public:
	CWuhanMetroDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CWuhanMetroView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CImage cimgImage;
	//缩放功能
    //放大的倍数
	float m_fMultiple;
	//原图坐标原点
	CPoint m_OriginSrcPoint;
	//原图的宽度
	int m_nWidthSrc;
	//原图的高度
	int	m_nHeightSrc;
	//滚轮滚动时工作区坐标点
	CPoint m_ptRollPointClient;
	//滚轮滚动时屏幕坐标点
	CPoint m_ptRollPointScreen;
	//绘图区的矩形区域
	CRect m_rectDraw;
	afx_msg void OnSearchRoad();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void Onperinformation();

private:
	int Model;
	CString Username;
	CString Password;
public:
	afx_msg void OnPublish();
	afx_msg void OnBrowse();
	// 获得模式
	inline int GetModel()
	{
		return Model;
	}
	// 获取密码和用户名
	inline CString GetUsername()
	{
		return Username;
	}
	afx_msg void OnTimeTable();
	afx_msg void On32785();
};

#ifndef _DEBUG  // Wuhan_MetroView.cpp 中的调试版本
inline CWuhanMetroDoc* CWuhanMetroView::GetDocument() const
   { return reinterpret_cast<CWuhanMetroDoc*>(m_pDocument); }
#endif

