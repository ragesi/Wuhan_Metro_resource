#include "pch.h"
#include "CMyFile.h"
#include"Cperinformation.h"

/************************************************************
	 函数名称：ReadStationFromFile
	 功能描述：读取站点.txt数据到数组station(全部站点)
	 参数说明：才
	 返回值：无
	 作者：许鹏
*************************************************************/
void CMyFile::ReadAllStationFromFile(CFile* file, vector<CString> &station)
{
	// 从文件读取中文
	INT size = file->GetLength();
	WCHAR* wBuf = new WCHAR[size + 1];
	char* buffer = new char[size + 1];
	file->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	wBuf[size] = '\0';
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wBuf, size + 1);
	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer, size + 1, 0, 0);
	// 读取信息到地点数组，1号站点对应数组的0号位置
	for (int i = 0; i <= size; )
	{
		// 保存站点名字
		CString name;
		CString num;
		// 中间容器，用来中文转化
		vector<char>a;
		// 第一次读取，将中文读取到容器中，并且获取中文大小
		while (buffer[i] != ';')
		{
			a.push_back(buffer[i]);
			i++;
		}
		char* temp = new char[a.size() + 1];
		// 将容器中的字符取出放到char*中
		for (int i = 0; i < a.size(); i++)
			temp[i] = a[i];
		temp[a.size()] = '\0';
		// char*转换为CString
		name = CA2CT(temp);
		delete temp;
		station.push_back(name);
		i++;
		// 跳过数字部分
		while (buffer[i] != '#')
		{
			i++;
		}
		// 跳过“#\r\n"
		i += 3;
		// 判断能否结束，必须有结束符
		if (buffer[i] == '!')
			break;
	}
	delete[] buffer;
	buffer = nullptr;
	delete[] wBuf;
	wBuf = nullptr;
}
/************************************************************
	 函数名称：ReadOneLineStationFromFile
	 功能描述：读取某一条线站点数据到数组station(一条线站点)
	 参数说明：文件指针，被修改的站点储存数组
	 返回值：无
	 作者：许鹏
*************************************************************/
void CMyFile::ReadOneLineStationFromFile(CFile* file, vector<CString>& station)
{
	// 从文件读取中文
	INT size = file->GetLength();
	WCHAR* wBuf = new WCHAR[size + 1];
	char* buffer = new char[size + 1];
	file->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	wBuf[size] = '\0';
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wBuf, size + 1);
	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer, size + 1, 0, 0);
	// 读取信息到地点数组，1号站点对应数组的0号位置
	for (int i = 0; i <= size; )
	{
		// 保存站点名字
		CString name;
		CString num;
		// 中间容器，用来中文转化
		vector<char>a;
		// 第一次读取，将中文读取到容器中，并且获取中文大小
		while (buffer[i] != '#')
		{
			a.push_back(buffer[i]);
			i++;
		}
		char* temp = new char[a.size() + 1];
		// 将容器中的字符取出放到char*中
		for (int i = 0; i < a.size(); i++)
			temp[i] = a[i];
		temp[a.size()] = '\0';
		// char*转换为CString
		name = CA2CT(temp);
		delete temp;
		station.push_back(name);
		// 跳过“#\r\n"
		i += 3;
		// 判断能否结束，必须有结束符
		if (buffer[i] == '!')
			break;
	}
	delete[] buffer;
	buffer = nullptr;
	delete[] wBuf;
	wBuf = nullptr;
}
/************************************************************
	 函数名称：ReadIndexFromFile
	 功能描述：读取索引目录到文件
	 参数说明：文件指针，读取的索引目录数组
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CMyFile::ReadIndexFromFile(CFile* file, vector<CString>& path)
{
		int temp = 0, size = file->GetLength();
		file->SeekToBegin();
		char* t = new char[size];
		file->Read(t, size);
		//读入索引文件目录，以“#”结束
		for (int i = 0;i < size;)
		{
			while (t[i] != '#')
			{
				temp = temp * 10 + t[i] - '0';
				i++;
			}
			//构造文件名称“0.txt”
			CString temp1, temp2 = CString(".txt");
			temp1.Format(_T("%d"), temp);
			path.push_back(temp1);
			temp = 0;
			i += 1;
		}
}
/************************************************************
	 函数名称：WriteFileToIndex
	 功能描述：写入索引文件
	 参数说明：文件指针，写入的索引目录数组
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CMyFile::WriteFileToIndex(CFile* file, vector<CString>& path)
{
	USES_CONVERSION;
	CString t = CString("#");
	for (int i = 0;i < path.size();i++)
	{
		char* p = T2A(path[i]);
		file->Write(p, strlen(p));
		file->Write(t, t.GetLength());
	}
}
/************************************************************
	 函数名称：WriteInformation
	 功能描述：写入失物招领信息
	 参数说明：文件指针，失物招领信息的四个CString值
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CMyFile::WriteInformation(CFile* file, CString szDate, CString Line, CString Station, CString m_content)
{
	USES_CONVERSION;
	CString temp = CString("#");
	char* szDate1 = T2A(szDate);
	char* Line1 = T2A(Line);
	char* Station1 = T2A(Station);
	char* m_content1 = T2A(m_content);
	int len = szDate.GetLength();
	file->Write(szDate1, strlen(szDate1));
	file->Write(temp, temp.GetLength());
	file->Write(Line1, strlen(Line1));
	file->Write(temp, temp.GetLength());
	file->Write(Station1, strlen(Station1));
	file->Write(temp, temp.GetLength());
	file->Write(m_content1, strlen(m_content1));
	file->Write(temp, temp.GetLength());
}
/************************************************************
	 函数名称：GetPath
	 功能描述：获取当前路径
	 参数说明：文件名称
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CMyFile::GetPath(CString cstrLoadPathName)
{
	//写入文件
	HMODULE module = GetModuleHandle(0);
	char* pFileName = new char[MAX_PATH];
	GetModuleFileName(module, LPWSTR(pFileName), MAX_PATH);
	cstrLoadPathName.Format(_T("%s"), pFileName);
	int nPos = cstrLoadPathName.ReverseFind(_T('\\'));
	cstrLoadPathName = cstrLoadPathName.Left(nPos);
	delete[]pFileName;
	cstrLoadPathName = cstrLoadPathName.Mid(0, cstrLoadPathName.GetLength() - 9);
}
/************************************************************
	 函数名称：GetPath
	 功能描述：读取失物招领信息
	 参数说明：文件指针，失物招领信息的四个CString值
	 返回值：无
	 作者：许鹏，王宇辰
*************************************************************/
void CMyFile::ReadFile(CFile* File, CString& content, CString& time, int& Line, int& station)
{
	INT size = File->GetLength();
	char* buffer = new char[size + 1];
	File->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	//读取信息到地点数组，1号站点对应数组的0号位置
	int i = 0;
	//中间容器，用来中文转化
	vector<char>a;
	//获取时间
	while (buffer[i] != '#')
	{
		time += buffer[i];
		i++;
	}
	i += 1;
	//获取站点和线路
	while (buffer[i] != '#')
	{
		Line = Line * 10 + buffer[i] - '0';
		i++;
	}
	i += 1;
	while (buffer[i] != '#')
	{
		station = station * 10 + buffer[i] - '0';
		i++;
	}
	i += 1;
	//获取具体信息
	while (buffer[i] != '#')
	{
		a.push_back(buffer[i]);
		i++;
	}
	char* temp = new char[a.size() + 1];
	//将容器中的字符取出放到char*中
	for (int i = 0; i < a.size(); i++)
		temp[i] = a[i];
	//处理中文
	temp[a.size()] = '\0';
	// char * 转换为CString
	content = CA2CT(temp);

	delete[] temp;
	delete[] buffer;
	buffer = nullptr;
}
/************************************************************
	 函数名称：ReadUserFile
	 功能描述：读取用户个人信息
	 参数说明：文件指针，读入的用户名、密码、年龄、性别 、常用起点、常用终点
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void CMyFile::ReadUserFile(CFile* file, CString& name, CString& password, CString& age, int& sex, int& s, int& p, int& q, int& r, int& t) 
{
	int size = file->GetLength();
	char* buff = new char[size];
	file->Read(buff, size * sizeof(char));
	int i = 0;
	//读取用户名
	while (buff[i] != '#')
	{
		name += buff[i];
		i++;
	}
	i += 1;
	//读取密码
	while (buff[i] != '#')
	{
		password += buff[i];
		i++;
	}
	i++;
	//有其他信息：性别，年龄...
	if (i != size)
	{
		//i += 2;
		//读取年龄
		while (buff[i] != '#')
		{
			age += buff[i];
			i++;
		}
		i += 1;
		//读取性别
		while (buff[i] != '#')
		{
			sex = buff[i] - 48;
			i++;
		}
		i += 1;
		//读取线路起点
		while (buff[i] != '#')
		{
			t = buff[i] - 48;
			i++;
		}
		i += 1;
		//读取起始站点
		while (buff[i] != '#')
		{
			s = s * 10 + buff[i] - 48;
			i++;
		}
		i += 1;
		//读取线路终点
		while (buff[i] != '#')
		{
			p = buff[i] - 48;
			i++;
		}
		i += 1;
		//读取起始终点
		while (buff[i] != '#')
		{
			q = q * 10 + buff[i] - 48;
			i++;
		}
	}
}
/************************************************************
	 函数名称：WriteUseFile
	 功能描述：写入用户个人信息
	 参数说明：文件指针，写入的用户名、密码、年龄、性别、常用起点、常用终点
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void CMyFile::WriteUseFile(CFile* file, CString& m_name, CString& password, CString& m_age, CString& a5, CString& a1, CString& a2, CString& a3, CString& a4,CString& temp)
{
	USES_CONVERSION;
	//转为CString
	//转换格式写入文档
	char* name = T2A(m_name);
	char* password1 = T2A(password);
	char* age = T2A(m_age);
	char* sex = T2A(a5);
	char* b1 = T2A(a1);
	char* b2 = T2A(a2);
	char* b3 = T2A(a3);
	char* b4 = T2A(a4);
	file->Write(name, strlen(name));
	file->Write(temp, temp.GetLength());
	file->Write(password1, strlen(password1));
	file->Write(temp, temp.GetLength());
	file->Write(age, strlen(age));
	file->Write(temp, temp.GetLength());
	file->Write(sex, strlen(sex));
	file->Write(temp, temp.GetLength());
	file->Write(b1, strlen(b1));
	file->Write(temp, temp.GetLength());
	file->Write(b2, strlen(b2));
	file->Write(temp, temp.GetLength());
	file->Write(b3, strlen(b3));
	file->Write(temp, temp.GetLength());
	file->Write(b4, strlen(b4));
	file->Write(temp, temp.GetLength());
}
/************************************************************
	 函数名称：WriteUserNameAndPassSWordToFile
	 功能描述：写入用户的用户名和密码
	 参数说明：文件指针，写入的用户名、密码
	 返回值：无
	 作者：许鹏，石博雅
*************************************************************/
void CMyFile::WriteUserNameAndPassSWordToFile(CFile* file, CString name, CString password)
{
	USES_CONVERSION;
	//转为CString
	//转换格式写入文档
	CString temp = CString("#");
	char* name1 = T2A(name);
	char* password1 = T2A(password);
	file->Write(name1, strlen(name1));
	file->Write(temp, temp.GetLength());
	file->Write(password1, strlen(password1));
	file->Write(temp, temp.GetLength());
}
