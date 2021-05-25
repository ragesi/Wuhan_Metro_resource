#include "pch.h"
#include "CMyFile.h"
#include"Cperinformation.h"

/************************************************************
	 �������ƣ�ReadStationFromFile
	 ������������ȡվ��.txt���ݵ�����station(ȫ��վ��)
	 ����˵������
	 ����ֵ����
	 ���ߣ�����
*************************************************************/
void CMyFile::ReadAllStationFromFile(CFile* file, vector<CString> &station)
{
	// ���ļ���ȡ����
	INT size = file->GetLength();
	WCHAR* wBuf = new WCHAR[size + 1];
	char* buffer = new char[size + 1];
	file->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	wBuf[size] = '\0';
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wBuf, size + 1);
	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer, size + 1, 0, 0);
	// ��ȡ��Ϣ���ص����飬1��վ���Ӧ�����0��λ��
	for (int i = 0; i <= size; )
	{
		// ����վ������
		CString name;
		CString num;
		// �м���������������ת��
		vector<char>a;
		// ��һ�ζ�ȡ�������Ķ�ȡ�������У����һ�ȡ���Ĵ�С
		while (buffer[i] != ';')
		{
			a.push_back(buffer[i]);
			i++;
		}
		char* temp = new char[a.size() + 1];
		// �������е��ַ�ȡ���ŵ�char*��
		for (int i = 0; i < a.size(); i++)
			temp[i] = a[i];
		temp[a.size()] = '\0';
		// char*ת��ΪCString
		name = CA2CT(temp);
		delete temp;
		station.push_back(name);
		i++;
		// �������ֲ���
		while (buffer[i] != '#')
		{
			i++;
		}
		// ������#\r\n"
		i += 3;
		// �ж��ܷ�����������н�����
		if (buffer[i] == '!')
			break;
	}
	delete[] buffer;
	buffer = nullptr;
	delete[] wBuf;
	wBuf = nullptr;
}
/************************************************************
	 �������ƣ�ReadOneLineStationFromFile
	 ������������ȡĳһ����վ�����ݵ�����station(һ����վ��)
	 ����˵�����ļ�ָ�룬���޸ĵ�վ�㴢������
	 ����ֵ����
	 ���ߣ�����
*************************************************************/
void CMyFile::ReadOneLineStationFromFile(CFile* file, vector<CString>& station)
{
	// ���ļ���ȡ����
	INT size = file->GetLength();
	WCHAR* wBuf = new WCHAR[size + 1];
	char* buffer = new char[size + 1];
	file->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	wBuf[size] = '\0';
	MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wBuf, size + 1);
	WideCharToMultiByte(CP_ACP, 0, wBuf, -1, buffer, size + 1, 0, 0);
	// ��ȡ��Ϣ���ص����飬1��վ���Ӧ�����0��λ��
	for (int i = 0; i <= size; )
	{
		// ����վ������
		CString name;
		CString num;
		// �м���������������ת��
		vector<char>a;
		// ��һ�ζ�ȡ�������Ķ�ȡ�������У����һ�ȡ���Ĵ�С
		while (buffer[i] != '#')
		{
			a.push_back(buffer[i]);
			i++;
		}
		char* temp = new char[a.size() + 1];
		// �������е��ַ�ȡ���ŵ�char*��
		for (int i = 0; i < a.size(); i++)
			temp[i] = a[i];
		temp[a.size()] = '\0';
		// char*ת��ΪCString
		name = CA2CT(temp);
		delete temp;
		station.push_back(name);
		// ������#\r\n"
		i += 3;
		// �ж��ܷ�����������н�����
		if (buffer[i] == '!')
			break;
	}
	delete[] buffer;
	buffer = nullptr;
	delete[] wBuf;
	wBuf = nullptr;
}
/************************************************************
	 �������ƣ�ReadIndexFromFile
	 ������������ȡ����Ŀ¼���ļ�
	 ����˵�����ļ�ָ�룬��ȡ������Ŀ¼����
	 ����ֵ����
	 ���ߣ����������
*************************************************************/
void CMyFile::ReadIndexFromFile(CFile* file, vector<CString>& path)
{
		int temp = 0, size = file->GetLength();
		file->SeekToBegin();
		char* t = new char[size];
		file->Read(t, size);
		//���������ļ�Ŀ¼���ԡ�#������
		for (int i = 0;i < size;)
		{
			while (t[i] != '#')
			{
				temp = temp * 10 + t[i] - '0';
				i++;
			}
			//�����ļ����ơ�0.txt��
			CString temp1, temp2 = CString(".txt");
			temp1.Format(_T("%d"), temp);
			path.push_back(temp1);
			temp = 0;
			i += 1;
		}
}
/************************************************************
	 �������ƣ�WriteFileToIndex
	 ����������д�������ļ�
	 ����˵�����ļ�ָ�룬д�������Ŀ¼����
	 ����ֵ����
	 ���ߣ����������
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
	 �������ƣ�WriteInformation
	 ����������д��ʧ��������Ϣ
	 ����˵�����ļ�ָ�룬ʧ��������Ϣ���ĸ�CStringֵ
	 ����ֵ����
	 ���ߣ����������
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
	 �������ƣ�GetPath
	 ������������ȡ��ǰ·��
	 ����˵�����ļ�����
	 ����ֵ����
	 ���ߣ����������
*************************************************************/
void CMyFile::GetPath(CString cstrLoadPathName)
{
	//д���ļ�
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
	 �������ƣ�GetPath
	 ������������ȡʧ��������Ϣ
	 ����˵�����ļ�ָ�룬ʧ��������Ϣ���ĸ�CStringֵ
	 ����ֵ����
	 ���ߣ����������
*************************************************************/
void CMyFile::ReadFile(CFile* File, CString& content, CString& time, int& Line, int& station)
{
	INT size = File->GetLength();
	char* buffer = new char[size + 1];
	File->Read(buffer, size * sizeof(char));
	buffer[size] = '\0';
	//��ȡ��Ϣ���ص����飬1��վ���Ӧ�����0��λ��
	int i = 0;
	//�м���������������ת��
	vector<char>a;
	//��ȡʱ��
	while (buffer[i] != '#')
	{
		time += buffer[i];
		i++;
	}
	i += 1;
	//��ȡվ�����·
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
	//��ȡ������Ϣ
	while (buffer[i] != '#')
	{
		a.push_back(buffer[i]);
		i++;
	}
	char* temp = new char[a.size() + 1];
	//�������е��ַ�ȡ���ŵ�char*��
	for (int i = 0; i < a.size(); i++)
		temp[i] = a[i];
	//��������
	temp[a.size()] = '\0';
	// char * ת��ΪCString
	content = CA2CT(temp);

	delete[] temp;
	delete[] buffer;
	buffer = nullptr;
}
/************************************************************
	 �������ƣ�ReadUserFile
	 ������������ȡ�û�������Ϣ
	 ����˵�����ļ�ָ�룬������û��������롢���䡢�Ա� ��������㡢�����յ�
	 ����ֵ����
	 ���ߣ�������ʯ����
*************************************************************/
void CMyFile::ReadUserFile(CFile* file, CString& name, CString& password, CString& age, int& sex, int& s, int& p, int& q, int& r, int& t) 
{
	int size = file->GetLength();
	char* buff = new char[size];
	file->Read(buff, size * sizeof(char));
	int i = 0;
	//��ȡ�û���
	while (buff[i] != '#')
	{
		name += buff[i];
		i++;
	}
	i += 1;
	//��ȡ����
	while (buff[i] != '#')
	{
		password += buff[i];
		i++;
	}
	i++;
	//��������Ϣ���Ա�����...
	if (i != size)
	{
		//i += 2;
		//��ȡ����
		while (buff[i] != '#')
		{
			age += buff[i];
			i++;
		}
		i += 1;
		//��ȡ�Ա�
		while (buff[i] != '#')
		{
			sex = buff[i] - 48;
			i++;
		}
		i += 1;
		//��ȡ��·���
		while (buff[i] != '#')
		{
			t = buff[i] - 48;
			i++;
		}
		i += 1;
		//��ȡ��ʼվ��
		while (buff[i] != '#')
		{
			s = s * 10 + buff[i] - 48;
			i++;
		}
		i += 1;
		//��ȡ��·�յ�
		while (buff[i] != '#')
		{
			p = buff[i] - 48;
			i++;
		}
		i += 1;
		//��ȡ��ʼ�յ�
		while (buff[i] != '#')
		{
			q = q * 10 + buff[i] - 48;
			i++;
		}
	}
}
/************************************************************
	 �������ƣ�WriteUseFile
	 ����������д���û�������Ϣ
	 ����˵�����ļ�ָ�룬д����û��������롢���䡢�Ա𡢳�����㡢�����յ�
	 ����ֵ����
	 ���ߣ�������ʯ����
*************************************************************/
void CMyFile::WriteUseFile(CFile* file, CString& m_name, CString& password, CString& m_age, CString& a5, CString& a1, CString& a2, CString& a3, CString& a4,CString& temp)
{
	USES_CONVERSION;
	//תΪCString
	//ת����ʽд���ĵ�
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
	 �������ƣ�WriteUserNameAndPassSWordToFile
	 ����������д���û����û���������
	 ����˵�����ļ�ָ�룬д����û���������
	 ����ֵ����
	 ���ߣ�������ʯ����
*************************************************************/
void CMyFile::WriteUserNameAndPassSWordToFile(CFile* file, CString name, CString password)
{
	USES_CONVERSION;
	//תΪCString
	//ת����ʽд���ĵ�
	CString temp = CString("#");
	char* name1 = T2A(name);
	char* password1 = T2A(password);
	file->Write(name1, strlen(name1));
	file->Write(temp, temp.GetLength());
	file->Write(password1, strlen(password1));
	file->Write(temp, temp.GetLength());
}
