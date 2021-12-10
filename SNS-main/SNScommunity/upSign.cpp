#include "upSign.h"

SignUp::SignUp() {

}

SignUp::SignUp(std::string id, std::string pw) {
    this->id = id;
    this->pw = pw;
}

SignUp::~SignUp() {
}

std::string SignUp::get_id_() { return this->id; }
std::string SignUp::get_pw_() { return this->pw; }

void SignUp::sign_up_user_() {     //  회원가입에 쓰이는 함수, 파일에 맨 뒤에다가 입력
    std::string _id = this->get_id_();
    std::string _pw = this->get_pw_();
    std::fstream member_list;
    member_list.open("./data/member_information.txt", std::ios::app);
    member_list << _id;
    member_list.put('/');
    member_list << _pw;
    member_list.put('\n');
}

bool SignUp::is_exist_user_(std::string _id) {        //  회원가입 전에 이미 등록된 아이디가 있는지 확인하는 함수 -> 아이디로 확인
    std::fstream _member_list;
    _member_list.open("./data/member_information.txt", std::ios::in);
    std::string _member_info;     //  member_info -> buffer
    bool _flag = false;
    while (getline(_member_list, _member_info)) {
        int _id_idx = _member_info.find_first_of('/');
        std::string _compare_id = _member_info.substr(0, _id_idx);
        if (_id == _compare_id) {
            _flag = true;
            break;
        }
    }
    return _flag;
}

bool SignUp::is_correct_id_(std::string _id) {        //  사용자가 입력한 id 가 적절한 id인지를 검사하는 함수
    bool _flag = true;
    int _len = _id.length();
    if (_len >= 7 && _len <= 14) {      //  길이가 만족한 애들만 올바른 문자인지 검사
        for (int i = 0; i < _len; i++) {
            if ((_id[i] >= 'A' && _id[i] <= 'Z') || (_id[i] >= 'a' && _id[i] <= 'z') || (_id[i] >= '0' && _id[i] <= '9'))
                continue;
            else {
                _flag = false;
                break;
            }
        }

    }
    else
        _flag = false;
    return _flag;
}

bool SignUp::is_correct_pw_(std::string _pw) {
    bool _flag = true;
    int _len = _pw.length();
    if (_len >= 7 && _len <= 14) {      //  길이가 만족한 애들만 올바른 문자인지 검사
        for (int i = 0; i < _len; i++) {
            if (_pw[i] >= 33 && _pw[i] <= 126)       //  특수문자, 숫자, 소문자, 대문자
                continue;
            else {
                _flag = false;
                break;
            }
        }

    }
    else
        _flag = false;
    return _flag;
}

bool SignUp::sign_up_main_() {
    std::string _id, _pw;
    // system("clear");  //    for mac command
    system("cls"); //    for windows command
    std::cout << "==================================\n";
    std::cout << "아이디 : \n";
    std::cin >> _id;
    if (_id == "b" || _id == "B")
        return false;   //  만약 b/B 가 입력되면 false 로 return
    while (!is_correct_id_(_id)) {
        std::cout << "잘못된 입력방식입니다\n";
        Sleep(1000);
        // system("clear");  //    for mac command
        system("cls"); //    for windows command
        std::cout << "==================================\n";
        std::cout << "아이디 : \n";
        std::cin >> _id;
        if (_id == "b" || _id == "B")
            return false;   //  만약 b/B 가 입력되면 false 로 return
    }
    while (is_exist_user_(_id)) {
        std::cout << "이미 존재하는 아이디입니다\n";
        Sleep(1000);
        // system("clear");  //    for mac command
        system("cls"); //    for windows command
        std::cout << "==================================\n";
        std::cout << "아이디 : \n";
        std::cin >> _id;
        if (_id == "b" || _id == "B")
            return false;   //  만약 b/B 가 입력되면 false 로 return
        while (!is_correct_id_(_id)) {
            std::cout << "잘못된 입력방식입니다\n";
            Sleep(1000);
            // system("clear");  //    for mac command
            system("cls"); //    for windows command
            std::cout << "==================================\n";
            std::cout << "아이디 : \n";
            std::cin >> _id;
            if (_id == "b" || _id == "B")
                return false;   //  만약 b/B 가 입력되면 false 로 return
        }
    }
    // system("clear");
    system("cls");
    std::cout << "==================================\n";
    std::cout << "비밀번호 : \n";
    std::cin >> _pw;
    if (_pw == "b" || _pw == "B")
        return false;   //  만약 b/B 가 입력되면 false 로 return
    while (!is_correct_pw_(_pw)) {
        std::cout << "잘못된 입력방식입니다\n";
        Sleep(1000);
        // system("clear");  //    for mac command
        system("cls"); //    for windows command
        std::cout << "==================================\n";
        std::cout << "비밀번호 : \n";
        std::cin >> _pw;
        if (_pw == "b" || _pw == "B")
            return false;   //  만약 b/B 가 입력되면 false 로 return
    }
    // system("clear");
    system("cls");
    SignUp _user(_id, _pw);
    _user.sign_up_user_();
    std::cout << "회원가입 성공\n";
    return true;        //  올바른 return
}