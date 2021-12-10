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

void SignUp::sign_up_user_() {     //  ȸ�����Կ� ���̴� �Լ�, ���Ͽ� �� �ڿ��ٰ� �Է�
    std::string _id = this->get_id_();
    std::string _pw = this->get_pw_();
    std::fstream member_list;
    member_list.open("./data/member_information.txt", std::ios::app);
    member_list << _id;
    member_list.put('/');
    member_list << _pw;
    member_list.put('\n');
}

bool SignUp::is_exist_user_(std::string _id) {        //  ȸ������ ���� �̹� ��ϵ� ���̵� �ִ��� Ȯ���ϴ� �Լ� -> ���̵�� Ȯ��
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

bool SignUp::is_correct_id_(std::string _id) {        //  ����ڰ� �Է��� id �� ������ id������ �˻��ϴ� �Լ�
    bool _flag = true;
    int _len = _id.length();
    if (_len >= 7 && _len <= 14) {      //  ���̰� ������ �ֵ鸸 �ùٸ� �������� �˻�
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
    if (_len >= 7 && _len <= 14) {      //  ���̰� ������ �ֵ鸸 �ùٸ� �������� �˻�
        for (int i = 0; i < _len; i++) {
            if (_pw[i] >= 33 && _pw[i] <= 126)       //  Ư������, ����, �ҹ���, �빮��
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
    std::cout << "���̵� : \n";
    std::cin >> _id;
    if (_id == "b" || _id == "B")
        return false;   //  ���� b/B �� �ԷµǸ� false �� return
    while (!is_correct_id_(_id)) {
        std::cout << "�߸��� �Է¹���Դϴ�\n";
        Sleep(1000);
        // system("clear");  //    for mac command
        system("cls"); //    for windows command
        std::cout << "==================================\n";
        std::cout << "���̵� : \n";
        std::cin >> _id;
        if (_id == "b" || _id == "B")
            return false;   //  ���� b/B �� �ԷµǸ� false �� return
    }
    while (is_exist_user_(_id)) {
        std::cout << "�̹� �����ϴ� ���̵��Դϴ�\n";
        Sleep(1000);
        // system("clear");  //    for mac command
        system("cls"); //    for windows command
        std::cout << "==================================\n";
        std::cout << "���̵� : \n";
        std::cin >> _id;
        if (_id == "b" || _id == "B")
            return false;   //  ���� b/B �� �ԷµǸ� false �� return
        while (!is_correct_id_(_id)) {
            std::cout << "�߸��� �Է¹���Դϴ�\n";
            Sleep(1000);
            // system("clear");  //    for mac command
            system("cls"); //    for windows command
            std::cout << "==================================\n";
            std::cout << "���̵� : \n";
            std::cin >> _id;
            if (_id == "b" || _id == "B")
                return false;   //  ���� b/B �� �ԷµǸ� false �� return
        }
    }
    // system("clear");
    system("cls");
    std::cout << "==================================\n";
    std::cout << "��й�ȣ : \n";
    std::cin >> _pw;
    if (_pw == "b" || _pw == "B")
        return false;   //  ���� b/B �� �ԷµǸ� false �� return
    while (!is_correct_pw_(_pw)) {
        std::cout << "�߸��� �Է¹���Դϴ�\n";
        Sleep(1000);
        // system("clear");  //    for mac command
        system("cls"); //    for windows command
        std::cout << "==================================\n";
        std::cout << "��й�ȣ : \n";
        std::cin >> _pw;
        if (_pw == "b" || _pw == "B")
            return false;   //  ���� b/B �� �ԷµǸ� false �� return
    }
    // system("clear");
    system("cls");
    SignUp _user(_id, _pw);
    _user.sign_up_user_();
    std::cout << "ȸ������ ����\n";
    return true;        //  �ùٸ� return
}