#include "Admin.h"
#include <Windows.h>
#include <iomanip>
#include <conio.h>

Admin::Admin(){
	name = "";
	password = "";
	phone = 0;
	wrong = 0;
}

void delay() {
	cout << endl;
	for (int i = 0; i < 300000000; i++)
		if (i % 100000000 == 0)cout << "\r即将跳转......." << 3 - i / 100000000;
	cout.clear();
	cin.sync();
}

int pressKey1() {
	int key;
	do {
		key = _getch();
		_getch();
	} while (key != 89 && key != 78 && key != 110 && key != 121 && key != 27);
	return key;
}

template<typename pfunc>
void Admin::findSongAndPushBack(list<Song>&src, vector< list<Song>::iterator> &v, pfunc const &pf) {
	list<Song>::iterator it=src.begin();
	while (it != src.end()) { 
		it = find_if(it, src.end(), pf);
		if (it != src.end()) { v.push_back(it); ++it; }
	}
}

bool Admin::login(string passw) {
	if (wrong >= 3) {
		cout << "密码连续输入错误3次！账户已被锁定！失去访问权限！" << endl;
		cout << "请前往账户验证解锁--重置密码或退出访问" << endl;
		return false;
	}
	else if (password == passw) {
		return true;
		wrong = 0;
	}
	else {
		wrong++;
		return false;
	}
}

void Admin::main_menu(list<Song>& src){
	while (1) {
		system("cls");
		cout << endl << endl << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t|             <管理员界面>              |" << endl;
		cout << "\t\t\t|=======================================|" << endl;
		cout << "\t\t\t|             1 所有歌曲                |" << endl;
		cout << "\t\t\t|             2 添加歌曲                |" << endl;
		cout << "\t\t\t|             3 批量导入歌曲            |" << endl;
		cout << "\t\t\t|             4 删除歌曲                |" << endl;
		cout << "\t\t\t|             5 歌曲排序                |" << endl;
		cout << "\t\t\t|             6 修改密码                |" << endl;
		cout << "\t\t\t|            ESC 退返主界面             |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		int key;
		do {//确保键值正确
			key = _getch();
			_getch();
		} while (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != 27);
		switch (key) {
		case '1':if (display(src) == -1)return; break;
		case '2':addOneSong(src); break;
		case '3':addSomeSong(src); break;
		case '4':if (substractSong(src) == -1)return; break;
		case '5':if (rankSong(src) == -1)return; break;
		case '6':if(changePassword()==-1)return; break;
		case 27:return;
		}
	}
}

bool isNumber(char c) {
	if (c >= '0'&&c <= '9')return true;
	else return false;
}
bool isBigCharacter(char c) {
	if (c >= 'A'&&c <= 'Z')return true;
	else return false;
}
bool isSmallCharacter(char c) {
	if (c >= 'a'&&c <= 'z')return true;
	else return false;
}
bool legalName(string name) {
	if (name.length() > 20)return false;
	else {
		for (int i = 0; i < name.length(); i++) {
			if (!(isNumber(name[i]) || isBigCharacter(name[i])|| isSmallCharacter(name[i])))return false;
		}
		return true;
	}
}
bool legalPassw(string passw) {
	if (passw.length() > 12)return false;
	else {
		bool flag1=false, flag2 = false, flag3 = false;
		for (int i = 0; i < passw.length(); i++) {
			if (isNumber(passw[i]))flag1 = true;
			else if (isBigCharacter(passw[i]))flag2 = true;
			else if (isSmallCharacter(passw[i]))flag3 = true;
		}
		return (flag1 && flag2 && flag3);
	}
}

Admin * Admin::sign_up()
{
	system("cls");
	Admin*p = new Admin;
	string temp;
	COORD name_pos, passw_pos1, passw_pos2, phone_pos;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                       管理员注册                         " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         用户名："; GetConsoleScreenBufferInfo(hOut, &bInfo); name_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         确认密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         密保手机:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	SetConsoleCursorPosition(hOut, name_pos);
	cin >> temp;
	DWORD x;
	while (!legalName(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 41, name_pos, &x);
		SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y });
		cout << "管理员ID不超过20个字符，只能由大小写字母或数字组成,请重新输入" << endl;
		SetConsoleCursorPosition(hOut, name_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { name_pos.X + 41,name_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y }); cout << "√" << endl;
	p->name = temp;

	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	while (!legalPassw(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 43, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 43,passw_pos1.Y });
		cout << "密码不超过12个字符，必须同时包括大小写字母和数字,请重新输入" << endl;
		SetConsoleCursorPosition(hOut, passw_pos1);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { passw_pos1.X + 43,passw_pos1.Y }, &x);
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
	FillConsoleOutputCharacterA(hOut, ' ', 19, { passw_pos2.X + 39,passw_pos2.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos2.X + 39,passw_pos2.Y }); cout << "√" << endl;
	SetConsoleCursorPosition(hOut, phone_pos);

	cin >> p->phone;
	SetConsoleCursorPosition(hOut, { phone_pos.X + 40,phone_pos.Y }); cout << "√" << endl;
	delay();
	cin.ignore(1024, '\n');
	cin.clear();
	return p;
}

int Admin::changePassword() {
	system("cls");
	string temp;
	COORD  passw_pos1, passw_pos2, phone_pos;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                       重置密码                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         原密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         新密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         确认新密码:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	DWORD x;
	while (temp != password) {
		FillConsoleOutputCharacterA(hOut, ' ', 44, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 44,passw_pos1.Y });
		cout << "×密码错误  " <<"剩余"<<3-(++wrong)<<"次"<< endl;
		SetConsoleCursorPosition(hOut, passw_pos1);
		if (wrong == 3)goto END;
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 20, { passw_pos1.X + 44,passw_pos1.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos1.X + 44,passw_pos1.Y }); cout << "√" << endl;

	SetConsoleCursorPosition(hOut, passw_pos2);
	cin >> temp;
	while (!legalPassw(temp)) {
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
	while (temp!=password) {
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
	delay();
	return 0;
END:
	system("cls");
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                账户被锁定                                " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	delay();
	return -1;
}

int Admin::display(list<Song>&src){
	list<Song>::iterator first = src.begin();
	int page = 1;
	do {
		system("cls");
		int count = 0;
		showSong(first, src.end(),page, src.size() / 10 + 1);
		cout << "按ESC返回主界面，按ENTER返回管理员界面" << endl;
		int value1, value2;
		do {//排除用户按其他的键值
			value1 = _getch();
			value2 = _getch();
		} while (!(value2 == 72 || value2 == 80 || value1 == 13 || value1 == 27));
		if (value1 == 13)return 0;
		else if (value1 == 27)return -1;
		else {
			switch(value2) {
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

void Admin::showSong(list<Song>::iterator first, list<Song>::iterator end, int page, int total_page, int num){
	cout << endl << endl;
	cout << setfill('*') << setw(114) << '*' << endl;
	cout << setfill(' ') << '|' << std::right << setw(61) << "<全部歌曲>" << setw(52) << '|' << endl;
	cout << '|' << setfill('=') << setw(113) << '|' << endl;
	cout << '|' << setfill(' ') << " 歌曲ID " << std::left << setw(28) << "  歌曲名" << setw(19) << " 歌手名" << setw(15) << "歌曲名首拼" << setw(12)
		<< "歌手名首拼" << setw(10) << "歌曲评分" << setw(10) << "播放次数" << setw(10) << "播放状态" << '|' << endl;
	for (int i = 0; i < num&&first!=end; i++) {
		cout << "|" << std::right << setw(6) << first->ID << "  " << std::left << setw(28) << first->song_name << setw(20) << first->singer
			<< setw(15) << first->abbr_song << setw(14) << first->abbr_singer << setw(9) << first->star << setw(8)
			<< first->count << setw(10) << (first->in_playing ? "正在播放" : "未在播放") << '|' << endl;
		first++;
	}
	cout << setfill('*') << setw(114) << '*' << endl;
	cout << setfill(' ') <<std::right <<"第" << page << "页 共" << total_page << "页  上一页(↑) 下一页(↓)" << setw(114) << endl;
}

void Admin::mergeSongList(list<Song>& src,list<Song>& newlist) {
	list<Song>:: iterator  it = newlist.begin();
	while (it != newlist.end()) {                                     //将不重复的歌曲存入src中
		list<Song>::iterator same = find(src.begin(), src.end(), *it);
		if (same == src.end()) {
			src.push_back(*it);
			newlist.erase(it);
		}
		it++;
	}
}

void Admin::addOneSong(list<Song>&src) {
	system("cls");
	cout << "请输入歌曲信息(歌曲名|歌手名|歌曲名首拼|歌手名首拼|)------输入-1退出" << endl;
	string s;
	cin >> s;
	if (s == "-1") {
		cin.ignore();
		return;
	}
	string temp;
	getline(cin, temp);
	s.append(temp);
	istringstream iss(s);
	Song newsong;
	iss >> newsong;
	list<Song>::iterator same = find(src.begin(), src.end(), newsong);
	if (same == src.end()) {
		src.push_back(newsong);
		cout << "歌曲添加成功！" << endl;
		delay();
	}
	else {
		cout << "歌曲添加失败！   曲库已存在！" << endl;
		delay();
	}
}

void Admin::addSomeSong(list<Song>& src){
	system("cls");
	cin.sync();
	cout << "请输入歌曲文件名---------输入为-1返回上一层界面" << endl;
	string file_name;
	cin >> file_name;
	if (file_name == "-1") {
		cin.ignore();
		return;
	}
	cin.ignore();
	ifstream f_in;
	f_in.open(file_name);
	while (!f_in.is_open()) {  //确保文件正确打开
		cout << "文件打开失败！请确认是否添加正确路径" << endl;
		cout << "请输入歌曲文件名---------输入为-1返回上一层界面" << endl;
		getline(cin, file_name);
		if (file_name == "-1") {
			cin.ignore();
			return;
		}
		f_in.open(file_name);
	}
	list<Song>new_song_list;
	while (!f_in.eof()) {  //读入歌曲
		Song newsong;
		f_in >> newsong;
		new_song_list.push_back(newsong);
		while (!f_in.eof() && (f_in.peek() == ' ' || f_in.peek() == '\n'))f_in.get();//防止文件尾空白符干扰对文件结束的判断
	}
	f_in.close();
	int total = new_song_list.size();
	mergeSongList(src, new_song_list);
	cout << "总计" << total << "首歌曲" << endl;
	if (!new_song_list.empty()) {
		cout << "其中" << new_song_list.size() << "首歌曲导入失败！" << endl;
		cout << "原因：曲库中已经存在！" << endl;
		cout << "未导入歌曲如下：" << endl;
		list<Song>::iterator cur = new_song_list.begin();
		int count = 1;
		while (cur != new_song_list.end()) {
			cout << count<< " " << cur->song_name << "\t\t" << cur->singer << endl;
			count++; cur++;
		}
		cout << "按ENTER键继续" << endl;
		cin.get();
	}
	cout << "批量导入结束！" << endl;
	delay();
}

int Admin::substract1(list<Song>&src) {
	list<Song>::iterator first = src.begin(),last;
	int page = 1;
	do {
		system("cls");
		int count = 0;
		last = first;
		while (count < 10 && last != src.end()) {
			//找到当页显示歌曲的最后一首的尾部
			count++; last++;
		}
		showSong(first, src.end(),page, src.size() / 10 + 1);
		cout << "找到要删除的曲目，输入编号即可删除-----ESC返回管理员界面、按B则返回上一层界面" << endl;
		int value1, value2;
		do {//排除用户按其他的键值
			value1 = _getch();
			value2 = _getch();
		} while (!(value1 >= '0' && value1 <= '9' || value2 == 72 || value2 == 80 || value1 == 'b'|| value1 == 'B' || value1 == 27));
		if (value1 == 'b' || value1 == 'B')return 0;  //用户按下B
		else if (value1 == 27)return -1;  //用户按下ESC
		else if (value2 == 0) {   
			//用户输入曲目编码
			unsigned int number;
			char c = (char)value1;
			cout << c;         
			cin.putback(c);         //返回_getch()掉的一个字符
			cin >> number;
			cin.ignore();
			list<Song>::iterator tar = find_if(first, last, [=](Song s)->bool {return s.getID() == number; });
			if (tar == last) cout << "编号输入错误，当前页无该曲目！" << endl;
			else {
				if (tar == first) {
					first++;
					if (subsConfirm(src, tar)) cout << "删除成功！" << endl;
					else first--;
				}
				else if (subsConfirm(src, tar)) cout << "删除成功！" << endl;
			}
			delay();
		}
		else {   //用户翻页
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

int Admin::substract2(list<Song>& src)
{
	while (1) {
		system("cls");
		cin.sync();
		cout << "请输入要删除的歌曲名------输入-1则返回上一层界面" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_delete;
		to_delete.clear();
		list<Song>::iterator it = src.begin();
		findSongAndPushBack(src, to_delete, [=](Song s)->bool {return s.getSongName() == name; });
		if (to_delete.empty()) {
			cout << "未找到匹配歌曲！请确认输入歌曲名是否正确 或 该歌曲不在曲库中" << endl;
			cout << "重新输入或者结束(按y/n)--------按ESC直接返回管理员界面" << endl;
			switch (pressKey1()){
			case 'n':case'N':return 0;
			case 27:return -1;
			}
			delay();
		}
		else {
			while (to_delete.size() != 0) {
				system("cls");
				cout << "查到的歌曲如下：" << endl;
				for (unsigned int i = 0; i < to_delete.size(); i++)
					cout << to_delete[i]->ID << "  " << to_delete[i]->song_name << "  " << to_delete[i]->singer << endl;
				cout << "输入歌曲编号删除对应歌曲" << endl;
				cout << "输入0结束删除" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					break;
				}
				cin.ignore(1024, '\n');
				vector<list<Song>::iterator>::iterator i;
				for (i = to_delete.begin(); i != to_delete.end(); i++)
					if ((*i)->ID == number)break;
				if (i == to_delete.end()) {
					cout << "曲目编号输入出错！" << endl;
					cout << "重新输入(按y/n)-------按ESC直接返回管理员菜单" << endl;
					switch (pressKey1()) {
					case 'n':case'N':return 0;
					case 27:return -1;
					}
				}
				else {
					if (subsConfirm(src, *i)) {//确认删除
						cout << "删除成功！" << endl;
					}
					to_delete.erase(i);
				}
				delay();
			}
		}
	}
}

int Admin::substract3(list<Song>& src)
{
	while (1) {
		system("cls");
		cin.sync();
		cout << "请输入要删除的歌手名------输入-1则结束本次删除" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_delete;
		to_delete.clear();
		list<Song>::iterator it = src.begin();
		findSongAndPushBack(src, to_delete, [=](Song s)->bool {return s.getSingerName() == name; });
		if (to_delete.empty()) {
			cout << "未找到匹配歌曲！请确认输入歌手名是否正确 或 曲库中暂无该歌手的曲目" << endl;
			cout << "重新输入或者结束(按y/n)--------按ESC直接返回管理员界面" << endl;
			switch (pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
			delay();
		}
		else {
			while (to_delete.size() != 0) {
				system("cls");
				cout << "查到的歌曲如下：" << endl;
				for (unsigned int i = 0; i < to_delete.size(); i++)
					cout << to_delete[i]->ID << "  " << to_delete[i]->song_name << "  " << to_delete[i]->singer << endl;
				cout << "输入歌曲编号删除对应歌曲" << endl;
				cout << "输入0结束删除" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					return 0;
				}
				cin.ignore(1024, '\n');
				vector<list<Song>::iterator>::iterator i;
				for (i = to_delete.begin(); i != to_delete.end(); i++)
					if ((*i)->ID == number)break;
				if (i == to_delete.end()) {
					cout << "曲目编号输入出错！" << endl;
					cout << "重新输入(按y/n)-------按ESC直接返回管理员菜单" << endl;
					switch (pressKey1()) {
					case 'n':case'N':return 0;
					case 27:return -1;
					}
				}
				else if (subsConfirm(src, *i)) {//确认删除
					cout << "删除成功！" << endl;
					to_delete.erase(i);
					delay();
				}
			}
		}
	}
}

int Admin::substract4(list<Song>& src)
{
	while (1) {
		system("cls");
		cin.sync();
		cout << "请输入要查找的首拼------输入-1则结束本次删除" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_delete_by_song;
		vector<list<Song>::iterator> to_delete_by_singer;
		to_delete_by_song.clear();
		to_delete_by_singer.clear();						//模糊查找歌曲
		findSongAndPushBack(src, to_delete_by_song, [=](Song s)->bool {return s.isAmbiguousTarSong(name); });
		findSongAndPushBack(src, to_delete_by_singer, [=](Song s)->bool {return s.isAmbiguousTarSinger(name); });
		if (!to_delete_by_song.empty() || !to_delete_by_singer.empty()) {
			while (!to_delete_by_song.empty() || !to_delete_by_singer.empty()) {
				system("cls");
				vector<list<Song>::iterator>::iterator i1 = to_delete_by_song.begin();
				vector<list<Song>::iterator>::iterator i2 = to_delete_by_singer.begin();
				if (!to_delete_by_song.empty()){
					cout << "按歌曲名查询结果" << endl;
					for (; i1 != to_delete_by_song.end(); i1++)
						cout << (*i1)->ID<<"  "<<(*i1)->song_name<<"  "<<(*i1)->singer << endl;
				}
				if (!to_delete_by_singer.empty()) {
					cout << "按歌手名查询结果" << endl;
					for (; i2 != to_delete_by_singer.end(); i2++)
						cout << (*i2)->ID << "  " << (*i2)->song_name << "  " << (*i2)->singer << endl;
				}
				cout << "请输入歌曲ID删除对应歌曲" << endl;
				cout << "输入0结束" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					return 0;
				}
				cin.ignore(1024, '\n');
				vector<list<Song>::iterator>::iterator tar;
				for (tar = to_delete_by_song.begin(); tar != to_delete_by_song.end(); tar++)
					if ((*tar)->ID == number)break;
				if (tar == to_delete_by_song.end()){
					for (tar = to_delete_by_singer.begin(); tar != to_delete_by_singer.end(); tar++)
						if ((*tar)->ID == number)break;
					if (tar == to_delete_by_singer.end()) {
						cout << "曲目编号输入出错！" << endl;
						cout << "重新输入(按y/n)-------按ESC直接返回管理员菜单" << endl;
						switch (pressKey1()) {
						case 'n':case'N':return 0;
						case 27:return -1;
						}
					}
					else if (subsConfirm(src, *tar)) {//确认删除
						cout << "删除成功！" << endl;
						to_delete_by_singer.erase(tar);
						delay();
					}
				}
				else if (subsConfirm(src, *tar)) {//确认删除
						cout << "删除成功！" << endl;
						to_delete_by_song.erase(tar);
						delay();
				}
			} 
		}
		else{
			cout << "很遗憾！没有查到相关曲目" << endl;
			cout << "重新输入(按y/n)-------按ESC直接返回管理员菜单" << endl;
			switch (pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
	} 
}

int Admin::substractSong(list<Song>&src) {
	while (1) {
		system("cls");
		cout << endl << endl << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t|            <歌曲删除界面>             |" << endl;
		cout << "\t\t\t|=======================================|" << endl;
		cout << "\t\t\t|            1 边查看边删               |" << endl;
		cout << "\t\t\t|            2 按歌曲名删除             |" << endl;
		cout << "\t\t\t|            3 按歌手名删除             |" << endl;
		cout << "\t\t\t|            4 模糊查找要删除的曲目     |" << endl;
		cout << "\t\t\t|          ENTER 结束删除               |" << endl;
		cout << "\t\t\t|          ESC   退返主界面             |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		int key;
		do {//确保键值正确
			key = _getch();
			_getch();
		} while (key != '1' && key != '2' && key != '3' && key != '4' && key != 27 && key != 13);
		int feedback;
		switch (key) {
		case '1':feedback = substract1(src); break;
		case '2':feedback = substract2(src); break;
		case '3':feedback = substract3(src); break;
		case '4':feedback = substract4(src); break;
		case 13: return 0;
		case 27:return -1;
		}
		if (feedback == -1)return -1;
	}
}

bool Admin::subsConfirm(list<Song>& src, list<Song>::iterator tar)
{
	cout << "要删除的歌曲：" << tar->song_name << "   " << tar->singer << endl;
	cout << "确认删除(按y/n)" << endl;
	int key;
	do {
		key = _getch();
		_getch();
	} while (key != 89 && key != 78 && key != 110 && key != 121 && key != 27);
	if (key == 89 || key == 121) {//确认删除
		unsigned int ID = tar->ID;
		updateSongID(++tar, src.end(), ID);
		tar--;
		src.erase(tar);
		return true;
	}
	else return false;
}

int Admin::rankSong(list<Song>&src){
	system("cls");
	cout << endl << endl << endl;
	cout << "\t\t\t*****************************************" << endl;
	cout << "\t\t\t|            <歌曲排序界面>             |" << endl;
	cout << "\t\t\t|             1 按歌手名                |" << endl;
	cout << "\t\t\t|             2 按歌曲名                |" << endl;
	cout << "\t\t\t|             3 按播放次数              |" << endl;
	cout << "\t\t\t|             4 按歌曲评分              |" << endl;
	cout << "\t\t\t|           ENTER 结束排序              |" << endl;
	cout << "\t\t\t|           ESC   退返主界面            |" << endl;
	cout << "\t\t\t*****************************************" << endl;
	int key;
	do {//确保键值正确
		key = _getch();
		_getch();
	} while (key != '1' && key != '2' && key != '3' && key != '4' && key != 27 && key != 13);
	switch (key) {
	case '1':src.sort([](Song s1, Song s2)->bool {return s1.getSingerName() < s2.getSingerName(); });
		cout << "排序成功!"<<endl; break;
	case '2':src.sort([](Song s1, Song s2)->bool {return s1.getSongName() < s2.getSongName(); });
		cout << "排序成功!" << endl; break;
	case '3':src.sort([](Song s1, Song s2)->bool {return s1.getCount() < s2.getCount(); });
		cout << "排序成功" << endl; break;
	case '4':src.sort([](Song s1, Song s2)->bool {return s1.getStar() < s2.getStar(); });
		cout << "排序成功" << endl; break;
	case 13:return 0;
	case 27:return -1;
	}
	updateSongID(src.begin(), src.end(), 1);
	delay();
	return 0;
}

void Admin::modifySong(list<Song>& src)
{
}

void Admin::updateSongID(list<Song>::iterator first, list<Song>::iterator end,int number_of_fisrt){
	unsigned int curNumber = number_of_fisrt;
	list<Song>::iterator i = first;
	while (i != end) {
		i->ID = curNumber;
		curNumber++;
		i++;
	}
}

ifstream & operator>>(ifstream & f_in, Admin & admin) {
	string s;
	getline(f_in, s);
	istringstream iss(s);
	stringstream trans;
	s.clear();
	getline(iss, s, '|');
	trans << s;
	trans >> admin.wrong;
	s.clear();
	getline(iss, s, '|');
	trans << s;
	trans >> admin.phone;
	getline(iss, admin.name, '|');
	getline(iss, admin.password, '|');
	return f_in;
}

ofstream & operator<<(ofstream & f_out, const Admin & admin) {
	f_out << admin.wrong << '|' << admin.phone << '|' << admin.name << '|' << admin.password << '|' << endl;
	return f_out;
}
