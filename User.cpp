#include "User.h"
#include<conio.h>
#include<iomanip >
#include<Windows.h>


User::User() {
	name = "";
	password = "";
	phone = 0;
}

void __delay() {
	cout << endl;
	for (int i = 0; i < 300000000; i++)
		if (i % 100000000 == 0)cout << "\r即将跳转......." << 3 - i / 100000000;
	cout.clear();
	cin.sync();
}

int _pressKey1() {
	int key;
	do {
		key = _getch();
		_getch();
	} while (key != 89 && key != 78 && key != 110 && key != 121 && key !=27);
	return key;
}
template<typename pfunc>
void User::findSongAndPushBack(list<Song>&src, vector<list<Song>::iterator> &v, pfunc const &pf) {
	list<Song>::iterator it = src.begin();
	while (it != src.end()) {
		it = find_if(it, src.end(), pf);
		if (it != src.end()) { v.push_back(it); ++it; }
	}
}

void User::main_menu(list<Song>& src) {
	while (1) {
		system("cls");
		cout << endl << endl << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t|              <用户界面>               |" << endl;
		cout << "\t\t\t|             1 歌手点歌                |" << endl;
		cout << "\t\t\t|             2 歌曲搜索                |" << endl;
		cout << "\t\t\t|             3 拼音点歌                |" << endl;
		cout << "\t\t\t|             4 所有歌曲                |" << endl;
		cout << "\t\t\t|             5 已点歌曲                |" << endl;
		cout << "\t\t\t|             6   切歌                  |" << endl;
		cout << "\t\t\t|            ESC 退返主界面             |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t请选择 [ ]\b\b";
		int key;
		do {//确保键值正确
			key = _getch();
			_getch();
		} while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != 27);
		switch (key) {
		case '1':pickSongBySinger(src); break;
		case '2':if (pickSongBySongName(src) == -1)return; break;
		case '3':if (pickSongByAbbr(src) == -1)return; break;
		case '4':if (pickSongFromAll(src) == -1)return; break;
		case '5':showInQueue(); break;
		case '6':cutSong(); break;
		case 27:return;
		}
	}
}

bool _isNumber(char c) {
	if (c >= '0'&&c <= '9')return true;
	else return false;
}
bool _isBigCharacter(char c) {
	if (c >= 'A'&&c <= 'Z')return true;
	else return false;
}
bool _isSmallCharacter(char c) {
	if (c >= 'a'&&c <= 'z')return true;
	else return false;
}
bool _legalName(string name) {
	if (name.length() > 20)return false;
	else {
		for (int i = 0; i < name.length(); i++) {
			if (!(_isNumber(name[i]) || _isBigCharacter(name[i]) || _isSmallCharacter(name[i])))return false;
		}
		return true;
	}
}
bool _legalPassw(string passw) {
	if (passw.length() > 12)return false;
	else {
		bool flag1 = false, flag2 = false, flag3 = false;
		for (int i = 0; i < passw.length(); i++) {
			if (_isNumber(passw[i]))flag1 = true;
			else if (_isBigCharacter(passw[i]))flag2 = true;
			else if (_isSmallCharacter(passw[i]))flag3 = true;
		}
		return (flag1 && flag2 && flag3);
	}
}

User * User::sign_up()
{
	system("cls");
	User*p = new User;
	string temp;
	COORD name_pos, passw_pos1, passw_pos2, phone_pos;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                        用户注册                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         用户名："; GetConsoleScreenBufferInfo(hOut, &bInfo); name_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         确认密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         密保手机:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	SetConsoleCursorPosition(hOut, name_pos);
	cin >> temp;
	DWORD x;
	while (!_legalName(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 41, name_pos, &x);
		SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y });
		cout << "用户ID不超过20个字符，只能由大小写字母或数字组成,请重新输入" << endl;
		SetConsoleCursorPosition(hOut, name_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { name_pos.X + 41,name_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y }); cout << "√" << endl;
	p->name = temp;

	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	while (!_legalPassw(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 43, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 43,passw_pos1.Y });
		cout << "密码不超过12个字符，必须同时包括大小写字母和数字,请重新输入" << endl;
		SetConsoleCursorPosition(hOut, passw_pos1);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ',60, { passw_pos1.X + 43,passw_pos1.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos1.X + 43,passw_pos1.Y }); cout << "√" << endl;
	p->password = temp;

	SetConsoleCursorPosition(hOut, passw_pos2);
	cin >> temp;
	while (temp != p->password) {
		FillConsoleOutputCharacterA(hOut, ' ', 39, passw_pos2, &x);
		SetConsoleCursorPosition(hOut, { passw_pos2.X + 39,passw_pos2.Y });
		cout << "两次输入密码不一致" << endl;
		SetConsoleCursorPosition(hOut, passw_pos2);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ',19, { passw_pos2.X + 39,passw_pos2.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos2.X + 39,passw_pos2.Y }); cout << "√" << endl;
	SetConsoleCursorPosition(hOut, phone_pos);

	cin >> p->phone;
	SetConsoleCursorPosition(hOut, { phone_pos.X + 40,phone_pos.Y }); cout << "√" << endl;
	__delay();
	cin.ignore(1024, '\n');
	cin.clear();
	return p;
}

void User::resetPassword() {
	system("cls");
	string temp;
	COORD  passw_pos1, passw_pos2, phone_pos,end_pos;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                       重置密码                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         原密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         新密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         确认新密码:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl << endl;
	GetConsoleScreenBufferInfo(hOut, &bInfo);end_pos = bInfo.dwCursorPosition;
	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	DWORD x;
	while (temp != password) {
		FillConsoleOutputCharacterA(hOut, ' ', 44, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 44,passw_pos1.Y });
		cout << "× 密码错误  " << endl;
		SetConsoleCursorPosition(hOut, end_pos);
		cout << "是否重新输入(按y/n)" << endl;
		int key;
		do {
			key = _getch();
			_getch();
		} while (key != 'n' && key != 'y' && key != 'N' && key != 'Y');
		if (key == 'n' || key == 'N')return;
		FillConsoleOutputCharacterA(hOut, ' ', 21, end_pos, &x);
		FillConsoleOutputCharacterA(hOut, ' ', 42, { passw_pos1.X + 42,passw_pos1.Y }, &x);
		SetConsoleCursorPosition(hOut, passw_pos1);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 20, { passw_pos1.X + 44,passw_pos1.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos1.X + 42,passw_pos1.Y }); cout << "√" << endl;

	SetConsoleCursorPosition(hOut, passw_pos2);
	cin >> temp;
	while (!_legalPassw(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos2.X + 42,passw_pos2.Y });
		cout << "密码不超过12个字符，必须同时包括大小写字母和数字,请重新输入" << endl;
		SetConsoleCursorPosition(hOut, passw_pos2);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { passw_pos2.X + 42,passw_pos2.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos2.X + 42,passw_pos2.Y }); cout << "√" << endl;
	password = temp;

	SetConsoleCursorPosition(hOut, phone_pos);
	cin >> temp;
	while (temp != password) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, phone_pos, &x);
		SetConsoleCursorPosition(hOut, { phone_pos.X + 42,phone_pos.Y });
		cout << "两次密码不一致" << endl;
		SetConsoleCursorPosition(hOut, phone_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { phone_pos.X + 42,phone_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { phone_pos.X + 42,phone_pos.Y }); cout << "√" << endl;
	cout << endl << endl;
	cout << "密码修改成功！" << endl;
	__delay();
	return ;
}

int User::pickSongBySinger(list<Song>& src){
	while (1) {
		system("cls");
		cout << "请输入歌手名----输入-1则返回上一层界面" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_pick;
		to_pick.clear();
		findSongAndPushBack(src, to_pick, [=](Song  s)->bool {return s.getSingerName() == name; });
		if (to_pick.empty()) {
			cout << "抱歉！未查到该歌手的任何曲目" << endl;
			cout << "是否重新输入(按y/n)----按ESC返回主菜单" << endl;
			switch (_pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
		else {
			while (1) {
				system("cls");
				cout << "查询到的歌曲如下：" << endl;
				vector<list<Song>::iterator>::iterator tar = to_pick.begin();
				display2(tar, to_pick.end());
				cout << "输入歌曲ID点歌-----输入0结束" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					break;
				}
				tar = find_if(to_pick.begin(), to_pick.end(), [=](list<Song>::iterator s)->bool {return s->getID() == number; });
				if (tar == to_pick.end()) {
					//未查找到歌曲ID
					cout << "无匹配歌曲----请确保歌曲ID输入无误" << endl;
					cout << "重新输入(按y/n)-------按ESC返回用户菜单" << endl;
					switch (_pressKey1()) {
					case 'n':case'N':break;
					case 27:return 0;
					}
				}
				else {
					if (in_queue.empty())(*tar)->play();
					in_queue.push_back(*(*tar));
					cout << "点歌成功！" << endl;
					cout << endl << endl;
					cout << "按 C 键继续点歌" << endl << "按 ENTER 键重新输入歌手名 " << endl << "按 ESC 返回用户界面" << endl;
					int key;
					do {
						key = _getch();
						_getch();
					} while (key != 'c' && key != 'C' && key != 27 && key != 13);
					if (key == 13)break;
					else if (key == 27)return -1;
					to_pick.erase(tar);
					__delay();
				}
			}
		}
	}
}

int User::pickSongBySongName(list<Song>& src) {
	while (1) {
		system("cls");
		cout << "请输入歌曲名----输入-1则返回上一层界面" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_pick;
		to_pick.clear();
		findSongAndPushBack(src, to_pick, [=](Song s)->bool {return s.getSongName() == name; });
		if (to_pick.empty()) {
			cout << "抱歉！未查到任何歌曲" << endl;
			cout << "是否重新输入(按y/n)----按ESC返回主菜单" << endl;
			switch (_pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
		else {
			while (1) {
				system("cls");
				cout << "查询到的歌曲如下：" << endl;
				vector<list<Song>::iterator>::iterator tar = to_pick.begin();
				display2(tar, to_pick.end());
				cout << "输入歌曲ID点歌-----输入0结束" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					break;
				}
				tar = find_if(to_pick.begin(), to_pick.end(), [=](list<Song>::iterator s)->bool {return s->getID() == number; });
				if (tar == to_pick.end()) {
					//未查找到歌曲ID
					cout << "无匹配歌曲----请确保歌曲ID输入无误" << endl;
					cout << "重新输入(按y/n)-------按ESC返回用户菜单" << endl;
					switch (_pressKey1()) {
					case 'n':case'N':break;
					case 27:return 0;
					}
				}
				else {
					if (in_queue.empty())(*tar)->play();
					in_queue.push_back(*(*tar));
					cout << "点歌成功！" << endl;
					cout << endl << endl;
					cout << "按 C 键继续点歌" << endl << "按 ENTER 键重新输入歌曲名 " << endl << "按 ESC 返回用户界面" << endl;
					int key;
					do {
						key = _getch();
						_getch();
					} while (key != 'c' && key != 'C' && key != 27 && key != 13);
					if (key == 13)break;
					else if (key == 27)return 0;
					to_pick.erase(tar);
					__delay();
				}
			}
		}
	}
}

int User::pickSongByAbbr(list<Song>& src) {
	while (1) {
		system("cls");
		cout << "请输入要查找的拼音----输入-1则返回上一层界面" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_pick_by_song;
		vector<list<Song>::iterator> to_pick_by_singer;
		to_pick_by_song.clear();
		to_pick_by_singer.clear();
		findSongAndPushBack(src, to_pick_by_song, [=](Song s)->bool {return s.isAmbiguousTarSong(name); });
		findSongAndPushBack(src, to_pick_by_singer, [=](Song s)->bool {return s.isAmbiguousTarSinger(name); });
		if (to_pick_by_singer.empty()&& to_pick_by_song.empty()) {
			cout << "抱歉！未查到任何歌曲" << endl;
			cout << "是否重新输入(按y/n)----按ESC返回主菜单" << endl;
			switch (_pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
		else {
			while (1) {
				system("cls");
				if (!to_pick_by_song.empty()) { //显示歌名模糊查询
					cout << "根据歌名模糊查询结果" << endl;
					display2(to_pick_by_song.begin(), to_pick_by_song.end());
				}
				if (!to_pick_by_singer.empty()) {//显示歌手名模糊查询
					cout << "根据歌手名模糊查询结果" << endl;
					display2(to_pick_by_singer.begin(), to_pick_by_singer.end());
				}
				cout << "请输入要点的歌曲ID------输入0结束" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					break;
				}
				vector<list<Song>::iterator>::iterator tar = to_pick_by_song.begin();
				for (; tar != to_pick_by_song.end(); tar++)
					if ((*tar)->getID() == number)break;
				if (tar == to_pick_by_song.end()) {
					//未在歌名模糊查询结果中查找到歌曲ID
					for (tar = to_pick_by_singer.begin(); tar != to_pick_by_singer.end(); tar++)
						if ((*tar)->getID() == number)break;
					if (tar == to_pick_by_singer.end()) {
						cout << "无匹配歌曲----请确保歌曲ID输入无误" << endl;
						cout << "重新输入(按y/n)-------按ESC返回用户菜单" << endl;
						switch (_pressKey1()) {
						case 'n':case'N':break;
						case 27:return 0;
						}
					}
					else {
						if (in_queue.empty())(*tar)->play();
						in_queue.push_back(*(*tar));
						cout << "点歌成功！" << endl;
						cout << endl << endl;
						cout << "按 C 键继续点歌" << endl << "按 ENTER 键重新输入首拼 " << endl << "按 ESC 返回用户界面" << endl;
						int key;
						do {
							key = _getch();
							_getch();
						} while (key != 'c' && key != 'C' && key != 27 && key != 13);
						if (key == 13)break;
						else if (key == 27)return 0;
						to_pick_by_singer.erase(tar);
					}
				}
				else {
					if (in_queue.empty())(*tar)->play();
					in_queue.push_back(*(*tar));
					cout << "点歌成功！" << endl;
					cout << endl << endl;
					cout << "按 C 键继续点歌" << endl << "按 ENTER 键重新输入首拼 " << endl << "按 ESC 返回用户界面" << endl;
					switch (_pressKey1()) {
					case 'n':case'N':break;
					case 27:return 0;
					}
					to_pick_by_song.erase(tar);
				}
			}
		}
	}
}

void User::display1(list<Song>::iterator first, list<Song>::iterator end,int page,int total_page, int num) {
	cout << endl << endl;
	cout << setfill('*') << setw(77) << '*' << endl;
	cout << setfill(' ') << '|' << std::right << setw(40) << "<全部歌曲>" << setw(36) << '|' << endl;
	cout << '|' << setfill('=') << setw(76) << '|' << endl;
	cout << '|' << setfill(' ') << " 歌曲ID " << std::left << setw(28) << "  歌曲名" << setw(19)
		<< " 歌手名" << setw(10) << "歌曲评分" << setw(10) << "播放状态" << '|' << endl;
	for (int i = 0; i < num&&first!=end; i++) {
		cout << '|' << std::right << setw(6) << first->getID() << "  " << std::left << setw(28) << first->getSongName()
			<< setw(20) << first-> getSingerName()<< setw(9) << 5 << setw(10) << (first->isOn() ? "正在播放" : " ") << '|' << endl;
		first++;
	}
	cout << '|' << std::right << setfill('=') << setw(76) << '|' << endl;
	cout << setfill('*') << setw(77) << '*' << endl;
	cout << setfill(' ') << std::right << "第" << page << "页 共" << total_page << "页  上一页(↑) 下一页(↓)" << setw(77) << endl;
}

void User::display2(vector<list<Song>::iterator>::iterator first, vector<list<Song>::iterator>::iterator end)
{
	cout << endl << endl; 
	cout << setfill('*') << setw(77) << '*' << endl;
	cout << '|'<<setfill(' ') << setfill(' ') << " 歌曲ID " << std::left << setw(28) << "  歌曲名" << setw(19)
		<< " 歌手名" << setw(10) << "歌曲评分" << setw(10) << "播放次数" << '|' << endl;
	cout << '|' <<std::right<< setfill('=') << setw(76) << '|' << endl;
	for (int i = 0; first!=end; i++) {
		cout << '|' << std::right<<setfill(' ') << setw(6) << (*first)->getID() << "  " << std::left << setw(28) << (*first)->getSongName()
			<< setw(20) << (*first)->getSingerName() << setw(9) << (*first)->getStar() << setw(10) << (*first)->getCount() << '|' << endl;
		first++;
	}
	cout << setfill('*') << setw(77) << '*' << endl;
}

int User::pickSongFromAll(list<Song> & src) {
	list<Song>::iterator first = src.begin(), last;
	int page = 1;
	do {
		system("cls");
		int count = 0;
		last = first;
		while (count < 10 && last != src.end()) {
			//找到当页显示歌曲的最后一首的尾部
			count++; last++;
		}
		display1(first, src.end(), page, src.size() / 10 + 1);
		cout << "找到要点的曲目，输入编号即可点歌-----按ES返回主界面 按B则结束点歌" << endl;
		int value1, value2;
		do {//排除用户按其他的键值
			value1 = _getch();
			value2 = _getch();
		} while (!(value1 >= '0' && value1 <= '9' || value2 == 72 || value2 == 80 || value1 == 'b'||value1=='B'||value1==27));
		if (value1 == 'b' || value1 == 'B')return 0;  //用户按B
		else if (value1 == 27)return -1;
		else if (value2 == 0) {
			//用户输入曲目编码
			unsigned int number;
			char c = (char)value1;
			cout << c;
			cin.putback(c);
			cin >> number;
			cin.ignore();
			list<Song>::iterator tar = find_if(first, last, [=](Song s)->bool {return s.getID() == number; });
			if (tar == last) {
				cout << "编号输入错误，当前页无该曲目！" << endl;
				__delay();
			}
			else {
				if (in_queue.empty())tar->play();
				in_queue.push_back(*tar);
				cout << "点歌成功！" << endl;
				cout << endl << endl;
				cout << "按 C 键继续点歌" << endl << "按 ENTER 返回用户界面" <<endl << "按 ESC 返回主界面" << endl;
				int key;
				do {
					key = _getch();
					_getch();
				} while (key != 'c' && key != 'C' && key != 27 && key !=13);
				if (key == 27)return -1;
				else if (key == 13)return 0;
			}
		}
		else {
			switch (value2) {
			case 80:if (page != src.size() / 10 + 1) {//先判断是否能继续下翻
				int count = 0;
				while (count < 10 && first != src.end()) {
					count++; first++;
				}
				page++;
			}break;
			case 72:if (page != 1) {//判断是否能上翻
				int count = 0;
				while (count < 10 && first != src.begin()) {
					count++; first--;
				}
				page--;
			}break;
			}
		}
	} while (1);
}

void User::cutSong() {
	if (in_queue.empty()) {
		cout << "暂无歌曲可切！" << endl;
		__delay();
		return;
	}
	out_queue.push_back(*in_queue.begin());
	mark(*in_queue.begin());
	in_queue.erase(in_queue.begin());
	if(!in_queue.empty())in_queue.begin()->play();
}

void User::showInQueue() {
	list<Song>::iterator first = in_queue.begin(), last;
	int page = 1;
	do {
		system("cls");
		int count = 0;
		last = first;
		while (count < 10 && last != in_queue.end()) {
			//找到当页显示歌曲的最后一首的尾部
			count++; last++;
		}
		display1(first, in_queue.end(), page, in_queue.size() / 10 + 1);
		cout << "按ESC返回用户界面" << endl;
		cout << "按1--->置顶歌曲" << endl;
		cout << "按2--->移除歌曲" << endl;
		cout << "按3--->切歌" << endl;
		int value1, value2;
		do {//排除用户按其他的键值
			value1 = _getch();
			value2 = _getch();
		} while (!(value1 == '1' || value1 == '2' || value1 == '3' || value1 == 27 || value2 == 80 || value2 == 72));
		if (value1 == 27)return;  //返回用户界面
		else if (value1 == '1') {
			pushToTop(first, last);
			first = in_queue.begin();
		}
		else if (value1 == '2') {
			substractSong(first, last);
			if (in_queue.empty())return;
			else if (first == in_queue.end()) {
				for (int i = 0; i < 10 && first != in_queue.begin(); i++)first--;
			}
		}
		else if (value1 == '3') {
			cutSong();
			if (in_queue.empty())return;
			first = in_queue.begin();
		}
		else {
			switch (value2) {
			case 80:if (page != in_queue.size() / 10 + 1) {//先判断是否能继续下翻
				int count = 0;
				while (count < 10 && first != in_queue.end()) {
					count++; first++;
				}
				page++;
			}break;
			case 72:if (page != 1) {//判断是否能上翻
				int count = 0;
				while (count < 10 && first != in_queue.begin()) {
					count++; first--;
				}
				page--;
			}break;
			}
		}
	} while (1);
}

void User::substractSong(list<Song>::iterator &first, list<Song>::iterator end) {
	cout << "请输入要删除歌曲ID----输入-1则结束" << endl;
	unsigned int number;
	cin >> number;
	if (number == -1) {
		cin.ignore();
		return;
	}
	cin.ignore();
	cin.clear();
	list<Song>::iterator it;
	do {
		it = find_if(first, end, [=](Song s)->bool {return s.getID() == number; });
		if (it == end) {
			cout << "未匹配到歌曲 请确保歌曲在该页中" << endl;
			cout << "重新输入(按y/n)" << endl;
			int key;
			do {
				key = _getch();
				_getch();
			} while (key != 'n' && key != 'N' && key != 'y' && key != 'Y');
			if (key == 'n' || key == 'N')return;
			else cin >> number;
		}
	} while (it == end);
	if (it == first) first++;
	out_queue.push_back(*it);
	in_queue.erase(it);
	cout << "删除成功！" << endl;
	__delay();
}

void User::pushToTop(list<Song>::iterator first, list<Song>::iterator end) {
	cout << "请输入要置顶的歌曲ID----输入-1则结束" << endl;
	unsigned int number;
	cin >> number;
	if (number == -1) {
		cin.ignore();
		return;
	}
	cin.ignore();
	cin.clear();
	list<Song>::iterator it;
	do {
		it = find_if(first, end, [=](Song s)->bool {return s.getID() == number; });
		if (it == end) {
			cout << "未匹配到歌曲 请确保歌曲在该页中" << endl;
			cout << "重新输入(按y/n)" << endl;
			int key;
			do {
				key = _getch();
				_getch();
			} while (key != 'n' && key != 'N' && key != 'y' && key != 'Y');
			if (key == 'n' || key == 'N')return;
			else cin >> number;
		}
	} while (it == end);
	in_queue.push_front(*it);
	list<Song>::iterator temp = in_queue.begin();
	temp++;
	in_queue.push_front(*temp);
	in_queue.erase(it);
	in_queue.erase(temp);
	cout << "置顶成功！" << endl;
	__delay();
}

void User::mark(Song &song)
{
	cout << endl;
	cout << "请留下宝贵的评价";
	cout << endl << "*************************************************" << endl;
	cout << "                  歌曲评价" << endl;
	cout << "=================================================" << endl;
	cout << "请给歌曲评分（1-5分），分数越高表示越满意" << endl;
	int star;
	cin >> star;
	if (star > 5) {
		cout << "我们十分感激你的过高评价，已将评分置满--5分" << endl;
		star = 5;
	}
	else if (star < 1) {
		cout << "该分数一定表示我们还有待提高，已默认赋分为0" << endl;
		star = 0;
	}
	else cout << "感谢你的评分，你的意见将是我们改进的指引" << endl;
	song.setStar(star);
	__delay();
	cout.clear();
	cin.sync();
}

ifstream & operator>>(ifstream & f_in, User & user){
	string s;
	getline(f_in, s);
	istringstream iss(s);
	stringstream trans;
	s.clear();
	getline(iss, s, '|');
	trans << s;
	trans >> user.phone;
	getline(iss, user.name, '|');
	getline(iss, user.password, '|');
	return f_in;
}

ofstream & operator<<(ofstream & f_out, const User & user){
	f_out << user.phone << '|' << user.name << '|' << user.password << '|' << endl;
	return f_out;
}
