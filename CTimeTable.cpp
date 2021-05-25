// CTimeTable.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "CTimeTable.h"
#include "afxdialogex.h"
#include"CTimeTable.h"


// CTimeTable 对话框

IMPLEMENT_DYNAMIC(CTimeTable, CDialogEx)

/************************************************************
	 函数名称：CTimeTable
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
CTimeTable::CTimeTable(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMETABLE, pParent)
	, m_road(_T(""))
	, m_timetable(_T(""))
{

}


/************************************************************
	 函数名称：CTimeTable
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
CTimeTable::~CTimeTable()
{
}



/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void CTimeTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_road);
	DDX_Text(pDX, IDC_EDIT1, m_timetable);
}


BEGIN_MESSAGE_MAP(CTimeTable, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTimeTable::OnBnClickedOk)
END_MESSAGE_MAP()



// CTimeTable 消息处理程序
/***************************************************
* 函数名称：OnBnClickedOk
* 函数功能：时刻表“确认查询”按键消息响应函数
* 参数：无
* 返回值：void
* 作者：王子越、杜慧琳
****************************************************/
void CTimeTable::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);             //获取控件中更新的值
	m_timetable = "";
	CString FilePath = (CString)"./res/line/";    //文件相对寻址路径
	if (m_road == "阳逻(21)号线")           //如果控件值获得的是阳逻线时打开文件的路径
	{
		FilePath += (CString)"8.txt";

	}

	else if (m_road == "11号线")          //如果控件值获得的是11号线时打开的文件路径
		FilePath += (CString)"7.txt";
	else                               //除阳逻线和11号线的文件路径
	{
		char* temp = (LPSTR)(LPCTSTR)m_road;      //对m_road进行强制转换
		int line = temp[0] - '0';              //对line类型转换

		switch (line)
		{
		case 1:
			FilePath += "0";
			break;
		case 2:
			FilePath += "1";
			break;
		case 3:
			FilePath += "2";
			break;
		case 4:
			FilePath += "3";
			break;
		case 6:
			FilePath += "4";
			break;
		case 7:
			FilePath += "5";
			break;
		case 8:
			FilePath += "6";
			break;
		default:
			break;
		}
		FilePath += (CString)".txt";
	}


	CFile file;            //文件类对象
	file.Open(FilePath, CFile::modeRead);       //以只读方式打开文件
	INT sz = file.GetLength();                  //获取文件长度
	WCHAR* wBuf = new WCHAR[sz + 1];
	char* buffer_src = new char[sz + 1];
	file.Read(buffer_src, sz * sizeof(char));
	buffer_src[sz] = '\0';
	wBuf[sz] = '\0';
	file.Close();

	char* buffer_src_temp = new char[sz * 2]{ ' ' };

	for (int i = 0, j = 0; i < sz; ++i, ++j)
	{
		if (buffer_src[i] == '\n')
		{
			buffer_src_temp[j] = '\r';
			buffer_src_temp[j + 1] = buffer_src[i];
			++j;
		}
		else buffer_src_temp[j] = buffer_src[i];
	}

	MultiByteToWideChar(CP_UTF8, 0, buffer_src_temp, -1, wBuf, sz + 1);

	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer_src_temp, sz + 1, 0, 0);

	m_timetable = buffer_src_temp;

	delete[] buffer_src;
	buffer_src = nullptr;
	delete[] wBuf;
	wBuf = nullptr;

	UpdateData(FALSE);
	//CDialogEx::OnOK();
}
