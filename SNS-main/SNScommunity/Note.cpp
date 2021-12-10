#include "Note.h"
#include "LogIn.h"


using std::string;
using std::experimental::filesystem::directory_iterator;
namespace fs = std::experimental::filesystem::v1;

Note::Note() {

}
Note::~Note() {

}

Note::Note(const string& senderID, const string noteContent)
    :senderID(senderID), noteContent(noteContent), hasBeenOpened(false)
{

}

Note::Note(const string& senderID, bool hasBeenOpened, const string noteContent)
    : senderID(senderID), hasBeenOpened(hasBeenOpened), noteContent(noteContent)
{

}

void Note::sendNote(const string& recipient)
{
    //notes��� �̸��� ������ ���� ��� ���丮 ����
    fs::path PATH = fs::current_path();
    PATH += "/notes";
    if (!fs::exists(PATH))
        fs::create_directory(PATH);

    if (!(noteContent.length() >= 2 && noteContent.length() <= 100))
        return;

    PATH += "/note_-" + recipient + "-.txt";
    //���� �̸��� ������ �ִ��� Ȯ�� X, ����������
    string HEAD_PATH = ".\\notes\\note_-" + recipient + "-.txt";
    std::ofstream note;

    if (fs::exists(HEAD_PATH))
    {
        note.open(HEAD_PATH, std::ios_base::app);
        note << senderID << "\t" << hasBeenOpened << "\t" << noteContent << "\n";
    }
    else
    {
        note.open(HEAD_PATH, std::ios_base::trunc);
        note << senderID << "\t" << hasBeenOpened << "\t" << noteContent << "\n";
    }

    note.close();
}

void Note::send_note(const string& userid) {
    system("cls");
    Login l;
    string rec;
    string letter;

    std::cout << "�������� �����ðڽ��ϱ�?. : ";
    std::cin >> rec;
    if (rec == userid) {
        std::cout << "���ο��Դ� ���� �� �����ϴ�. " << std::endl;
        Sleep(1000);
        send_note(userid);
    }
    else {
        std::cout << "- ���� ���� - " << std::endl;
        std::cin >> letter;

        senderID = userid;
        Note note(senderID, letter);

        note.sendNote(rec);
        l.select_note(userid);
    }
}