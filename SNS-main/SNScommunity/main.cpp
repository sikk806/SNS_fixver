#pragma once
#include "board.h"
#include "boardPost.h"
#include "upSign.h"
#include "LogIn.h"
#include "Note.h"

#include <io.h>
#include <direct.h>

using std::experimental::filesystem::directory_iterator;

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

using namespace std;

void setting_data_directory();
void notesSent(const string& userID);
void notesReceived(const string& userID);
bool isNumber(const string& str);

int main()
{
	setting_data_directory();

	Login lg_;
	lg_.main_promp();

	return 0;
}

void setting_data_directory()
{
	int data_directory_exists = _access("./data", 00);
	if (data_directory_exists == -1)
	{
		int nResult = _mkdir("./data");

		if (nResult == 0)
			cout << "������ ���丮 ����" << endl;
		else
			cout << "������ ���丮 ���� ����" << endl;
	}

	int data_post_1_directory_exists = _access("./data/post_1", 00);
	if (data_post_1_directory_exists == -1)
	{
		int nResult = _mkdir("./data/post_1");

		if (nResult == 0)
			cout << "post_1 ������ ���丮 ����" << endl;
		else
			cout << "post_1 ������ ���丮 ���� ����" << endl;
	}

	int data_post_2_directory_exists = _access("./data/post_2", 00);
	if (data_post_2_directory_exists == -1)
	{
		int nResult = _mkdir("./data/post_2");

		if (nResult == 0)
			cout << "post_2 ������ ���丮 ����" << endl;
		else
			cout << "post_2 ������ ���丮 ���� ����" << endl;
	}

	int data_post_3_directory_exists = _access("./data/post_3", 00);
	if (data_post_3_directory_exists == -1)
	{
		int nResult = _mkdir("./data/post_3");

		if (nResult == 0)
			cout << "post_3 ������ ���丮 ����" << endl;
		else
			cout << "post_3 ������ ���丮 ���� ����" << endl;
	}

	int data_post_4_directory_exists = _access("./data/post_4", 00);
	if (data_post_4_directory_exists == -1)
	{
		int nResult = _mkdir("./data/post_4");

		if (nResult == 0)
			cout << "post_4 ������ ���丮 ����" << endl;
		else
			cout << "post_4 ������ ���丮 ���� ����" << endl;
	}

	int data_sub_File_For_Merge_Category_directroy_exists = _access("./data/merge_Category", 00);
	if (data_sub_File_For_Merge_Category_directroy_exists == -1)
	{
		int nResult = _mkdir("./data/merge_Category");

		if (nResult == 0)
			cout << "merge_Category ������ ���丮 ����" << endl;
		else
			cout << "merge_Category ������ ���丮 ���� ����" << endl;
	}

	int data_manager_Category_File_exists = _access("./data/manager_Category,txt", 00);
	if(data_manager_Category_File_exists == -1)
	{
		string filename = "./data/manager_category.txt";
		ofstream openpost(filename);
		openpost << "post_1	����" << endl;
		openpost << "post_2	IT" << endl;
		openpost << "post_3	������" << endl;
		openpost << "post_4	������" << endl;
		openpost.close();
	}
}



void notesSent(const string& userID) {
    system("cls");
    std::cout << "======================================" << std::endl;
    std::cout << "���� ������                              " << std::endl;

    std::vector<Note> notesSent;
    std::vector<string> listOfRecipients;
    string PATH = ".";
    PATH += "/notes";
    if (!fs::is_empty(PATH))
    {
        for (const auto& entry : directory_iterator(PATH))
        {
            if (fs::path(entry.path()).filename() == ".DS_Store")
                continue;
            //userID�� ���� ���� ������ ������ ���� �����ϼ��� ���� (���� ���� �ִ� ���̵�� �޴»���̸�)
            //���� ���� ���̵� ������
            if (fs::path(entry.path()).filename().string().find(userID) == string::npos)
            {
                unsigned long first = fs::path(entry.path()).filename().string().find("_-");
                unsigned long last = fs::path(entry.path()).filename().string().find("-.");

                string HEAD_PATH = PATH + "/"; // ./notes/��� ���� �̸�.txt
                HEAD_PATH += fs::path(entry.path()).filename().u8string();
                std::ifstream f(HEAD_PATH);

                string s;
                while (getline(f, s))
                {
                    string id = "";
                    string temp = "";
                    bool hasBeenOpened;
                    string noteContent = "";
                    int foo = 0;
                    for (auto x : s)
                    {
                        if (x == '\t' && foo == 0)
                        {
                            foo++;
                            //������ ���� ������ �ƴϸ� break
                            if (id != userID) {
                                break;
                            }
                            else {
                                listOfRecipients.push_back(fs::path(entry.path()).filename().
                                    string().substr(first + 2, last - first - 2));
                            }
                        }
                        else if (x == '\t' && foo == 1)
                        {
                            foo++;
                            hasBeenOpened = temp == "1" ? true : false;
                        }
                        else if (foo == 0)
                        {
                            id = id + x;
                        }
                        else if (foo == 1)
                        {
                            temp = temp + x;
                        }
                        else if (foo == 2)
                        {
                            noteContent = noteContent + x;
                        }
                    }
                    if (temp != "")
                    {

                        notesSent.push_back(Note(id, hasBeenOpened, noteContent));
                    }
                }
            }
        }
    }

    string input;
    do
    {
        string str = "";
        int index = 1;

        for (Note n : notesSent)
        {
            str += std::to_string(index) + ". �޴� ��� : ";
            str += listOfRecipients.at(index - 1) + "," + (n.hasBeenOpened ? "����" : "������") + "\n";

            vector<char> content;
            string copy = n.noteContent;
            for (int i = 0; i < n.noteContent.length(); i++) {
                content.push_back(copy[i]);
            }
            int wordCount = 0;


            for (int i = 0; i < n.noteContent.length(); i++)

            {
                str += content[i];
                wordCount++;
                if (wordCount >= 20)
                    break;
            }
            str += "...\n";

            index++;
            if (index == notesSent.size())
                str += "===================================\n";
            else
                str += "-----------------------------------\n";
        }
        str += "������ ������ ��ȣ�� �Է����ּ���.\n";
        str += "(b/B :  �ڷΰ���)\n";
        str += "�Է�: \n";
        std::cout << str << std::endl;
        str += "===============================\n";
        std::cin >> input;
        if (isNumber(input))
        {
            if (stoi(input) > listOfRecipients.size() || stoi(input) == 0 || notesSent.at(stoi(input) - 1).hasBeenOpened == true)
            {
                std::cout << "�ùٸ��� ���� �Է��Դϴ�, �ٽ� �Է��ϼ���" << std::endl;
                Sleep(1000);
                continue;
            }
            else if (notesSent.at(stoi(input) - 1).hasBeenOpened == false)
            {
                std::ifstream f("./notes/note_-" + listOfRecipients.at(stoi(input) - 1) + "-.txt");
                int numLine = 0;
                string deletedContent = "";
                string s;
                while (getline(f, s))
                {
                    numLine++;
                    if (numLine != stoi(input))
                    {
                        deletedContent += s + "\n";
                    }
                }
                f.close();
                std::ofstream os;
                os.open("./notes/note_-" + listOfRecipients.at(stoi(input) - 1) + "-.txt");
                os << deletedContent;
                os.close();
                //���� ������ vector���� erase
                listOfRecipients.erase(listOfRecipients.begin() + stoi(input) - 1);
                notesSent.erase(notesSent.begin() + stoi(input) - 1);
                std::cout << "======================================" << std::endl;
                std::cout << "���� ������                              " << std::endl;
            }
        }
        else if (input != "B" && input != "b")
        {
            std::cout << input << std::endl;
            std::cout << "�ùٸ��� ���� �Է��Դϴ�, �ٽ� �Է��ϼ���" << std::endl;

            Sleep(1000);
            continue;
        }
    } while (input != "B" && input != "b");
    Login l;
    l.select_note(userID);
}

bool isNumber(const string& str)
{
    for (char const& c : str)
    {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void notesReceived(const string& userID) {
    system("cls");
    std::cout << "======================================" << std::endl;
    std::cout << "���� ������                              " << std::endl;

    std::vector<Note> notesReceived;
    std::vector<string> listOfSenders;
    string PATH = ".";
    PATH += "/notes";
    if (!fs::is_empty(PATH))
    {
        for (const auto& entry : directory_iterator(PATH))
        {
            if (fs::path(entry.path()).filename() == ".DS_Store")
                continue;
            //userID�� �ؽ�Ʈ ���� ���� ������, userID���� ���� ����
            if (fs::path(entry.path()).filename().string().find(userID) != string::npos)
            {
                string HEAD_PATH = PATH + "/"; // ./notes/��� ���� �̸�.txt
                HEAD_PATH += fs::path(entry.path()).filename().u8string();
                std::ifstream f(HEAD_PATH);
                string s;
                while (getline(f, s))
                {
                    string id = "";
                    string temp = "";
                    bool hasBeenOpened;
                    string noteContent = "";
                    int foo = 0;
                    for (auto x : s)
                    {
                        if (x == '\t' && foo == 0)
                        {
                            foo++;
                            listOfSenders.push_back(id);
                        }
                        else if (x == '\t' && foo == 1)
                        {
                            foo++;
                            hasBeenOpened = temp == "1" ? true : false;
                        }
                        else if (foo == 0)
                        {
                            id = id + x;
                        }
                        else if (foo == 1)
                        {
                            temp = temp + x;
                        }
                        else if (foo == 2)
                        {
                            noteContent = noteContent + x;
                        }
                    }
                    if (temp != "")
                    {
                        notesReceived.push_back(Note(id, hasBeenOpened, noteContent));
                    }
                }
            }
        }
    }

    string input;
    do
    {
        string str = "";
        int index = 1;
        for (Note n : notesReceived)
        {
            str += std::to_string(index) + ". ���� ��� : ";
            str += n.senderID + "\n";
            string specialChar = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

            vector<char> content;
            string copy = n.noteContent;
            for (int i = 0; i < n.noteContent.length(); i++) {
                content.push_back(copy[i]);
            }
            int wordCount = 0;


            for (int i = 0; i < n.noteContent.length(); i++)

            {
                str += content[i];
                wordCount++;
                if (wordCount >= 20)
                    break;
            }
            str += "...\n";

            index++;
            if (index == notesReceived.size())
                str += "===================================\n";
            else
                str += "-----------------------------------\n";
        }
        str += "Ȯ���� ������ ��ȣ�� �Է����ּ���.\n";
        str += "(b/B :  �ڷΰ���)\n";
        str += "�Է�: \n";
        std::cout << str << std::endl;
        str += "===============================\n";
        std::cin >> input;
        if (isNumber(input))
        {
            cout << "input : " << input << " listOfSenders : " << listOfSenders.size() << endl;
            if (stoi(input) > listOfSenders.size() || stoi(input) == 0)
            {
                std::cout << "�ùٸ��� ���� �Է��Դϴ�, �ٽ� �Է��ϼ���" << std::endl;
                Sleep(1000);
                continue;
            }
            else
            {
                string bar;
                do
                {
                    std::cout << "======================================" << std::endl;
                    std::cout << "���� ���: " << notesReceived.at(stoi(input) - 1).senderID << std::endl;
                    std::cout << "======================================" << std::endl;
                    std::cout << notesReceived.at(stoi(input) - 1).noteContent << std::endl;
                    std::ifstream f("./notes/note_-" + userID + "-.txt");
                    int numLine = 0;
                    string contentAfter = "";
                    string s;
                    while (getline(f, s))
                    {
                        numLine++;
                        if (numLine != stoi(input))
                            contentAfter += s + "\n";
                        else
                            contentAfter += notesReceived.at(stoi(input) - 1).senderID + "\t" + "1" + "\t" + notesReceived.at(stoi(input) - 1).noteContent + "\n";
                    }
                    f.close();
                    std::ofstream os;
                    os.open("./notes/note_-" + userID + "-.txt");
                    os << contentAfter;
                    os.close();
                    notesReceived.at(stoi(input) - 1).hasBeenOpened = true;
                    std::cout << "======================================" << std::endl;
                    std::cout << "(b/B :  �ڷΰ���)\n";
                    std::cout << "�Է�: \n";
                    std::cin >> bar;
                } while (bar != "B" && bar != "b");
            }
        }
    } while (input != "B" && input != "b");
    Login l;
    l.select_note(userID);
}