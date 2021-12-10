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
	cout << "      카테고리 선택" << endl;
	cout << endl;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " 게시판" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}
	cout << endl;
	cout << "      0. 이전 화면으로 / ";
	if (_userid == "manager") {
		cout << "카테고리 관리(M / m)" << endl;
	}
	cout << endl;
	cout << "===========================" << endl;

	string _select;
	cout << endl;
	cout << "게시판을 선택해주세요. (0~";
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
			cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... ";
			Sleep(1000);
			selectCategory(_userid);
		}
	}
	else {
		cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... ";
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
		cout << "글을 작성하여 첫 포스트를 남겨주세요!" << endl;
	}
	else {
		for (int i = 0; i < 10; i++) {
			// 파일명은 자연수만 가능 (0이하로는 금지)
			if (_getFile == 0) {
				break;
			}
			// 파일명은 파일 최대 갯수를 넘을 수 없음.
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
				cout << i << ". " << "신고가 많은 글입니다." << endl;
				cout << "	- 글을 보시려면 " << i << "번을 입력해주세요." << endl;
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
	cout << "W/w. 게시글 작성" << endl;
	if (_cntFile % 10 == 0) {
		if ((_cntFile - (_getFile + 1)) / 10 + 1 < (_cntFile / 10)) {
			cout << "F/f. 다음 페이지로" << endl;
		}
	}
	else {
		if ((_cntFile - (_getFile + 1)) / 10 + 1 < (_cntFile / 10 + 1)) {
			cout << "F/f. 다음 페이지로" << endl;
		}
	}

	if ((_cntFile - (_getFile + 1)) / 10 + 1 <= 1) {
		cout << "B/b. 카테고리 선택" << endl;
	}
	else {
		cout << "B/b. 이전 페이지로" << endl;
	}
	string select;
	cout << "입력 : ";
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
			cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... ";
			Sleep(1000);
			_getFile = _cntFile % 10;
			mainPost(_userid, _category, _getFile);
		}
		else {
			int _postnum = _cntFile - ((_cntFile - (_getFile + 1)) / 10) * 10 - _select; // 넘겨줄 파일 번호
			string _pn = to_string(_postnum);
			string subCategory = _category.substr(7, _category.size() - 1);
			string dir = subCategory + "/" + _pn + ".txt";

			boardPost bP;
			bP.Post(dir, _userid);
		}
	}
	else {
		cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... ";
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

	cout << "제목 : ";
	cin.ignore();
	getline(cin, _title);
	if (_title == "B" || _title == "b") {
		mainPost(_userid, _category, 0);
		return;
	}
	if (_title.size() < 2 || _title.size() > 35) {
		cout << "제목의 길이는 2자 이상 35자 이하 입니다.";
		Sleep(1000);
		createPost(_userid, _category, _befPostnum);
	}
	else {
		cout << "=========================================";
		cout << endl;
		cout << "본문 : ";
		getline(cin, _content);
		if (_content == "B" || _content == "b") {
			mainPost(_userid, _category, 0);
			return;
		}
		else if (_content.size() < 2 || _content.size() > 300) {
			cout << "본문의 길이는 2자 이상 300자 이하 입니다.";
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

				// 파일 내용 작성 (파일번호/유저아이디/포매팅된날짜/제목/본문)
				// 추천수나 신고수는 추후에 다른 함수에서 추가해주기
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
				cerr << "정보를 불러오는데에 실패하였습니다." << endl;
			}

			string _post = "";


			for (int i = 0; i < total.size(); i++) {
				_post += total[i];
			}

			savepost << _post;
			savepost.close();


			// 파일 작성이 끝나면 갱신된 파라미터로 다시 mainPost 함수 호출
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

	/* regex 예외처리 부분은 나중에 */

	return false;
}

void Board::managerCategory(string user_id) {
	system("cls");
	cout << "============================" << endl;
	cout << endl;
	cout << "      카테고리 관리" << endl;
	cout << endl;
	cout << "      1. 카테고리 이름변경" << endl;
	cout << endl;
	cout << "      2. 카테고리 추가" << endl;
	cout << endl;
	cout << "      3. 카테고리 병합" << endl;
	cout << endl;
	cout << "      4. 카테고리 삭제" << endl;
	cout << endl;
	cout << endl;
	cout << "      이전 화면으로 (B/b)" << endl;
	cout << endl;
	cout << "===========================" << endl;

	string _select;
	cout << endl;
	cout << "관리 모드를 선택해주세요. : " << endl;
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
		cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... " << endl;
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
	cout << "      바꿀 카테고리" << endl;
	cout << endl;

	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " 게시판" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}

	cout << "============================" << endl;
	int selectCategory;
	cout << endl;
	cout << "변경할 카테고리를 선택해주세요.(최대 " << numline - 1 << "까지) : ";
	cin >> selectCategory;
	if (selectCategory < 1 && selectCategory > numline - 1) {
		cout << "잘못 입력하셨습니다." << endl;
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
	cout << "	변경할 이름을 입력해주세요." << endl;
	cout << "	";
	cin >> _changeName;
	if (_changeName == "B" || _changeName == "b") {
		managerCategory(user_id);
	}
	else if (_changeName.length() >= 2 && _changeName.length() <= 10) {
		for (int i = 0; i < name.size(); i++) {
			if (_changeName == name[i] && i != selectCategory - 1) {
				cout << "중복되는 이름이 있습니다.";
				changeName(user_id, selectCategory, name);
			}
			else {
				string check;
				cout << "변경하시겠습니까? (Y/y) or (N/n)";
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
					cout << "변경하였습니다." << endl;
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
	cout << "        카테고리 추가        " << endl;
	cout << endl;
	cout << "=============================" << endl;
	cin >> _newCategoryName;

	if (_newCategoryName == "B" || _newCategoryName == "b") {
		managerCategory(user_id);
	}
	else if (_newCategoryName.length() < 2 || _newCategoryName.length() > 10) {
		cout << "카테고리 이름은 2자리에서 10자리 사이의 길이여야만 합니다." << endl;
		addCategory(user_id);
	}
	else {
		for (int i = 0; i < nameOfCategory.size(); i++) {
			if (_newCategoryName == nameOfCategory[i]) {
				cout << "이미 존재하는 카테고리 이름입니다." << endl;
				addCategory(user_id);
			}
			else {
				// 제대로 카테고리가 생성되는 로직
				string check;
				cout << "추가하시겠습니까? (Y/y) or (N/n)";
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

					cout << "새로운 카테고리가 추가되었습니다." << endl;
					managerCategory(user_id);
					break;
				}
				else {
					cout << "취소하였습니다." << endl;
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
	cout << "      바꿀 카테고리" << endl;
	cout << endl;

	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " 게시판" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}

	cout << "============================" << endl;
	int _merge1; // 병합할 폴더1
	int _merge2; // 병합할 폴더2

	cout << endl;
	cout << "합칠 카테고리를 선택해주세요.(2개) : ";
	cin >> _merge1;
	cin >> _merge2;

	if (_merge1 >= numline || _merge1 < 1 || _merge2 >= numline || _merge2 < 1) {
		cout << "잘못된 입력입니다." << endl;
		Sleep(1000);
		openpost.close();
		mergeCategory(user_id);
	}
	else {
		openpost.close();
		mergingFolders(to_string(_merge1), to_string(_merge2));
		cout << "카테고리 병합에 성공하였습니다." << endl;
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
	
	// 덜 이동된 것 Merge
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

	// path2 폴더 삭제
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

	//manager_Category 재배치
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

	// 뒷정리
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
	cout << "            카테고리 삭제            " << endl;
	cout << endl;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " 게시판" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "=====================================" << endl;
	cout << endl;
	cout << " 삭제할 게시판의 번호를 입력해주세요." << endl;
	cout << endl;
	cout << "          (b/B : 뒤로가기)           " << endl;
	cout << endl;
	cout << " 입력 : ";
	cout << endl;
	while (!(cin >> _deleteCategoryNum)) {

		cin.clear();

		cin.ignore(INT_MAX, '\n');

		cout << "삭제할 게시판의 번호만 입력해주세요." << endl;

		Sleep(1000);
	}

	if (_deleteCategoryNum < 1 || _deleteCategoryNum > nameOfCategory.size()) {
		cout << "존재하지 않는 게시판입니다." << endl;
		deleteCategory(user_id);
	}
	else {
		// 카테고리를 삭제하는 로직
		string check;
		cout << "정말 삭제하시겠습니까? (Y/y) or (N/n)";
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

			//cout << "내 현재 경로 : " << fs::current_path() << endl;
			
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
			cout << "게시판이 삭제되었습니다." << endl;
			managerCategory(user_id);
		}
		else if (check == "N" || check == "n") {
			cout << "취소하였습니다." << endl;
			managerCategory(user_id);
		}
		else {
			cout << "올바른 값을 입력해주세요." << endl;
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
	string post_location = _postname; //.txt 까지의 경로
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
		location += post_location[j]; //post_n까지의 경로
	}
	want_2_move.close();

	int file_num = numFile(location); // 파일 갯수
	string filename = "./data/manager_category.txt";
	int numline = lineFile(filename);
	ifstream openpost(filename);
	vector<string> nameOfCategory;
	cout << "============================" << endl;
	cout << endl;
	cout << "      카테고리 선택" << endl;
	cout << endl;
	for (int i = 1; i < numline; i++) {
		string line;
		getline(openpost, line);
		stringstream ss(line);

		vector<string> data;

		while (getline(ss, line, '	')) {
			data.push_back(line);
		}
		cout << "      " << i << "." << data[1] << " 게시판" << endl;
		nameOfCategory.push_back(data[1]);
		cout << endl;
	}
	cout << endl;
	cout << "      0. 이전 화면으로 / ";
	cout << endl;
	cout << "===========================" << endl;

	string _select;
	cout << endl;
	cout << "이동할 게시판을 선택해주세요. (0~";
	cout << numline - 1 << ") : " << endl;
	cin >> _select;
	bool out = true;
	int sel = stoi(_select);
	string move_to = "./data/post_";
	move_to += _select;
	int num_folder1 = numFile(move_to); // 이동할 게시판 파일 수
	openpost.close();
	int _cat_num = numFile(location);
	fs::path o_path = "";
	fs::path origin_path = "";
	string _cat;

	if (sel > 0 && sel < numline) {
		if (num_folder1 == 0) {
			string _category = "./data/post_"; // 이동할 게시판
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
				string _category = "./data/post_"; // 이동할 게시판
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
		cout << "입력 형식이 맞지 않습니다. 다시 입력해주세요... ";
		Sleep(1000);
		change_Category(_postname, _userid);
	}
}