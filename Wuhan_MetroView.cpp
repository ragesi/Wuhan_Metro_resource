
// Wuhan_MetroView.cpp: CWuhanMetroView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Wuhan_Metro.h"
#endif

#include"CBrowse.h"
#include"CLostAndFound.h"
#include "Wuhan_MetroView.h"
#include"CSearchRoad.h"
#include "CLoginDlg.h"
#include"Cperinformation.h"
#include"CTimeTable.h"
#include"CLineInformation.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWuhanMetroView

IMPLEMENT_DYNCREATE(CWuhanMetroView, CView)

BEGIN_MESSAGE_MAP(CWuhanMetroView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32804, &CWuhanMetroView::OnSearchRoad)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_32773, &CWuhanMetroView::OnPublish)
	ON_COMMAND(ID_32786, &CWuhanMetroView::OnBrowse)
	ON_COMMAND(ID_32783, &CWuhanMetroView::Onperinformation)
	ON_COMMAND(ID_32808, &CWuhanMetroView::OnTimeTable)
	ON_COMMAND(ID_32785, &CWuhanMetroView::On32785)
END_MESSAGE_MAP()

// CWuhanMetroView 构造/析构
/************************************************************
	 函数名称：CWuhanMetroView
	 功能描述：主视图的默认构造函数
	 参数说明：无
	 返回值：无
	 修改说明：增加了对应地图的相关信息,增加了登录界面的信息
	 作者：微软
*************************************************************/
CWuhanMetroView::CWuhanMetroView() noexcept
{
	// TODO: 在此处添加构造代码

	CLoginDlg loginDlg;
	loginDlg.DoModal();
	Model = loginDlg.GetModel();
	loginDlg.GetUserInfo(Username, Password);
	//放大倍数初始化
	m_fMultiple = 0.0;
	//原图坐标原点
	m_OriginSrcPoint = (0, 0);
	//原图的宽度
	m_nWidthSrc = 0;
	//原图的高度
	m_nWidthSrc = 0;
	//滚轮滚动时工作区坐标点
	m_ptRollPointClient = (0, 0);
	//滚轮滚动时屏幕坐标点
	m_ptRollPointScreen = (0, 0);
}

CWuhanMetroView::~CWuhanMetroView()
{
}

BOOL CWuhanMetroView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CWuhanMetroView 绘图
/************************************************************
	 函数名称：OnDraw
	 功能描述：主视图的绘图函数
	 参数说明：无
	 返回值：无
	 修改说明：增加了对应地图的绘制操作
	 作者：微软
*************************************************************/
void CWuhanMetroView::OnDraw(CDC* pDC)
{
	CWuhanMetroDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//地图地址
	CString cstrLoadPathName;
	//参数为0，则GetModuleHandle返回用于c的文件的句柄
	HMODULE module = GetModuleHandle(0);
	char* pFileName = new char[MAX_PATH];
	GetModuleFileName(module, LPWSTR(pFileName), MAX_PATH);
	cstrLoadPathName.Format(_T("%s"), pFileName);
	//返回此CString对象中与要求的字符匹配的最后一个字符的索引
	int nPos = cstrLoadPathName.ReverseFind(_T('\\'));
	if (nPos < 0)
	{
		MessageBox(L"无法加载地图！", L"message", MB_OK);
		return;
	}
	else
	{
		//得到.EXE的文件地址
		cstrLoadPathName = cstrLoadPathName.Left(nPos);
	}
	delete[]pFileName;
	cstrLoadPathName = cstrLoadPathName.Mid(0, cstrLoadPathName.GetLength() - 9) + CString("res\\高清版武汉轨道交通线路图5.jpg");
	//构造加载文件的文件对话框
	if (cimgImage.IsNull()) 
	{
		//加载图片
		cimgImage.Load(cstrLoadPathName);
		//放大倍数清零
		m_fMultiple = 0;
		//原图的宽度
		m_nWidthSrc = cimgImage.GetWidth();
		//原图的高度
		m_nHeightSrc = cimgImage.GetHeight();
		//源的原点清零
		m_OriginSrcPoint = (0, 0);
		//使当前的窗口无效:让Windows知道这个窗口现在该重新绘制一下了
		Invalidate();
	}
	//如果CImage对象不为空
	if (!cimgImage.IsNull())
	{
		//矩形对象rectControl：客户区的矩形区域
		CRect rectClient;
		//获取工作区Client的矩形区域
		GetClientRect(rectClient);

		//每次显示前先将原来的界面刷新称白色
		//刷成白色（255,255,255）
		CBrush br(0xffffff);
		pDC->FillRect(rectClient, &br);

		//获取图片的宽、高
		double dWidthOrigin = cimgImage.GetWidth();
		double dHeightOrigin = cimgImage.GetHeight();
		//定义拉伸后图片的宽、高
		double dWidthStrectch;
		double dHeightStrectch;

		//显示方法二：使原图最大地显示在客户区当中
		if (dWidthOrigin > dHeightOrigin)
		{
			//原图的宽比高大：处理后的宽度，让它和显示框等宽
			dWidthStrectch = rectClient.Width();
			//处理后的高度
			dHeightStrectch = dWidthStrectch / dWidthOrigin * dHeightOrigin;
		}
		else
		{
			//原图的高比宽大：处理后的高度，让它和显示框等高
			dHeightStrectch = rectClient.Height();
			dWidthStrectch = dHeightStrectch / dHeightOrigin * dWidthOrigin;
		}

		//绘图区域在客户区Client的位置
		m_rectDraw = CRect(CPoint((rectClient.Width() - dWidthStrectch) / 2, (rectClient.Height() - dHeightStrectch) / 2), CSize(dWidthStrectch, dHeightStrectch));

		//绘制图片到控件表示的区域：CImage::StretchBlt
		//句柄+尺寸参数
		//SRCCOPY：将源矩形区直接拷贝到目标矩形区域pDC
		//handle to destination DC：pDC->m_hDC
		/*方法1*/
		//cimgImage.StretchBlt(pDC->m_hDC, rectDraw, SRCCOPY);
		/*方法2*/
		//目标区域Dst
		int xDest = m_rectDraw.TopLeft().x;
		int yDest = m_rectDraw.TopLeft().y;
		int nDestWidth = m_rectDraw.Width();
		int nDestHeight = m_rectDraw.Height();
		//源图片Src
		int xSrc = m_OriginSrcPoint.x;
		int ySrc = m_OriginSrcPoint.y;
		int nSrcWidth = m_nWidthSrc;
		int nSrcHeight = m_nHeightSrc;
		//光栅操作
		DWORD dwROP = SRCCOPY;
		//缩放操作
		cimgImage.StretchBlt(pDC->m_hDC, xDest, yDest, nDestWidth, dHeightStrectch, xSrc, ySrc, nSrcWidth, nSrcHeight, dwROP);
		//image.Draw(pDC->GetSafeHdc(), 0, 0);
	// TODO: 在此处为本机数据添加绘制代码
	}
}


void CWuhanMetroView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWuhanMetroView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWuhanMetroView 诊断

#ifdef _DEBUG
void CWuhanMetroView::AssertValid() const
{
	CView::AssertValid();
}

void CWuhanMetroView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWuhanMetroDoc* CWuhanMetroView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWuhanMetroDoc)));
	return (CWuhanMetroDoc*)m_pDocument;
}
#endif //_DEBUG


// CWuhanMetroView 消息处理程序

/************************************************************
	 函数名称：OnSearchRoad
	 功能描述：打开消息查询对话框
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
void CWuhanMetroView::OnSearchRoad()
{
	// TODO: 在此添加命令处理程序代码
	CSearchRoad dlg;
	dlg.DoModal();
}

/************************************************************
	 函数名称：OnMouseWheel
	 功能描述：响应鼠标滚轮滑动操作，对当前位图进行放大缩小操作
	 参数说明：无
	 返回值：无
	 作者：许鹏，王子越
*************************************************************/
BOOL CWuhanMetroView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//pt是Screen显示器坐标系的坐标
	//将OnMouseWheel的左边传到当前位置坐标变量当中
	m_ptRollPointScreen = pt;
	//将pt从屏幕坐标系转换工作区坐标系
	//ScreenToClient传入的是坐标点的指针
	m_ptRollPointClient = pt;
	ScreenToClient(&m_ptRollPointClient);


	//如果存在加载的图像，改变原点和宽、高
	if (!cimgImage.IsNull())
	{
		//设立一个tmp暂存正常变量
		//保存上一次的结果
		CPoint ptTmp = m_OriginSrcPoint;
		int nTmpWidth = m_nWidthSrc;
		int nTmpHeight = m_nHeightSrc;

		//放大操作
		if (zDelta > 0)
		{
			//判断滚轮坐标是否在绘图区当中：在左侧的右边，在右侧的左边
			if (m_ptRollPointClient.x < m_rectDraw.TopLeft().x || m_ptRollPointClient.x > m_rectDraw.BottomRight().x)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//防止缩放过度
			//如果宽、高<50，则缩放过度
			else if (m_nWidthSrc < 50 || m_nHeightSrc < 50)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//设置放大倍数
			m_fMultiple = 0.1;
			//改变原图的宽、高：
			//实现放大的过程其实是获取原图某个【区域】的过程
			//这个【区域】对比【源图区域】是小的
			m_nWidthSrc = m_nWidthSrc * (1 - m_fMultiple);
			m_nHeightSrc = m_nHeightSrc * (1 - m_fMultiple);

			/*（计算缩放前在Rect的宽和高的比例）、然后用比例乘以Delta（缩放前后宽、高的差值）*/
			float nDeltaX = m_ptRollPointClient.x - float(m_rectDraw.TopLeft().x);
			float fPosXRatio = nDeltaX / float(m_rectDraw.Width());
			float nDeltaY = m_ptRollPointClient.y - float(m_rectDraw.TopLeft().y);
			float fPosYRatio = nDeltaY / float(m_rectDraw.Height());

			//改变显示区域的原点位置
			//改变原点的位置，往右、下移动
			//1、以鼠标为中心的缩放（放大）
			m_OriginSrcPoint.x += (nTmpWidth - m_nWidthSrc) * fPosXRatio;
			m_OriginSrcPoint.y += (nTmpHeight - m_nHeightSrc) * fPosYRatio;

		}
		//缩小操作
		if (zDelta < 0)
		{
			//判断滚轮坐标是否在绘图区当中
			if (m_ptRollPointClient.x < m_rectDraw.TopLeft().x || m_ptRollPointClient.x > m_rectDraw.BottomRight().x)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//如果宽、高到为3000，则缩小过度
			else if (m_nWidthSrc > 3000 || m_nHeightSrc > 3000)
			{
				return CView::OnMouseWheel(nFlags, zDelta, pt);
			}
			//设置缩小倍数
			m_fMultiple = -0.1;

			//改变原图的宽、高：
			//实现放大的过程其实是获取原图某个【区域】的过程
			//这个【区域】对比【源图区域】是小的
			m_nWidthSrc = m_nWidthSrc * (1 - m_fMultiple);
			m_nHeightSrc = m_nHeightSrc * (1 - m_fMultiple);

			//改变显示区域的原点位置
			//改变原点的位置，往右、下移动
			//2、以工作区的中心进行缩放（缩小）fPosXRatio = fPosYRatio = 0.5
			m_OriginSrcPoint.x += (nTmpWidth - m_nWidthSrc) * 0.5;
			m_OriginSrcPoint.y += (nTmpHeight - m_nHeightSrc) * 0.5;
		}

		//使当前的窗口无效:让Windows知道这个窗口现在该重新绘制一下了
		Invalidate();

	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CWuhanMetroView::OnPublish()
{
	// TODO: 在此添加命令处理程序代码
	if (Model == 2)
	{
		CLostAndFound dlg;
		dlg.DoModal();
	}
	else if (Model == 1)
	{
		MessageBox(L"您还未登录，请登录后再发布！", L"Tips", MB_OK);
	}
}


/************************************************************
	 函数名称：OnBrowse
	 功能描述：主视图的失物招领中“浏览”的消息响应函数
	 参数说明：无
	 返回值：无
	 作者：许鹏、王宇辰
*************************************************************/
void CWuhanMetroView::OnBrowse()
{
	// TODO: 在此添加命令处理程序代码
	CBrowse dlg;
	dlg.DoModal();
}

/************************************************************
	 函数名称：Onperinformation
	 功能描述：主视图的失物招领中“发布”的消息响应函数
	 参数说明：无
	 返回值：无
	 作者：许鹏、王宇辰
*************************************************************/
void CWuhanMetroView::Onperinformation()
{
	// TODO: 在此添加命令处理程序代码
	if (Model == 2)
	{
		Cperinformation dlg;
		dlg.DoModal();
	}
	else if (Model == 1)
	{
		MessageBox(L"您还未登录，请登录后查看！", L"Tips", MB_OK);
	}
}




/************************************************************
	 函数名称：OnTimeTable
	 功能描述：主视图中时刻表的消息响应函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
void CWuhanMetroView::OnTimeTable()
{
	// TODO: 在此添加命令处理程序代码
	CTimeTable timetableDlg;
	if (timetableDlg.DoModal() == IDOK)
	{

	}

}


/************************************************************
	 函数名称：On32785
	 功能描述：主视图中线路信息的消息响应函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
void CWuhanMetroView::On32785()
{
	// TODO: 在此添加命令处理程序代码
	CLineInformation lineinformationDlg;
	lineinformationDlg.DoModal();
}
