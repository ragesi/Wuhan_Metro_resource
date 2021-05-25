#pragma once
#include <afxstr.h>
#include<vector>
#include <afx.h>
using namespace std;
/************************************************************
	 类名称：CMyFile
	 功能描述：对文件读取的接口类，包装所有的对文件的读写操作
	 外部函数接口：所有函数
	 作者：all members
	 注：由于每个人调用的时候对文件读取参数可能不同，所以都只传CFile指针进来
	     且函数中的CFile都不关闭，由调用者自行关闭文件释放资源
*************************************************************/
class CMyFile {
public:
	// 读取全部站点信息到数组
	void ReadAllStationFromFile(CFile* file, vector<CString>&station);
	// 读取某条线站点信息到数组
	void ReadOneLineStationFromFile(CFile* file, vector<CString>& station);
	// 读取索引目录到文件
	void ReadIndexFromFile(CFile* file, vector<CString>& path);
	// 写入索引文件
	void WriteFileToIndex(CFile* file, vector<CString>& path);
	// 写入失物招领信息
	void WriteInformation(CFile* file, CString, CString, CString, CString);
	// 获取当前路径
	void GetPath(CString cstrLoadPathName);
	// 读取失物招领信息
	void ReadFile(CFile* File, CString& content, CString& time, int& Line, int& station);
	//读取用户信息
	void ReadUserFile(CFile* file, CString& name, CString& password, CString& age, int& sex, int& s, int& p, int& q, int& r, int& t);
	//写入用户信息
	void WriteUseFile(CFile* file, CString& m_name, CString& password, CString& m_age, CString& a5, CString& a1, CString& a2, CString& a3, CString& a4,CString& temp);
	// 只写入用户用户名和密码
	void WriteUserNameAndPassSWordToFile(CFile* file, CString name, CString password);
};