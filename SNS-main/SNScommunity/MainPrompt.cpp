#include "upSign.h"
#include "LogIn.h"

int Login::show_main_promp_() {
    int cmd;
    system("cls");
    std::cout << "1. �α���\n";
    std::cout << "2. ȸ������\n";
    std::cout << "3. ����\n";
    std::cin >> cmd;
    return cmd;
}

void Login::main_promp() {
    while (true) {
        int cmd = show_main_promp_();
        if (cmd == 3) {
            cout << "�����մϴ�." << endl;
            Sleep(1000);
            break;
        }
        else if (cmd == 1) {
            std::string id_, pw_;
            // system("clear");  //    for mac command
            system("cls"); //    for windows command
            std::cout << "==================================\n";
            std::cout << "���̵� : \n";
            std::cin >> id_;
            if (id_ == "B" || id_ == "b")
                continue;
            std::cout << "��й�ȣ : ";
            // system("clear");  //    for mac command
            system("cls"); //    for windows command
            std::cout << "==================================\n";
            std::cout << "��й�ȣ : \n";
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
            std::cout << "�ùٸ� �Է��� �ƴմϴ�\n";
            Sleep(1000);
        }
    }
}
