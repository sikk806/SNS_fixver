#include "upSign.h"
#include "LogIn.h"

int Login::show_main_promp_() {
    int cmd;
    system("cls");
    std::cout << "1. 로그인\n";
    std::cout << "2. 회원가입\n";
    std::cout << "3. 종료\n";
    std::cin >> cmd;
    return cmd;
}

void Login::main_promp() {
    while (true) {
        int cmd = show_main_promp_();
        if (cmd == 3) {
            cout << "종료합니다." << endl;
            Sleep(1000);
            break;
        }
        else if (cmd == 1) {
            std::string id_, pw_;
            // system("clear");  //    for mac command
            system("cls"); //    for windows command
            std::cout << "==================================\n";
            std::cout << "아이디 : \n";
            std::cin >> id_;
            if (id_ == "B" || id_ == "b")
                continue;
            std::cout << "비밀번호 : ";
            // system("clear");  //    for mac command
            system("cls"); //    for windows command
            std::cout << "==================================\n";
            std::cout << "비밀번호 : \n";
            std::cin >> pw_;
            if (pw_ == "B" || pw_ == "b")
                continue;
            Login user(id_, pw_);
            user.login();
        }
        else if (cmd == 2) {
            SignUp temp_;
            bool flag = temp_.sign_up_main_();
            if (!flag)
                continue;
        }
        else {
            std::cout << "올바른 입력이 아닙니다\n";
            Sleep(1000);
        }
    }
}
