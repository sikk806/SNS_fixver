#include "board.h"
using namespace std;

Board::Board() {

}

Board::~Board() {

}

void Board::setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void Board::selectCategory(string _userid) {
	system("cls");
	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;
	cout << "============================" << endl;
	cout << endl;
	cout << "      ī�װ� ����" << endl;
	cout << endl;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " �Խ���" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}
	cout << endl;
	cout << "      0. ���� ȭ������ / ";
	if (_userid == "manager") {
		cout << "ī�װ� ����(M / m)" << endl;
	}
	cout << endl;
	cout << "===========================" << endl;

	string _select;
	cout << endl;
	cout << "�Խ����� �������ּ���. (0~";
	cout << numline - 1 << ") : " << endl;
	cin >> _select;

	int sel = stoi(_select);
	if(sel > 0 && sel < numline){
	
		string _category = "./data/post_";
		_category += _select;

		mainPost(_userid, _category, 0);
	}
	else if (_select == "0") {
		return;
	}
	else if (_select == "M" || _select == "m") {
		if (_userid == "manager") {
			managerCategory(_userid);
		}
		else {
			cout << "�Է� ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���... ";
			Sleep(1000);
			selectCategory(_userid);
		}
	}
	else {
		cout << "�Է� ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���... ";
		Sleep(1000);
		selectCategory(_userid);
	}

}

void Board::mainPost(string _userid, string _category, int _getFile) {
	//system("clear"); // Mac command
	system("cls"); // Windows.h
	int _cntFile = numFile(_category);
	if (_getFile == 0) {
		_getFile = _cntFile;
	}

	if (_cntFile == 0) {
		cout << "���� �ۼ��Ͽ� ù ����Ʈ�� �����ּ���!" << endl;
	}
	else {
		for (int i = 0; i < 10; i++) {
			// ���ϸ��� �ڿ����� ���� (0���Ϸδ� ����)
			if (_getFile == 0) {
				break;
			}
			// ���ϸ��� ���� �ִ� ������ ���� �� ����.
			else if (_getFile > _cntFile) {
				break;
			}
			string _fname = to_string(_getFile);
			string _filename = _category + "/" + _fname + ".txt";

			ifstream openpost(_filename);

			string line;
			getline(openpost, line);
			stringstream ss(line);

			vector<string> data;

			while (getline(ss, line, '	')) {
				data.push_back(line);
			}
			if (stoi(data[5]) > 10 && (stoi(data[6]) / stoi(data[5])) < 1) {
				cout << i << ". " << "�Ű� ���� ���Դϴ�." << endl;
				cout << "	- ���� ���÷��� " << i << "���� �Է����ּ���." << endl;
			}
			else {
				cout << i << ". " << data[3] << endl;

				if (data[4].length() > 20) {
					string _substring = data[4].substr(0, 20);
					cout << "	- " << _substring << "..." << endl;
				}
				else {
					cout << "	- " << data[4] << endl;
				}
			}
			_getFile--;

			openpost.close();
		}
	}
	if (_cntFile % 10 == 0) {
		cout << "Page. " << (_cntFile - (_getFile + 1)) / 10 + 1 << "/" << (_cntFile / 10) << endl;
	}
	else {
		cout << "Page. " << (_cntFile - (_getFile + 1)) / 10 + 1 << "/" << (_cntFile / 10 + 1) << endl;
	}
	cout << "W/w. �Խñ� �ۼ�" << endl;
	if (_cntFile % 10 == 0) {
		if ((_cntFile - (_getFile + 1)) / 10 + 1 < (_cntFile / 10)) {
			cout << "F/f. ���� ��������" << endl;
		}
	}
	else {
		if ((_cntFile - (_getFile + 1)) / 10 + 1 < (_cntFile / 10 + 1)) {
			cout << "F/f. ���� ��������" << endl;
		}
	}

	if ((_cntFile - (_getFile + 1)) / 10 + 1 <= 1) {
		cout << "B/b. ī�װ� ����" << endl;
	}
	else {
		cout << "B/b. ���� ��������" << endl;
	}
	string select;
	cout << "�Է� : ";
	cin >> select;
	if (select == "B" || select == "b") {
		if ((_cntFile - _getFile - 1) / 10 < 1) {
			selectCategory(_userid);
		}
		else {
			if ((_cntFile - (_getFile + 1)) / 10 + 1 == (_cntFile / 10 + 1)) {
				_getFile += _cntFile % 10;
			}
			_getFile += 10;
			mainPost(_userid, _category, _getFile);
		}

	}
	else if (select == "F" || select == "f" && _cntFile > 10) {
		mainPost(_userid, _category, _getFile);
	}
	else if (select == "W" || select == "w") {
		createPost(_userid, _category, _cntFile);
	}

	else if (select == "0" || select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "6" || select == "7" || select == "8" || select == "9") {
		int _select = stoi(select);
		if ((_cntFile - (_getFile + 1)) / 10 + 1 == (_cntFile / 10 + 1) && _select >= _cntFile % 10) {
			cout << "�Է� ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���... ";
			Sleep(1000);
			_getFile = _cntFile % 10;
			mainPost(_userid, _category, _getFile);
		}
		else {
			int _postnum = _cntFile - ((_cntFile - (_getFile + 1)) / 10) * 10 - _select; // �Ѱ��� ���� ��ȣ
			string _pn = to_string(_postnum);
			string subCategory = _category.substr(7, _category.size() - 1);
			string dir = subCategory + "/" + _pn + ".txt";

			boardPost bP;
			bP.Post(dir, _userid);
		}
	}
	else {
		cout << "�Է� ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���... ";
		Sleep(1000);
		if ((_cntFile - (_getFile + 1)) / 10 + 1 == (_cntFile / 10 + 1)) {
			_getFile = _cntFile % 10;
		}
		else {
			_getFile += 10;
		}
		mainPost(_userid, _category, _getFile);
	}
}

void Board::createPost(string _userid, string _category, int _postnum) {
	//system("clear"); // Mac command
	system("cls"); // Windows.h

	string _title = " ";
	string _content = "";
	string _path;
	int _befPostnum = _postnum;
	string _currentnum = to_string(++_postnum);

	vector<string> total;

	cout << "���� : ";
	cin.ignore();
	getline(cin, _title);
	if (_title == "B" || _title == "b") {
		mainPost(_userid, _category, 0);
		return;
	}
	if (_title.size() < 2 || _title.size() > 35) {
		cout << "������ ���̴� 2�� �̻� 35�� ���� �Դϴ�.";
		Sleep(1000);
		createPost(_userid, _category, _befPostnum);
	}
	else {
		cout << "=========================================";
		cout << endl;
		cout << "���� : ";
		getline(cin, _content);
		if (_content == "B" || _content == "b") {
			mainPost(_userid, _category, 0);
			return;
		}
		else if (_content.size() < 2 || _content.size() > 300) {
			cout << "������ ���̴� 2�� �̻� 300�� ���� �Դϴ�.";
			Sleep(1000);
			createPost(_userid, _category, _befPostnum);
		}
		else {


			_path += _category + "/" + _currentnum + ".txt";

			ofstream savepost(_path);

			if (savepost.is_open()) {
				time_t rawtime;
				tm* timeinfo;
				char buffer[80];

				time(&rawtime);
				timeinfo = localtime(&rawtime);

				strftime(buffer, 80, "%Y-%m-%d-%H-%M", timeinfo);
				puts(buffer);

				string _datetime(buffer);

				// ���� ���� �ۼ� (���Ϲ�ȣ/�������̵�/�����õȳ�¥/����/����)
				// ��õ���� �Ű���� ���Ŀ� �ٸ� �Լ����� �߰����ֱ�
				total.push_back(_currentnum);
				total.push_back("	");
				total.push_back(_userid);
				total.push_back("	");
				total.push_back(_datetime);
				total.push_back("	");
				total.push_back(_title);
				total.push_back("	");
				total.push_back(_content);
				total.push_back("	0	0	");
			}
			else {
				cerr << "������ �ҷ����µ��� �����Ͽ����ϴ�." << endl;
			}

			string _post = "";


			for (int i = 0; i < total.size(); i++) {
				_post += total[i];
			}

			savepost << _post;
			savepost.close();


			// ���� �ۼ��� ������ ���ŵ� �Ķ���ͷ� �ٽ� mainPost �Լ� ȣ��
			mainPost(_userid, _category, _postnum);
		}
	}

}

int Board::numFile(string _category) {
	int _cnt = 0;

	CFileFind finder;
	CString _foldername = _category.c_str();

	BOOL _existfolder = finder.FindFile(_foldername + "/*.*");

	while (_existfolder) {
		_existfolder = finder.FindNextFile();
		if (finder.IsDots()) {
			continue;
		}
		_cnt++;

	}

	finder.Close();

	return _cnt;
}

bool Board::checkWords(string _words)
{
	string words = _words;

	/* regex ����ó�� �κ��� ���߿� */

	return false;
}

void Board::managerCategory(string user_id) {
	system("cls");
	cout << "============================" << endl;
	cout << endl;
	cout << "      ī�װ� ����" << endl;
	cout << endl;
	cout << "      1. ī�װ� �̸�����" << endl;
	cout << endl;
	cout << "      2. ī�װ� �߰�" << endl;
	cout << endl;
	cout << "      3. ī�װ� ����" << endl;
	cout << endl;
	cout << "      4. ī�װ� ����" << endl;
	cout << endl;
	cout << endl;
	cout << "      ���� ȭ������ (B/b)" << endl;
	cout << endl;
	cout << "===========================" << endl;

	string _select;
	cout << endl;
	cout << "���� ��带 �������ּ���. : " << endl;
	cin >> _select;

	if (_select == "1") {
		changeCategoryName(user_id);
	}
	else if (_select == "2") {
		addCategory(user_id);
	}
	else if (_select == "3") {
		mergeCategory(user_id);
	}
	else if (_select == "4") {
		deleteCategory(user_id);
	}
	else if (_select == "B" || _select == "b") {
		selectCategory(user_id);
	}
	else {
		cout << "�Է� ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���... " << endl;
		Sleep(1000);
		managerCategory(user_id);
	}

}

void Board::changeCategoryName(string user_id) {
	system("cls");
	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;
	cout << "============================" << endl;
	cout << endl;
	cout << "      �ٲ� ī�װ�" << endl;
	cout << endl;

	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " �Խ���" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}

	cout << "============================" << endl;
	int selectCategory;
	cout << endl;
	cout << "������ ī�װ��� �������ּ���.(�ִ� " << numline - 1 << "����) : ";
	cin >> selectCategory;
	if (selectCategory < 1 && selectCategory > numline - 1) {
		cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
		Sleep(1000);
		openpost.close();
		changeCategoryName(user_id);
	}
	else {
		openpost.close();
		changeName(user_id, selectCategory, nameOfCategory);
	}
}

void Board::changeName(string user_id, int selectCategory, vector<string>& name) {
	system("cls");
	string _changeName;
	cout << "============================" << endl;
	cout << endl;
	cout << "	������ �̸��� �Է����ּ���." << endl;
	cout << "	";
	cin >> _changeName;
	if (_changeName == "B" || _changeName == "b") {
		managerCategory(user_id);
	}
	else if (_changeName.length() >= 2 && _changeName.length() <= 10) {
		for (int i = 0; i < name.size(); i++) {
			if (_changeName == name[i] && i != selectCategory - 1) {
				cout << "�ߺ��Ǵ� �̸��� �ֽ��ϴ�.";
				changeName(user_id, selectCategory, name);
			}
			else {
				string check;
				cout << "�����Ͻðڽ��ϱ�? (Y/y) or (N/n)";
				cin >> check;
				if (check == "Y" || check == "y") {
					name[selectCategory - 1] = _changeName;
					string filename = "./data/manager_category.txt";
					ofstream openpost(filename);
					vector<string> reset;
					for (int i = 0; i < name.size(); i++) {
						string resetName = "";
						resetName += "post_";
						resetName += to_string(i + 1);
						resetName += "	";
						resetName += name[i];
						Sleep(1000);
						openpost << resetName << endl;

					}
					cout << "�����Ͽ����ϴ�." << endl;
					managerCategory(user_id);
					break;
				}
			}
		}
	}
}

void Board::addCategory(string user_id) {

	system("cls");

	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;

	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		nameOfCategory.push_back(data[1]);
	}

	string _newCategoryName;
	cout << "=============================" << endl;
	cout << endl;
	cout << "        ī�װ� �߰�        " << endl;
	cout << endl;
	cout << "=============================" << endl;
	cin >> _newCategoryName;

	if (_newCategoryName == "B" || _newCategoryName == "b") {
		managerCategory(user_id);
	}
	else if (_newCategoryName.length() < 2 || _newCategoryName.length() > 10) {
		cout << "ī�װ� �̸��� 2�ڸ����� 10�ڸ� ������ ���̿��߸� �մϴ�." << endl;
		addCategory(user_id);
	}
	else {
		for (int i = 0; i < nameOfCategory.size(); i++) {
			if (_newCategoryName == nameOfCategory[i]) {
				cout << "�̹� �����ϴ� ī�װ� �̸��Դϴ�." << endl;
				addCategory(user_id);
			}
			else {
				// ����� ī�װ��� �����Ǵ� ����
				string check;
				cout << "�߰��Ͻðڽ��ϱ�? (Y/y) or (N/n)";
				cin >> check;
				if (check == "Y" || check == "y") {
					nameOfCategory.push_back(_newCategoryName);
					string filename = "./data/manager_category.txt";
					ofstream openpost(filename);
					vector<string> reset;
					for (int i = 0; i < nameOfCategory.size(); i++) {
						string resetName = "";
						resetName += "post_";
						resetName += to_string(i + 1);
						resetName += "	";
						resetName += nameOfCategory[i];
						Sleep(1000);
						openpost << resetName << endl;
					}

					cout << "���ο� ī�װ��� �߰��Ǿ����ϴ�." << endl;
					managerCategory(user_id);
					break;
				}
				else {
					cout << "����Ͽ����ϴ�." << endl;
					managerCategory(user_id);
					break;
				}
			}
		}
	}
}

void Board::mergeCategory(string user_id) {
	system("cls");
	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;
	cout << "============================" << endl;
	cout << endl;
	cout << "      �ٲ� ī�װ�" << endl;
	cout << endl;

	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " �Խ���" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}

	cout << "============================" << endl;
	int _merge1; // ������ ����1
	int _merge2; // ������ ����2

	cout << endl;
	cout << "��ĥ ī�װ��� �������ּ���.(2��) : ";
	cin >> _merge1;
	cin >> _merge2;

	if (_merge1 >= numline || _merge1 < 1 || _merge2 >= numline || _merge2 < 1) {
		cout << "�߸��� �Է��Դϴ�." << endl;
		Sleep(1000);
		openpost.close();
		mergeCategory(user_id);
	}
	else {
		openpost.close();
		mergingFolders(to_string(_merge1), to_string(_merge2));
		cout << "ī�װ� ���տ� �����Ͽ����ϴ�." << endl;
		Sleep(1000);
		managerCategory(user_id);
	}
}

void Board::mergingFolders(string _merge1, string _merge2) {
	if (stoi(_merge1) > stoi(_merge2)) {
		string tmp = _merge1;
		_merge1 = _merge2;
		_merge2 = tmp;
	}

	string str_merge1_path = "./data/post_";
	str_merge1_path += _merge1;
	str_merge1_path += "/";
	string str_merge2_path = "./data/post_";
	str_merge2_path += _merge2;
	str_merge2_path += "/";

	//fs::path _merge1_path = str_merge1_path;
	//fs::path _merge2_path = str_merge2_path;

	int numFile_merge1 = numFile(str_merge1_path);
	int numFile_merge2 = numFile(str_merge2_path);

	int name_merge1 = 1;
	int name_merge2 = 1;
	int cnt_file = 1;
	
	while (numFile_merge1+1 != name_merge1 && numFile_merge2+1 != name_merge2) {
		fs::path _new_path = "./data/merge_Category/";
		fs::path merge1_path = "./data/post_1/";
		_new_path += to_string(cnt_file);
		_new_path += ".txt";
		string merge1_filename = str_merge1_path;
		merge1_filename += to_string(name_merge1);
		merge1_filename += ".txt";
		string merge2_filename = str_merge2_path;
		merge2_filename += to_string(name_merge2);
		merge2_filename += ".txt";

		ifstream read_merge1(merge1_filename);
		string merge1_date;
		getline(read_merge1, merge1_date);
		vector<string> date1;
		stringstream md1(merge1_date);
		while (getline(md1, merge1_date, '	')) {
			date1.push_back(merge1_date);
		}

		ifstream read_merge2(merge2_filename);
		string merge2_date;
		getline(read_merge2, merge2_date);
		vector<string> date2;
		stringstream md2(merge2_date);
		while (getline(md2, merge2_date, '	')) {
			date2.push_back(merge2_date);
		}

		date1[2].erase(remove(date1[2].begin(), date1[2].end(), '-'), date1[2].end());
		date2[2].erase(remove(date2[2].begin(), date2[2].end(), '-'), date2[2].end());
		double comp_date1 = stod(date1[2]);
		double comp_date2 = stod(date2[2]);

		if (comp_date1 < comp_date2) {
			fs::path merge1_path = merge1_filename;
			cout << merge1_path << endl;
			fs::copy_file(merge1_path, _new_path);
			
			name_merge1++;
		}
		else {
			fs::path _merge2_path = merge2_filename;
			cout << _merge2_path << endl;
			fs::copy_file(_merge2_path, _new_path);
			
			name_merge2++;
		}
		cnt_file++;

		read_merge1.close();
		read_merge2.close();
	}
	
	// �� �̵��� �� Merge
	while (numFile_merge1 + 1 != name_merge1) {
		string merge1_filename = str_merge1_path;
		merge1_filename += to_string(name_merge1);
		merge1_filename += ".txt";
		fs::path merge1_path = merge1_filename;
		fs::path _new_path = "./data/merge_Category/";
		_new_path += to_string(cnt_file);
		_new_path += ".txt";

		fs::copy_file(merge1_path, _new_path);
		name_merge1++;
		cnt_file++;
	}

	while (numFile_merge2 + 1 != name_merge2) {
		string merge2_filename = str_merge2_path;
		merge2_filename += to_string(name_merge2);
		merge2_filename += ".txt";
		fs::path merge2_path = merge2_filename;
		fs::path _new_path = "./data/merge_Category/";
		_new_path += to_string(cnt_file);
		_new_path += ".txt";

		fs::copy_file(merge2_path, _new_path);
		name_merge2++;
		cnt_file++;
	}

	// path2 ���� ����
	string remove_path = "./data/post_";
	remove_path += _merge2;
	fs::remove_all(remove_path);
	string copy_path = "./data/post_";
	copy_path += _merge1;
	
	int mC_numFile = numFile("./data/merge_Category");
	while (mC_numFile != 0) {
		string remove_path = "./data/merge_Category/";
		remove_path += to_string(mC_numFile);
		remove_path += ".txt";
		fs::copy(remove_path, copy_path, fs::copy_options::overwrite_existing);
		mC_numFile--;
	}

	//manager_Category ���ġ
	ifstream openfile("./data/manager_category.txt");
	int numline = lineFile("./data/manager_category.txt");
	vector<string> nameOfCategory;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openfile, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}

	cout << nameOfCategory[1] << endl;
	openfile.close();
	ofstream writefile("./data/manager_category.txt");
	for (int i = 1; i <= nameOfCategory.size(); i++) {
		if (i < stoi(_merge2)) {
			string rewrite = "post_";
			rewrite += to_string(i);
			rewrite += "\t";
			rewrite += nameOfCategory[i - 1];
			writefile << rewrite << endl;
		}
		else if(i > stoi(_merge2)){
			string rewrite = "post_";
			rewrite += to_string(i-1);
			rewrite += "\t";
			rewrite += nameOfCategory[i - 1];
			writefile << rewrite << endl;
		}
	}

	int merge2 = stoi(_merge2);
	while (merge2 != numline-1) {
		string copypath = "./data/post_";
		copypath += to_string(merge2 + 1);
		string new_path = "./data/post_";
		new_path += to_string(merge2);

		fs::rename(copypath, new_path);
		merge2++;
	}

	// ������
	mC_numFile = numFile("./data/merge_Category");
	while (mC_numFile != 0) {
		string remove_path = "./data/merge_Category/";
		remove_path += to_string(mC_numFile);
		remove_path += ".txt";
		fs::remove(remove_path);
		mC_numFile--;
	}

}

void Board::deleteCategory(string user_id) {

	system("cls");
	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;
	int _deleteCategoryNum;

	fs::path _delete_dir_path = "./data/post_";

	cout << "=====================================" << endl;
	cout << endl;
	cout << "            ī�װ� ����            " << endl;
	cout << endl;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " �Խ���" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "=====================================" << endl;
	cout << endl;
	cout << " ������ �Խ����� ��ȣ�� �Է����ּ���." << endl;
	cout << endl;
	cout << "          (b/B : �ڷΰ���)           " << endl;
	cout << endl;
	cout << " �Է� : ";
	cout << endl;
	while (!(cin >> _deleteCategoryNum)) {

		cin.clear();

		cin.ignore(INT_MAX, '\n');

		cout << "������ �Խ����� ��ȣ�� �Է����ּ���." << endl;

		Sleep(1000);
	}

	if (_deleteCategoryNum < 1 || _deleteCategoryNum > nameOfCategory.size()) {
		cout << "�������� �ʴ� �Խ����Դϴ�." << endl;
		deleteCategory(user_id);
	}
	else {
		// ī�װ��� �����ϴ� ����
		string check;
		cout << "���� �����Ͻðڽ��ϱ�? (Y/y) or (N/n)";
		cin >> check;
		if (check == "Y" || check == "y") {
			_delete_dir_path += to_string(_deleteCategoryNum);
			fs::remove_all(_delete_dir_path);

			
			for (int i = _deleteCategoryNum + 1; i <= nameOfCategory.size(); i++) {
				//fs::path _base_dir_path("./data/post_" + to_string(i));
				string _base_dir_path = "./data/post_" + to_string(i);
				//fs::path _base_renamed_dir_path("./data/post_" + to_string(i - 1));
				string _base_renamed_dir_path = "./data/post_" + to_string(i - 1);
				try {
					fs::rename(_base_dir_path, _base_renamed_dir_path);
				}
				catch (exception& e) {
					cout << e.what() << endl;
				}
			}

			//cout << "�� ���� ��� : " << fs::current_path() << endl;
			
			nameOfCategory.erase(nameOfCategory.begin() + (_deleteCategoryNum - 1));
			string filename = "./data/manager_category.txt";
			ofstream openpost(filename);
			vector<string> reset;
			for (int i = 0; i < nameOfCategory.size(); i++) {
				string resetname = "";
				resetname += "post_";
				resetname += to_string(i + 1);
				resetname += "	";
				resetname += nameOfCategory[i];
				Sleep(1000);
				openpost << resetname << endl;
			}
			cout << "�Խ����� �����Ǿ����ϴ�." << endl;
			managerCategory(user_id);
		}
		else if (check == "N" || check == "n") {
			cout << "����Ͽ����ϴ�." << endl;
			managerCategory(user_id);
		}
		else {
			cout << "�ùٸ� ���� �Է����ּ���." << endl;
			Sleep(1000);
			deleteCategory(user_id);
		}
	}
}

int Board::lineFile(string _filename) {
	int _cnt = 0;

	ifstream openpost(_filename);

	while (!openpost.eof()) {
		string line;
		getline(openpost, line);
		_cnt++;
	}

	return _cnt;
}

void Board::change_Category(string _postname, string _userid) {
	system("cls");
	string post_location = _postname; //.txt ������ ���
	string txt_num = post_location;
	string N_txt = txt_num.substr(14, txt_num.size());
	int z = 0;
	txt_num = "";
	while (N_txt[z] != '.') {
		txt_num += N_txt[z];
		z++;
	}

	ifstream want_2_move(post_location);
	string move_date;
	getline(want_2_move, move_date);
	vector<string> m_date;
	stringstream md1(move_date);
	while (getline(md1, move_date, '\t')) {
		m_date.push_back(move_date);
	}
	m_date[2].erase(remove(m_date[2].begin(), m_date[2].end(), '-'), m_date[2].end());
	string date_m = m_date[2];
	double move = stod(date_m);

	int i = post_location.length() - 1;
	while (post_location[i] != '/') {
		i--;
	}
	string location = "";
	for (int j = 0; j < i; j++) {
		location += post_location[j]; //post_n������ ���
	}
	want_2_move.close();

	int file_num = numFile(location); // ���� ����
	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;
	cout << "============================" << endl;
	cout << endl;
	cout << "      ī�װ� ����" << endl;
	cout << endl;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " �Խ���" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}
	cout << endl;
	cout << "      0. ���� ȭ������ / ";
	cout << endl;
	cout << "===========================" << endl;

	string _select;
	cout << endl;
	cout << "�̵��� �Խ����� �������ּ���. (0~";
	cout << numline - 1 << ") : " << endl;
	cin >> _select;
	bool out = true;
	int sel = stoi(_select);
	string move_to = "./data/post_";
	move_to += _select;
	int num_folder1 = numFile(move_to); // �̵��� �Խ��� ���� ��
	openpost.close();
	int _cat_num = numFile(location);
	fs::path o_path = "";
	fs::path origin_path = "";
	string _cat;

	if (sel > 0 && sel < numline) {
		if (num_folder1 == 0) {
			string _category = "./data/post_"; // �̵��� �Խ���
			_category += _select;
			_category += "/1.txt";

			fs::path org_path = _postname;
			fs::path ch_path = _category;
			fs::copy_file(org_path, ch_path, fs::copy_options::overwrite_existing);
			for (int i = stoi(txt_num); i <= file_num; i++) {
				fs::path m_p = location;
				m_p += "/";
				m_p += to_string(i);
				m_p += ".txt";
				fs::path n_p = location;
				n_p += "/";
				n_p += to_string(i - 1);
				n_p += ".txt";
				fs::rename(m_p, n_p);
			}
		}
		else {
			while (out != false) {
				string _category = "./data/post_"; // �̵��� �Խ���
				_category += _select;

				_category += "/";
				_cat = _category;
				_category += to_string(num_folder1);
				_category += ".txt";


				ifstream loc_2_move(_category);
				string loc_date;
				getline(loc_2_move, loc_date);
				vector<string> l_date;
				stringstream md2(loc_date);
				while (getline(md2, loc_date, '\t')) {
					l_date.push_back(loc_date);
				}
				l_date[2].erase(remove(l_date[2].begin(), l_date[2].end(), '-'), l_date[2].end());
				string loc_d = l_date[2];
				double loc = stod(loc_d);
				loc_2_move.close();

				if (loc >= move) {
					string o_cat = _cat;
					o_cat += to_string(num_folder1 + 1);
					o_cat += ".txt";
					o_path = _category;
					fs::path back_path = o_cat;
					fs::copy_file(o_path, back_path, fs::copy_options::overwrite_existing);
					num_folder1--;
				}
				else {
					string n_cat = _cat;
					n_cat += to_string(num_folder1);
					n_cat += ".txt";
					string kk = _postname;
					origin_path = kk;
					fs::path _new_path = n_cat;
					fs::copy_file(origin_path, _new_path, fs::copy_options::overwrite_existing);
					out = false;
				}
				if (num_folder1 == 0) {
					out = false;
				}
			}
			fs::remove(origin_path);
			for (int i = stoi(txt_num)+1; i <= file_num; i++) {
				fs::path m_p = location;
				m_p += "/";
				m_p += to_string(i);
				m_p += ".txt";
				fs::path n_p = location;
				n_p += "/";
				n_p += to_string(i - 1);
				n_p += ".txt";
				fs::rename(m_p, n_p);
			}
		}

	}
	else if (_select == "0") {
		return;
	}
	else {
		cout << "�Է� ������ ���� �ʽ��ϴ�. �ٽ� �Է����ּ���... ";
		Sleep(1000);
		change_Category(_postname, _userid);
	}
}