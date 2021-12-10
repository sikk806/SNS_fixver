#include "boardPost.h"
// #include <curses.h>
#include <Windows.h>
#include <cctype>
//#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <io.h>
#include <direct.h>

#include <filesystem>
#include <time.h>

using namespace std;
/*
long _findfirst(char *filespec, struct _finddata_t *fileinfo);
int _findnext(long handle, struct _finddata_t *fileinfo);
int _findclose(long handle);
*/
// string _title;
// string _contents;
// string _date;
// int _recommand;
// string comment;
// int _datanum;
// string _userid;
// int _report;

boardPost::boardPost()
{
}

boardPost::~boardPost()
{
}

int boardPost::check_fspace(string s)
{
	int front = s.front();
	int back = s.back();
	if (isspace(front) != 0 || isspace(back) != 0)
	{
		return 0;
	}
	else
		return 1;
}

int boardPost::check_(string s)
{
	bool check = false;
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s.at(i)) || isalpha(s.at(i)) || ((s.at(i) & 0X80) == 0x80) || (s.at(i) == ' '))
			check = false;
		else
			check = true;
		break;
	}
	if (check)
	{
		return 1;
	}
	return 0;
}



//????? ??????? ??????? ???????.
void boardPost::Post(string _filename, string _userid)
{
	while (1)
	{
		int com_num = 0;
		string _file = "./data/";
		string _postname = _file + _filename;
		fstream postinfo;
		postinfo.open(_postname, ios::in | ios::out);
		string line;
		string s;
		char cstr[1000];
		getline(postinfo, line);
		stringstream ss(line);
		vector<string> data;
		stringstream aa;
		postinfo.seekg(0, ios::end);
		int size = postinfo.tellg();
		s.resize(size);
		postinfo.seekg(0, ios::beg);
		postinfo.read(&s[0], size);
		// s.erase(remove(s.begin(), s.end(), '\n'), s.end());
		strcpy(cstr, s.c_str());
		char* ptr = strtok(cstr, "\t");
		while (ptr != NULL)
		{
			string st;
			st = ptr;
			data.push_back(st);
			ptr = strtok(NULL, "\t");
		}
		postinfo.close();
		if (data.size() == 6)
		{
			com_num = 0;
		}
		else
		{
			int count = data.size();
			com_num = (count - 7) / 2;
		}

		system("cls");
		// system("clear"); // Mac용 system("cls")

		cout << "============================" << endl;
		cout << data[2] << endl;
		cout << "제목 "
			<< " : " << data[3] << endl;
		cout << "본문"
			<< " : " << data[4] << endl;
		cout << "신고"
			<< ": " << data[5] << " 추천"
			<< ": " << data[6] << endl;
		cout << "============================" << endl;
		cout << "댓글" << endl;
		int j = 1;
		for (int i = 7; i < data.size(); i++)
		{

			if (i % 2 != 0)
			{
				cout << j++ << ". " << _userid << " : ";
			}
			else
			{
				cout << data[i] << endl;
			}
		}
		cout << "============================" << endl;
		cout << "1.댓글 작성"
			<< "/"
			<< " 2.신고"
			<< "/"
			<< " 3.추천"
			<< "/"
			<< " 4.수정 "
			<< "/"
			<< " 5.댓글 삭제 "
			<< "/"
			<< " 6.게시글 삭제 "
			<< "/";
		if (_userid == "manager") {
			cout << " 7.게시글 이동 ";
			cout << "/";
		}
		cout << " 뒤로가기(B/b)" << endl;
		string command;
		cin >> command;
		cin.ignore();
		if (command == "1")
		{
			//??? ????
			while (1)
			{
				system("cls");
				// system("clear");
				cout << "댓글 : ";
				string s;
				// cin.ignore();
				// getline(cin, s);
				string s1;
				while (1)
				{
					// cin.ignore();
					getline(cin, s1);
					if (s1.find('\t') == string::npos)
					{
						s = s + s1 + '\n';
					}
					else
					{
						int index = s1.find('\t');
						for (int i = 0; i < index; i++)
						{
							s = s + s1.at(i);
						}
						break;
					}
				}
				if (s.empty())
				{
					cout << "잘못된 입력방식입니다1" << endl;
					Sleep(1000);
					// sleep(1);
				}
				else if (s.size() == 1 && (s.compare("b") == 0 || s.compare("B") == 0))
				{
					break;
					//back show
				}
				//(s.size() != s1.size()) ||
				else if (s.size() < 2 || s.size() > 100)
				{
					cout << "잘못된 입력방식입니다3" << endl;
					Sleep(1000);
					// sleep(1);
				}
				else
				{
					string a;
					cout << "작성을 완료하시겠습니까?(y or n)";
					cin >> a;
					if (a == "y" || a == "Y")
					{
						data.push_back(_userid);
						data.push_back(s);
						postinfo.open(_postname, ios::app);
						postinfo << _userid;
						postinfo.put('\t');
						postinfo << s;
						postinfo.put('\t');
						postinfo.close();
						break;
					}
					else if (a == "n" || a == "N")
					{
						break;
						//back show
					}
					else
					{
						cout << "잘못된 입력방식입니다3" << endl;
						Sleep(1000);
						// sleep(1);
						//back show
					}
				}
			}
		}
		else if (command == "2")
		{
			cout << "신고를 하시겠습니까?" << endl;
			string command_report;
			cin >> command_report;
			cin.ignore();
			if (command_report == "Y" || command_report == "y")
			{
				//????? += 1
				fstream post_content;
				post_content.open(_postname, ios::out);
				int num_report = stoi(data[5]);
				num_report += 1;
				data[5] = to_string(num_report);
				for (int j = 0; j < 7; j++)
				{
					post_content << data[j];
					post_content.put('\t');
				}
				for (int i = 7; i < data.size(); i++)
				{
					post_content << data[i];
					post_content.put('\t');
				}
				post_content.close();
			}
			else if (command_report == "N" || command_report == "n")
			{
				//??? ???
			}
			else
			{
				//입력오류
				cout << "잘못된 입력입니다." << endl;
				Sleep(1000);
				// sleep(1);
			}
		}
		else if (command == "3")
		{
			cout << "추천을 하시겠습니까?" << endl;
			string command_recommand;
			cin >> command_recommand;
			if (command_recommand == "Y" || command_recommand == "y")
			{
				//????? += 1
				int num_recommand = stoi(data[6]);
				num_recommand += 1;
				data[6] = to_string(num_recommand);
				fstream post_content;
				post_content.open(_postname, ios::out);
				for (int j = 0; j < 7; j++)
				{
					post_content << data[j];
					post_content.put('\t');
				}
				for (int i = 7; i < data.size(); i++)
				{
					post_content << data[i];
					post_content.put('\t');
				}
				post_content.close();
			}
			else if (command_recommand == "N" || command_recommand == "n")
			{
				//??????
			}
			else
			{
				//입력오류
				cout << "잘못된 입력입니다." << endl;
				Sleep(1000);
				// sleep(1);
			}
		}

		else if (command == "4")
		{
			//********user_id 와 data[1] 비교 알고리즘 필요!*********
			if (_userid == data[1] || _userid == "manager")
			{
				system("cls");
				// system("clear"); // Mac용 system("cls")
				string change;
				//???? ?????? ????????? ??????? ????? ?????
				cout << "게시글을 수정하시겠습니까? (Y/y or N/n)" << endl;
				cin >> change;
				cin.ignore();

				// else
				// {                                                              //게시글 삭제 가능
				//     postinfo.open(_postname, ios::in | ios::out | ios::trunc); //게시글 데이터파일 내용 전부 삭제
				//     postinfo.close();
				//     cout << "게시글 삭제" << endl;
				Sleep(1000);
				// sleep(1);
			//     break; //게시글목록으로 이동
			// }
				if (change == "Y" || change == "y")
				{
					if (com_num != 0)
					{
						cout << "댓글이 한 개 이상 존재합니다" << endl;
						// sleep(1);
					}
					else
					{
						while (1)
						{
							system("cls");
							// system("clear");
							cout << "제목 : ";
							string title;
							// cin.ignore(); // 개행문자(Enter) 입력을 막기위해서 넣어준 메쏘드
							// getline(cin, title);
							string s1;
							while (1)
							{
								//cin.ignore();
								getline(cin, s1);
								if (s1.find('\t') == string::npos)
								{
									title = title + s1 + '\n';
								}
								else
								{
									int index = s1.find('\t');
									for (int i = 0; i < index; i++)
									{
										title = title + s1.at(i);
									}
									break;
								}
							}
							if (title.empty())
							{
								cout << "잘못된 입력방식입니다" << endl;
								Sleep(1000);
								// sleep(1);
							}
							else if (title.size() == 1 && (title.compare("b") == 0 || title.compare("B") == 0))
							{
								break;
							}
							//(s.size() != s1.size()) ||
							else if (title.size() < 2 || title.size() > 35)
							{
								cout << "잘못된 입력방식입니다" << endl;
								Sleep(1000);
								// sleep(1);
							}
							//입력 검사요소를 모두 통과하였을때
							else
							{
								system("cls");
								// system("clear");
								cout << "본문 : ";
								// cin.ignore();
								string contents;
								// getline(cin, contents);
								string s2;
								while (1)
								{
									//cin.ignore();
									getline(cin, s2);
									if (s2.find('\t') == string::npos)
									{
										contents = contents + s2 + '\n';
									}
									else
									{
										int index = s2.find('\t');
										for (int i = 0; i < index; i++)
										{
											contents = contents + s2.at(i);
										}
										break;
									}
								}
								if (contents.empty())
								{
									cout << "잘못된 입력방식입니다" << endl;
									Sleep(1000);
									// sleep(1);
								}
								else if (contents.size() == 1 && (contents.compare("b") == 0 || contents.compare("B") == 0))
								{
									break;
								}
								else if (contents.size() < 2 || contents.size() > 300)
								{
									cout << "잘못된 입력방식입니다" << endl;
									Sleep(1000);
									// sleep(1);
								}
								else
								{
									//파일열어서 수정해야댐
									string modify;
									cout << "게시글 수정을 완료하시겠습니까?" << endl;
									cin >> modify;
									if (modify == "Y" || modify == "y")
									{
										fstream post_content;
										post_content.open(_postname, ios::out);
										data[3] = title;
										data[4] = contents;
										for (int j = 0; j < 7; j++)
										{
											post_content << data[j];
											post_content.put('\t');
										}
										for (int i = 7; i < data.size(); i++)
										{
											post_content << data[i];
											post_content.put('\t');
										}
										post_content.close();
										break;
									}
									else if (modify == "N" || modify == "n")
									{
										break;
									}
									else
									{
										cout << "잘못된 입력방식입니다" << endl;
										Sleep(1000);
										// sleep(1);
									}
								}
							}
						}
					}
				}
				else if (change == "N" || change == "n")
				{
				}
				else
				{
					cout << "잘못된 입력방식입니다" << endl;
					Sleep(1000);
					// sleep(1);
				}
			}
			else
			{
				cout << "사용자가 일치하지 않습니다" << endl;
				Sleep(1000);
				// sleep(1);
			}
		}
		else if (command == "5")
		{ //댓글 삭제 - user_id 부분 일치
			cout << "댓글 번호를 입력해주세요." << endl;
			string com;
			cin >> com;
			int num = stoi(com);
			if (_userid == data[7 + 2 * (num - 1)] || _userid == "manager")
			{
				fstream post_content;
				data.erase(data.begin() + (7 + 2 * (num - 1)));
				data.erase(data.begin() + (7 + 2 * (num - 1)));

				post_content.open(_postname, ios::out);
				for (int j = 0; j < 7; j++)
				{
					post_content << data[j];
					post_content.put('\t');
				}
				for (int i = 7; i < data.size(); i++)
				{
					post_content << data[i];
					post_content.put('\t');
				}
				post_content.close();
			}
			else
			{
				cout << "잘못된 입력입니다." << endl;
				Sleep(1000);
				// sleep(1);
			}
		}
		else if (command == "6")
		{ //게시글 삭제 - user_id 부분 일치 , 댓글 하나 이상 존재할 경우 삭제 x
			if (_userid == "manager")
			{
				postinfo.open(_postname, ios::in | ios::out | ios::trunc); //게시글 데이터파일 내용 전부 삭제
				postinfo.close();
				cout << "게시글 삭제" << endl;
				Sleep(1000);
				// sleep(1);
				break; //게시글목록으로 이동
			}
			if (_userid == data[1])
			{
				if (com_num != 0)
				{
					cout << "댓글이 한 개 이상 존재합니다" << endl;
					Sleep(1000);
					// sleep(1);
				}
				else
				{                                                              //게시글 삭제 가능
					//postinfo.open(_postname, ios::in | ios::out | ios::trunc); //게시글 데이터파일 내용 전부 삭제
					//postinfo.close();
					char pathname[10];
					strcpy(pathname, _postname.c_str());
					remove(pathname);

					size_t pos = _filename.rfind('/');
					string category_name = _filename.substr(0, pos);
					//cout << category_name << endl;
					string dataSetpath = "./data/" + category_name;
					string path = dataSetpath + "/*";
					intptr_t handle;
					struct _finddata_t fd;

					if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
						cout << "no file in directory" << endl;

					int i = 0;
					string oldname;
					string newname;

					do {
						if (i > 1) {
							oldname = dataSetpath + "/" + fd.name;
							newname = dataSetpath + "/" + to_string(i - 1) + ".txt";
							rename(oldname.c_str(), newname.c_str());
							//cout << "변경" << endl;
						}
						i++;
					} while (_findnext(handle, &fd) == 0);
					//cout << i << endl;
					_findclose(handle);


					cout << "게시글 삭제" << endl;
					Sleep(1000);
					// sleep(1);
					break; //게시글목록으로 이동
				}
			}
			else
			{
				cout << "작성자가 아닙니다." << endl;
				Sleep(1000);
				// sleep(1);
			}
		}
		else if (command == "7") {
			if (_userid != "manager") {
				cout << "잘못된 입력입니다. " << endl;
				Sleep(1000);
			}
			else {
				Board b;
				b.change_Category(_postname, _userid);
				cout << "카테고리 변경이 완료되었습니다.....";
				Sleep(1000);
				
				b.selectCategory(_userid);
				break;
			}
		}

		else if (command == "B" || command == "b")
		{
			//?????????? ??????
			
			string _goMain = "./data/";
			_goMain += _filename;
			string sub_goMain = _goMain.substr(0, 13);
			Board b;
			b.mainPost(_userid, sub_goMain, 0);
			
			break;
		}
		else
		{
			cout << "잘못된 입력입니다." << endl;
			Sleep(1000);
			// sleep(1);
		}
	}
}

//void boardPost::change_Category(string _postname, string _userid) {
//	system("cls");
//	Board b;
//	string post_location = _postname; //.txt 까지의 경로
//
//	ifstream want_2_move(post_location);
//	string move_date;
//	getline(want_2_move, move_date);
//	vector<string> m_date;
//	stringstream md1(move_date);
//	while (getline(md1, move_date, '\t')) {
//		m_date.push_back(move_date);
//	}
//	m_date[2].erase(remove(m_date[2].begin(), m_date[2].end(), '-'), m_date[2].end());
//	double move = stod(m_date[2]);
//
//	int i = post_location.length() - 1;
//	while (post_location[i] != '/') {
//		i--;
//	}
//	string location = "";
//	for (int j = 0; j < i; j++) {
//		location += post_location[j]; //post_n까지의 경로
//	}
//	
//	int file_num = b.numFile(location); // 파일 갯수
//	string filename = "./data/manager_category.txt";
//	int numline = b.lineFile(filename);
//	ifstream openpost(filename);
//	vector<string> nameOfCategory;
//	cout << "============================" << endl;
//	cout << endl;
//	cout << "      카테고리 선택" << endl;
//	cout << endl;
//	for (int i = 1; i < numline; i++) {
//		string line;
//		getline(openpost, line);
//		stringstream ss(line);
//
//		vector<string> data;
//
//		while (getline(ss, line, '	')) {
//			data.push_back(line);
//		}
//		cout << "      " << i << "." << data[1] << " 게시판" << endl;
//		nameOfCategory.push_back(data[1]);
//		cout << endl;
//	}
//	cout << endl;
//	cout << "      0. 이전 화면으로 / ";
//	cout << endl;
//	cout << "===========================" << endl;
//
//	string _select;
//	cout << endl;
//	cout << "이동할 게시판을 선택해주세요. (0~";
//	cout << numline - 1 << ") : " << endl;
//	cin >> _select;
//	bool out = true;
//	int sel = stoi(_select);
//	int num_folder1 = b.numFile(_select); // 이동할 게시판 파일 수
//	//if (sel > 0 && sel < numline && num_folder1 == 0) {
//	//	string _category = "./data/post_"; // 이동할 게시판
//	//	_category += _select;
//	//	_category += "/1.txt";
//
//	//	cout << _postname << endl;
//	//	cout << _category << endl;
//
//	//	fs::path org_path = _postname;
//	//	fs::path ch_path = _category;
//
//	//	fs::copy_file(org_path, ch_path);
//	//	fs::remove_all(org_path);
//	//}
//	if (sel > 0 && sel < numline) {
//		while (out != false) {
//			string _category = "./data/post_"; // 이동할 게시판
//			_category += _select;
//
//			_category += "/";
//			_category += to_string(num_folder1);
//
//
//			ifstream loc_2_move(post_location);
//			string loc_date;
//			getline(loc_2_move, loc_date);
//			vector<string> l_date;
//			stringstream md2(loc_date);
//			while (getline(md2, loc_date, '\t')) {
//				l_date.push_back(loc_date);
//			}
//			l_date[2].erase(remove(l_date[2].begin(), l_date[2].end(), '-'), l_date[2].end());
//			string loc_d = l_date[2];
//			double loc = stod(loc_d);
//
//			// loc : 200 201 202 204
//			// move : 203
//
//			cout << loc << endl;
//			cout << move << endl;
//			cout << endl;
//
//			if (loc > move) {
//				string o_cat = _category + to_string(num_folder1);
//				_category += to_string(num_folder1+1);
//				fs::path o_path = _postname;
//				fs::path back_path = _category;
//				fs::copy_file(o_path, back_path);
//				fs::remove(o_path);
//				num_folder1--;
//			}
//			else {
//				cout << num_folder1 << endl;
//				_category += to_string(num_folder1);
//				fs::path origin_path = _postname;
//				fs::path _new_path = _category;
//				cout << origin_path << endl;
//				cout << _new_path << endl;
//				fs::copy_file(origin_path, _new_path);
//				fs::remove(origin_path);
//				out = false;
//			}
//		}
//		
//	}
//	else if (_select == "0") {
//		return;
//	}
//	else {
//		cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... ";
//		Sleep(1000);
//		change_Category(_postname, _userid);
//	}
//}

//int main(void)
// {
//     boardPost b;
////     //    string _postname = "post_1/1.txt";
//     string _postname = "post_1/1.txt";
//     string _userid = "aaaa";
//     b.Post(_postname, _userid);
// }

