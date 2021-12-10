#include "LogIn.h"

extern void notesSent(const string& userID);
extern void notesReceived(const string& userID);

Login::Login() {

}

Login::~Login() {

}

Login::Login(const string& ID, const string& pw)
    :userID(ID), password(pw)
{

}

void Login::login()
{
    ifstream file("./data/member_information.txt", ios::in); //파일 불러오기
    vector<string> result;
    bool flag;
    if (file.is_open())
    {
        string user;
        while (getline(file, user)) //파일 읽기
        {
            stringstream ss(user);
            flag = false;
            result.clear();
            while (ss.good())   //id와 pw가져오기
            {
                string substr;
                getline(ss, substr, '/');
                result.push_back(substr);
            }
            //파일에서 읽은 아이디/비번과 일치하는지 확인
            for (int i = 0; i < result.size(); i += 2)
            {
                if (result.at(i) == userID && result.at(i + 1) == password)
                {
                    // 로그인 성공
                    cout << "Login successful: " << userID << ", " << password << endl;
                    Sleep(1000);
                    flag = true;
                    //다음 과정 진행
                    //Board b;
                    // 카테고리 vs 쪽지함
                    //1. 카테고리
                    //b.selectCategory(userID);
                    //2. 쪽지함
                    /*1. 쪽지 보내기(SendNote) : 받는 사람 ID(recipient) 입력 받아서. 
                    2.보낸 쪽지함 : noteSent(userID) : 삭제는 내부 구현
                    3. 받은 쪽지함 : notesReceived(userID) : 삭제는 내부 구현
                    */
                    select_cat_note(userID);
                }
            }
            if (flag) //이미 일치하는 아이디/비번을 찾았으면 더이상 읽지 않는다
                break;
        }
        if (!flag) {
            cout << "Login failed: " << userID << ", " << password << endl;
            Sleep(1000);
        }
        file.close();
    }
    else //파일 불러오기 실패
    {
        cout << "Failed to open file" << endl;
        Sleep(1000);
    }
}

void Login::select_cat_note(string userid) {
    system("cls");
    cout << "1. 카테고리 선택" << endl;
    cout << "2. 쪽지함" << endl;
    cout << endl;
    cout << "0. 로그아웃" << endl;

    string select;
    cin >> select;

    Board b;

    if (select == "1") {
        b.selectCategory(userid);
    }
    else if (select == "2") {
        select_note(userid);
    }
    else if (select == "0") {
        cout << "로그아웃...." << endl;
        Sleep(1000);
        return;
    }
    else {
        cout << "잘못 입력하셨습니다." << endl;
        Sleep(1000);
        select_cat_note(userid);
    }
}

void Login::select_note(string userid) {
    system("cls");
    cout << "1. 쪽지 보내기" << endl;
    cout << "2. 보낸 쪽지함" << endl;
    cout << "3. 받은 쪽지함" << endl;
    cout << endl;
    cout << "0. 뒤로가기" << endl;

    Note n;
    string select;
    cin >> select;

    if (select == "1") {
        n.send_note(userid);
    }
    else if (select == "2") {
        notesSent(userid);
    }
    else if (select == "3") {
        notesReceived(userid);
    }
    else if (select == "0") {
        select_cat_note(userid);
    }
    else {
        cout << "잘못 입력하셨습니다." << endl;
        Sleep(1000);
        select_note(userid);
    }
    

}
