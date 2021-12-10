#pragma once
#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//#include <curses.h>
#include <stdlib.h>
#include <cctype>
#include <cstdio>
#include <experimental/filesystem>

using namespace std;
namespace fs = std::experimental::filesystem::v1;

class boardPost {
private:

public:
	boardPost();
	~boardPost();
	void Post(string _filename, string _userid);
	int Report(int data);
	int check_fspace(string s);
	int check_(string s);
	//void change_Category(string _postname, string _userid);

};