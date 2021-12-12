#pragma once
#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "boardPost.h"
#include "upSign.h"
#include "LogIn.h"
#include <afxwin.h> // for windows header ( 실행 안되면 afx.h )
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
	void selectCategory(string user_id); // 카테고리 선택
	void createPost(string _userid, string _category, int _postnum); // 글 작성
	void mainPost(string _userid, string _category, int _getFile); // 글 목록
	void setColor(unsigned short text); // windows.h를 사용하는 함수 Mac에서 불가능할 경우 삭제.
	void managerCategory(string user_id);
	void changeCategoryName(string user_id);
	void changeName(string user_id, int selectCategory, vector<string>& name, int check);
	void addCategory(string user_id);
	void mergeCategory(string user_id);
	void deleteCategory(string user_id);
	void change_Category(string _postname, string _userid);

	void mergingFolders(string user_id, string _merge1, string _merge2);
	int lineFile(string _filename);
	int numFile(string _category); // 폴더내 파일 갯수
	bool checkWords(string _words); // 공백을 포함한 아라비아 숫자,한글과 영어로만 이루어진 문자열인지 여부를 검사
};