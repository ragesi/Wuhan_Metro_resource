// CLineInformation.cpp: 实现文件
//

#include "pch.h"
#include "Wuhan_Metro.h"
#include "CLineInformation.h"
#include "afxdialogex.h"
#include"CLineInformation.h"
#include"CLineInformation.h"
#include"vector"
using namespace std;

// CLineInformation 对话框

IMPLEMENT_DYNAMIC(CLineInformation, CDialogEx)
/************************************************************
	 函数名称：CLineInformation
	 功能描述：对话框的默认构造函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
CLineInformation::CLineInformation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LineInformation, pParent)
	, m_line(_T(""))
	, m_LineInformation(_T(""))
	, m_road(_T(""))
{

}

/************************************************************
	 函数名称：CLineInformation
	 功能描述：对话框的默认析构函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
CLineInformation::~CLineInformation()
{
}


/************************************************************
	 函数名称：DoDataExchange
	 功能描述：响应控件变化消息
	 参数说明：无
	 返回值：无
	 作者：微软
*************************************************************/
void CLineInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_line);
	//DDX_Control(pDX, IDC_COMBO2, m_road);
	DDX_Text(pDX, IDC_EDIT1, m_LineInformation);
	DDX_CBString(pDX, IDC_COMBO2, m_road);
}


BEGIN_MESSAGE_MAP(CLineInformation, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CLineInformation::OnLine)
	ON_BN_CLICKED(IDOK, &CLineInformation::OnBnClickedOk)
END_MESSAGE_MAP()


// CLineInformation 消息处理程序

/************************************************************
	 函数名称：OnLine
	 功能描述：选择线路的消息响应函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
void CLineInformation::OnLine()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CFile* file = new CFile();
	CString FilePath = (CString)"./res/information1/";

	if (m_line == "阳逻线(21号线)")
	{
		FilePath += (CString)"8.txt";
		A = "8";
	}
	else if (m_line == "11号线")
	{
		FilePath += (CString)"7.txt";
		A = "7";
	}
	else
	{
		char* temp = (LPSTR)(LPCTSTR)m_line;
		int line = temp[0] - '0';

		switch (line)
		{
		case 1:
			FilePath += "0";
			A = "0";
			break;
		case 2:
			FilePath += "1";
			A = "1";
			break;
		case 3:
			FilePath += "2";
			A = "2";
			break;
		case 4:
			FilePath += "3";
			A = "3";
			break;
		case 6:
			FilePath += "4";
			A = "4";
			break;
		case 7:
			FilePath += "5";
			A = "5";
			break;
		case 8:
			FilePath += "6";
			A = "6";
			break;
		default:
			break;
		}
		FilePath += (CString)".txt";
	}

	file->Open(FilePath, CFile::modeRead);

	INT size = file->GetLength();
	WCHAR* wBuf = new WCHAR[size + 1];
	char* buffer = new char[size + 1];
	file->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	wBuf[size] = '\0';
	file->Close();
	delete file;
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wBuf, size + 1);
	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer, size + 1, 0, 0);

	CComboBox* combownd1 = NULL;
	combownd1 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	combownd1->ResetContent();
	vector<char> temp1;
	for (int i = 0; i < size; ++i)
	{
		if (buffer[i] == '#')
		{
			char* temp2 = new char[temp1.size() + 1];
			for (int j = 0; j < temp1.size(); ++j)
				temp2[j] = temp1[j];
			temp2[temp1.size()] = '\0';


			combownd1->AddString(CA2CT(temp2));
			temp1.clear();
		}
		else if (buffer[i] == '!')
		{
			break;
		}
		else temp1.push_back(buffer[i]);
	}

	UpdateData(FALSE);

}


/************************************************************
	 函数名称：OnBnClickedOk
	 功能描述：线路信息中的确定按键的消息响应函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
void CLineInformation::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	m_LineInformation = "";


	CString FilePath = CString("./res/line/") + A + (CString)".txt";
	CFile* file = new CFile();
	file->Open(FilePath, CFile::modeRead);
	INT size = file->GetLength();
	WCHAR* wBuf = new WCHAR[size + 1];
	char* buffer = new char[size + 1];
	file->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	wBuf[size] = '\0';
	file->Close();
	delete file;
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wBuf, size + 1);
	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer, size + 1, 0, 0);

	bool IsStart = false;
	//用于类型转换
	vector<char> temp1;
	CString name;
	int Num = 0;
	for (int i = 0; i < size; ++i)
	{
		if (buffer[i] == '|' && IsStart == true)
		{

			IsStart = false;
			char* temp2 = new char[temp1.size() + 1];

			for (int i = 0; i < temp1.size(); ++i)
				temp2[i] = temp1[i];
			temp2[temp1.size()] = '\0';

			name = CA2CT(temp2);

			if (name == m_road || ((CString)"\n" + name == m_road))
			{
				if (Num % 2 == 1) m_LineInformation += (CString)"往上行方向\r\n";
				else m_LineInformation += (CString)"往下行方向\r\n";
				for (int j = i + 1; j < size; ++j)
				{
					if (buffer[j] != '|') m_LineInformation += buffer[j];
					else
					{
						i = j - 1;
						break;
					}
				}
				m_LineInformation += (CString)"\r\n";
			}
		}

		if (IsStart)
			temp1.push_back(buffer[i]);

		if (buffer[i] == '|' && IsStart == false)
		{
			IsStart = true;
			++Num;
			temp1.clear();
		}
	}

	UpdateData(FALSE);

	//CDialogEx::OnOK();
}


/************************************************************
	 函数名称：OnInitDialog
	 功能描述：调整输出字体大小的函数
	 参数说明：无
	 返回值：无
	 作者：王子越、杜慧琳
*************************************************************/
BOOL CLineInformation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	my_Font.CreatePointFont(160, L"Arial");
	GetDlgItem(IDC_EDIT1)->SetFont(&my_Font);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}