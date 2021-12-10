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
    ifstream file("./data/member_information.txt", ios::in); //���� �ҷ�����
    vector<string> result;
    bool flag;
    if (file.is_open())
    {
        string user;
        while (getline(file, user)) //���� �б�
        {
            stringstream ss(user);
            flag = false;
            result.clear();
            while (ss.good())   //id�� pw��������
            {
                string substr;
                getline(ss, substr, '/');
                result.push_back(substr);
            }
            //���Ͽ��� ���� ���̵�/����� ��ġ�ϴ��� Ȯ��
            for (int i = 0; i < result.size(); i += 2)
            {
                if (result.at(i) == userID && result.at(i + 1) == password)
                {
                    // �α��� ����
                    cout << "Login successful: " << userID << ", " << password << endl;
                    Sleep(1000);
                    flag = true;
                    //���� ���� ����
                    //Board b;
                    // ī�װ� vs ������
                    //1. ī�װ�
                    //b.selectCategory(userID);
                    //2. ������
                    /*1. ���� ������(SendNote) : �޴� ��� ID(recipient) �Է� �޾Ƽ�. 
                    2.���� ������ : noteSent(userID) : ������ ���� ����
                    3. ���� ������ : notesReceived(userID) : ������ ���� ����
                    */
                    select_cat_note(userID);
                }
            }
            if (flag) //�̹� ��ġ�ϴ� ���̵�/����� ã������ ���̻� ���� �ʴ´�
                break;
        }
        if (!flag) {
            cout << "Login failed: " << userID << ", " << password << endl;
            Sleep(1000);
        }
        file.close();
    }
    else //���� �ҷ����� ����
    {
        cout << "Failed to open file" << endl;
        Sleep(1000);
    }
}

void Login::select_cat_note(string userid) {
    system("cls");
    cout << "1. ī�װ� ����" << endl;
    cout << "2. ������" << endl;
    cout << endl;
    cout << "0. �α׾ƿ�" << endl;

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
        cout << "�α׾ƿ�...." << endl;
        Sleep(1000);
        return;
    }
    else {
        cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
        Sleep(1000);
        select_cat_note(userid);
    }
}

void Login::select_note(string userid) {
    system("cls");
    cout << "1. ���� ������" << endl;
    cout << "2. ���� ������" << endl;
    cout << "3. ���� ������" << endl;
    cout << endl;
    cout << "0. �ڷΰ���" << endl;

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
        cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
        Sleep(1000);
        select_note(userid);
    }
    

}
