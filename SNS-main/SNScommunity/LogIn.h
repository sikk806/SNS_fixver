#pragma once
#include "board.h"
#include "Note.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

using std::string;
class Login
{
private:
    string userID;
    string password;
public:
    Login();
    ~Login();
    Login(const string& ID, const string& pw);
    void login();
    int show_main_promp_();
    void main_promp();
    void select_cat_note(string userid);
    void select_note(string userid);
};
