#pragma once
#include <afxstr.h>
#include<vector>
#include <afx.h>
using namespace std;
/************************************************************
	 �����ƣ�CMyFile
	 �������������ļ���ȡ�Ľӿ��࣬��װ���еĶ��ļ��Ķ�д����
	 �ⲿ�����ӿڣ����к���
	 ���ߣ�all members
	 ע������ÿ���˵��õ�ʱ����ļ���ȡ�������ܲ�ͬ�����Զ�ֻ��CFileָ�����
	     �Һ����е�CFile�����رգ��ɵ��������йر��ļ��ͷ���Դ
*************************************************************/
class CMyFile {
public:
	// ��ȡȫ��վ����Ϣ������
	void ReadAllStationFromFile(CFile* file, vector<CString>&station);
	// ��ȡĳ����վ����Ϣ������
	void ReadOneLineStationFromFile(CFile* file, vector<CString>& station);
	// ��ȡ����Ŀ¼���ļ�
	void ReadIndexFromFile(CFile* file, vector<CString>& path);
	// д�������ļ�
	void WriteFileToIndex(CFile* file, vector<CString>& path);
	// д��ʧ��������Ϣ
	void WriteInformation(CFile* file, CString, CString, CString, CString);
	// ��ȡ��ǰ·��
	void GetPath(CString cstrLoadPathName);
	// ��ȡʧ��������Ϣ
	void ReadFile(CFile* File, CString& content, CString& time, int& Line, int& station);
	//��ȡ�û���Ϣ
	void ReadUserFile(CFile* file, CString& name, CString& password, CString& age, int& sex, int& s, int& p, int& q, int& r, int& t);
	//д���û���Ϣ
	void WriteUseFile(CFile* file, CString& m_name, CString& password, CString& m_age, CString& a5, CString& a1, CString& a2, CString& a3, CString& a4,CString& temp);
	// ֻд���û��û���������
	void WriteUserNameAndPassSWordToFile(CFile* file, CString name, CString password);
};