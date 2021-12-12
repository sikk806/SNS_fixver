#pragma once
#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "boardPost.h"
#include "upSign.h"
#include "LogIn.h"
#include <afxwin.h> // for windows header ( ���� �ȵǸ� afx.h )
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h> // for windows header
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <errno.h>
#include <experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class Board {
private:

public:
	Board();
	~Board();
	void selectCategory(string user_id); // ī�װ� ����
	void createPost(string _userid, string _category, int _postnum); // �� �ۼ�
	void mainPost(string _userid, string _category, int _getFile); // �� ���
	void setColor(unsigned short text); // windows.h�� ����ϴ� �Լ� Mac���� �Ұ����� ��� ����.
	void managerCategory(string user_id);
	void changeCategoryName(string user_id);
	void changeName(string user_id, int selectCategory, vector<string>& name, int check);
	void addCategory(string user_id);
	void mergeCategory(string user_id);
	void deleteCategory(string user_id);
	void change_Category(string _postname, string _userid);

	void mergingFolders(string user_id, string _merge1, string _merge2);
	int lineFile(string _filename);
	int numFile(string _category); // ������ ���� ����
	bool checkWords(string _words); // ������ ������ �ƶ��� ����,�ѱ۰� ����θ� �̷���� ���ڿ����� ���θ� �˻�
};