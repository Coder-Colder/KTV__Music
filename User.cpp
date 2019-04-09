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
		if (i % 100000000 == 0)cout << "\r������ת......." << 3 - i / 100000000;
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
		cout << "\t\t\t|              <�û�����>               |" << endl;
		cout << "\t\t\t|             1 ���ֵ��                |" << endl;
		cout << "\t\t\t|             2 ��������                |" << endl;
		cout << "\t\t\t|             3 ƴ�����                |" << endl;
		cout << "\t\t\t|             4 ���и���                |" << endl;
		cout << "\t\t\t|             5 �ѵ����                |" << endl;
		cout << "\t\t\t|             6   �и�                  |" << endl;
		cout << "\t\t\t|            ESC �˷�������             |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t��ѡ�� [ ]\b\b";
		int key;
		do {//ȷ����ֵ��ȷ
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
	cout << "\t\t\t                        �û�ע��                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         �û�����"; GetConsoleScreenBufferInfo(hOut, &bInfo); name_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         ���룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         ȷ�����룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         �ܱ��ֻ�:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	SetConsoleCursorPosition(hOut, name_pos);
	cin >> temp;
	DWORD x;
	while (!_legalName(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 41, name_pos, &x);
		SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y });
		cout << "�û�ID������20���ַ���ֻ���ɴ�Сд��ĸ���������,����������" << endl;
		SetConsoleCursorPosition(hOut, name_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { name_pos.X + 41,name_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y }); cout << "��" << endl;
	p->name = temp;

	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	while (!_legalPassw(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 43, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 43,passw_pos1.Y });
		cout << "���벻����12���ַ�������ͬʱ������Сд��ĸ������,����������" << endl;
		SetConsoleCursorPosition(hOut, passw_pos1);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ',60, { passw_pos1.X + 43,passw_pos1.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos1.X + 43,passw_pos1.Y }); cout << "��" << endl;
	p->password = temp;

	SetConsoleCursorPosition(hOut, passw_pos2);
	cin >> temp;
	while (temp != p->password) {
		FillConsoleOutputCharacterA(hOut, ' ', 39, passw_pos2, &x);
		SetConsoleCursorPosition(hOut, { passw_pos2.X + 39,passw_pos2.Y });
		cout << "�����������벻һ��" << endl;
		SetConsoleCursorPosition(hOut, passw_pos2);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ',19, { passw_pos2.X + 39,passw_pos2.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos2.X + 39,passw_pos2.Y }); cout << "��" << endl;
	SetConsoleCursorPosition(hOut, phone_pos);

	cin >> p->phone;
	SetConsoleCursorPosition(hOut, { phone_pos.X + 40,phone_pos.Y }); cout << "��" << endl;
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
	cout << "\t\t\t                       ��������                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         ԭ���룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         �����룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         ȷ��������:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl << endl;
	GetConsoleScreenBufferInfo(hOut, &bInfo);end_pos = bInfo.dwCursorPosition;
	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	DWORD x;
	while (temp != password) {
		FillConsoleOutputCharacterA(hOut, ' ', 44, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 44,passw_pos1.Y });
		cout << "�� �������  " << endl;
		SetConsoleCursorPosition(hOut, end_pos);
		cout << "�Ƿ���������(��y/n)" << endl;
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
	SetConsoleCursorPosition(hOut, { passw_pos1.X + 42,passw_pos1.Y }); cout << "��" << endl;

	SetConsoleCursorPosition(hOut, passw_pos2);
	cin >> temp;
	while (!_legalPassw(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos2.X + 42,passw_pos2.Y });
		cout << "���벻����12���ַ�������ͬʱ������Сд��ĸ������,����������" << endl;
		SetConsoleCursorPosition(hOut, passw_pos2);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { passw_pos2.X + 42,passw_pos2.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos2.X + 42,passw_pos2.Y }); cout << "��" << endl;
	password = temp;

	SetConsoleCursorPosition(hOut, phone_pos);
	cin >> temp;
	while (temp != password) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, phone_pos, &x);
		SetConsoleCursorPosition(hOut, { phone_pos.X + 42,phone_pos.Y });
		cout << "�������벻һ��" << endl;
		SetConsoleCursorPosition(hOut, phone_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { phone_pos.X + 42,phone_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { phone_pos.X + 42,phone_pos.Y }); cout << "��" << endl;
	cout << endl << endl;
	cout << "�����޸ĳɹ���" << endl;
	__delay();
	return ;
}

int User::pickSongBySinger(list<Song>& src){
	while (1) {
		system("cls");
		cout << "�����������----����-1�򷵻���һ�����" << endl;
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
			cout << "��Ǹ��δ�鵽�ø��ֵ��κ���Ŀ" << endl;
			cout << "�Ƿ���������(��y/n)----��ESC�������˵�" << endl;
			switch (_pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
		else {
			while (1) {
				system("cls");
				cout << "��ѯ���ĸ������£�" << endl;
				vector<list<Song>::iterator>::iterator tar = to_pick.begin();
				display2(tar, to_pick.end());
				cout << "�������ID���-----����0����" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					break;
				}
				tar = find_if(to_pick.begin(), to_pick.end(), [=](list<Song>::iterator s)->bool {return s->getID() == number; });
				if (tar == to_pick.end()) {
					//δ���ҵ�����ID
					cout << "��ƥ�����----��ȷ������ID��������" << endl;
					cout << "��������(��y/n)-------��ESC�����û��˵�" << endl;
					switch (_pressKey1()) {
					case 'n':case'N':break;
					case 27:return 0;
					}
				}
				else {
					if (in_queue.empty())(*tar)->play();
					in_queue.push_back(*(*tar));
					cout << "���ɹ���" << endl;
					cout << endl << endl;
					cout << "�� C ���������" << endl << "�� ENTER ��������������� " << endl << "�� ESC �����û�����" << endl;
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
		cout << "�����������----����-1�򷵻���һ�����" << endl;
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
			cout << "��Ǹ��δ�鵽�κθ���" << endl;
			cout << "�Ƿ���������(��y/n)----��ESC�������˵�" << endl;
			switch (_pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
		else {
			while (1) {
				system("cls");
				cout << "��ѯ���ĸ������£�" << endl;
				vector<list<Song>::iterator>::iterator tar = to_pick.begin();
				display2(tar, to_pick.end());
				cout << "�������ID���-----����0����" << endl;
				unsigned int number;
				cin >> number;
				if (number == 0) {
					cin.ignore();
					break;
				}
				tar = find_if(to_pick.begin(), to_pick.end(), [=](list<Song>::iterator s)->bool {return s->getID() == number; });
				if (tar == to_pick.end()) {
					//δ���ҵ�����ID
					cout << "��ƥ�����----��ȷ������ID��������" << endl;
					cout << "��������(��y/n)-------��ESC�����û��˵�" << endl;
					switch (_pressKey1()) {
					case 'n':case'N':break;
					case 27:return 0;
					}
				}
				else {
					if (in_queue.empty())(*tar)->play();
					in_queue.push_back(*(*tar));
					cout << "���ɹ���" << endl;
					cout << endl << endl;
					cout << "�� C ���������" << endl << "�� ENTER ��������������� " << endl << "�� ESC �����û�����" << endl;
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
		cout << "������Ҫ���ҵ�ƴ��----����-1�򷵻���һ�����" << endl;
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
			cout << "��Ǹ��δ�鵽�κθ���" << endl;
			cout << "�Ƿ���������(��y/n)----��ESC�������˵�" << endl;
			switch (_pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
		}
		else {
			while (1) {
				system("cls");
				if (!to_pick_by_song.empty()) { //��ʾ����ģ����ѯ
					cout << "���ݸ���ģ����ѯ���" << endl;
					display2(to_pick_by_song.begin(), to_pick_by_song.end());
				}
				if (!to_pick_by_singer.empty()) {//��ʾ������ģ����ѯ
					cout << "���ݸ�����ģ����ѯ���" << endl;
					display2(to_pick_by_singer.begin(), to_pick_by_singer.end());
				}
				cout << "������Ҫ��ĸ���ID------����0����" << endl;
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
					//δ�ڸ���ģ����ѯ����в��ҵ�����ID
					for (tar = to_pick_by_singer.begin(); tar != to_pick_by_singer.end(); tar++)
						if ((*tar)->getID() == number)break;
					if (tar == to_pick_by_singer.end()) {
						cout << "��ƥ�����----��ȷ������ID��������" << endl;
						cout << "��������(��y/n)-------��ESC�����û��˵�" << endl;
						switch (_pressKey1()) {
						case 'n':case'N':break;
						case 27:return 0;
						}
					}
					else {
						if (in_queue.empty())(*tar)->play();
						in_queue.push_back(*(*tar));
						cout << "���ɹ���" << endl;
						cout << endl << endl;
						cout << "�� C ���������" << endl << "�� ENTER ������������ƴ " << endl << "�� ESC �����û�����" << endl;
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
					cout << "���ɹ���" << endl;
					cout << endl << endl;
					cout << "�� C ���������" << endl << "�� ENTER ������������ƴ " << endl << "�� ESC �����û�����" << endl;
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
	cout << setfill(' ') << '|' << std::right << setw(40) << "<ȫ������>" << setw(36) << '|' << endl;
	cout << '|' << setfill('=') << setw(76) << '|' << endl;
	cout << '|' << setfill(' ') << " ����ID " << std::left << setw(28) << "  ������" << setw(19)
		<< " ������" << setw(10) << "��������" << setw(10) << "����״̬" << '|' << endl;
	for (int i = 0; i < num&&first!=end; i++) {
		cout << '|' << std::right << setw(6) << first->getID() << "  " << std::left << setw(28) << first->getSongName()
			<< setw(20) << first-> getSingerName()<< setw(9) << 5 << setw(10) << (first->isOn() ? "���ڲ���" : " ") << '|' << endl;
		first++;
	}
	cout << '|' << std::right << setfill('=') << setw(76) << '|' << endl;
	cout << setfill('*') << setw(77) << '*' << endl;
	cout << setfill(' ') << std::right << "��" << page << "ҳ ��" << total_page << "ҳ  ��һҳ(��) ��һҳ(��)" << setw(77) << endl;
}

void User::display2(vector<list<Song>::iterator>::iterator first, vector<list<Song>::iterator>::iterator end)
{
	cout << endl << endl; 
	cout << setfill('*') << setw(77) << '*' << endl;
	cout << '|'<<setfill(' ') << setfill(' ') << " ����ID " << std::left << setw(28) << "  ������" << setw(19)
		<< " ������" << setw(10) << "��������" << setw(10) << "���Ŵ���" << '|' << endl;
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
			//�ҵ���ҳ��ʾ���������һ�׵�β��
			count++; last++;
		}
		display1(first, src.end(), page, src.size() / 10 + 1);
		cout << "�ҵ�Ҫ�����Ŀ�������ż��ɵ��-----��ES���������� ��B��������" << endl;
		int value1, value2;
		do {//�ų��û��������ļ�ֵ
			value1 = _getch();
			value2 = _getch();
		} while (!(value1 >= '0' && value1 <= '9' || value2 == 72 || value2 == 80 || value1 == 'b'||value1=='B'||value1==27));
		if (value1 == 'b' || value1 == 'B')return 0;  //�û���B
		else if (value1 == 27)return -1;
		else if (value2 == 0) {
			//�û�������Ŀ����
			unsigned int number;
			char c = (char)value1;
			cout << c;
			cin.putback(c);
			cin >> number;
			cin.ignore();
			list<Song>::iterator tar = find_if(first, last, [=](Song s)->bool {return s.getID() == number; });
			if (tar == last) {
				cout << "���������󣬵�ǰҳ�޸���Ŀ��" << endl;
				__delay();
			}
			else {
				if (in_queue.empty())tar->play();
				in_queue.push_back(*tar);
				cout << "���ɹ���" << endl;
				cout << endl << endl;
				cout << "�� C ���������" << endl << "�� ENTER �����û�����" <<endl << "�� ESC ����������" << endl;
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
			case 80:if (page != src.size() / 10 + 1) {//���ж��Ƿ��ܼ����·�
				int count = 0;
				while (count < 10 && first != src.end()) {
					count++; first++;
				}
				page++;
			}break;
			case 72:if (page != 1) {//�ж��Ƿ����Ϸ�
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
		cout << "���޸������У�" << endl;
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
			//�ҵ���ҳ��ʾ���������һ�׵�β��
			count++; last++;
		}
		display1(first, in_queue.end(), page, in_queue.size() / 10 + 1);
		cout << "��ESC�����û�����" << endl;
		cout << "��1--->�ö�����" << endl;
		cout << "��2--->�Ƴ�����" << endl;
		cout << "��3--->�и�" << endl;
		int value1, value2;
		do {//�ų��û��������ļ�ֵ
			value1 = _getch();
			value2 = _getch();
		} while (!(value1 == '1' || value1 == '2' || value1 == '3' || value1 == 27 || value2 == 80 || value2 == 72));
		if (value1 == 27)return;  //�����û�����
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
			case 80:if (page != in_queue.size() / 10 + 1) {//���ж��Ƿ��ܼ����·�
				int count = 0;
				while (count < 10 && first != in_queue.end()) {
					count++; first++;
				}
				page++;
			}break;
			case 72:if (page != 1) {//�ж��Ƿ����Ϸ�
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
	cout << "������Ҫɾ������ID----����-1�����" << endl;
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
			cout << "δƥ�䵽���� ��ȷ�������ڸ�ҳ��" << endl;
			cout << "��������(��y/n)" << endl;
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
	cout << "ɾ���ɹ���" << endl;
	__delay();
}

void User::pushToTop(list<Song>::iterator first, list<Song>::iterator end) {
	cout << "������Ҫ�ö��ĸ���ID----����-1�����" << endl;
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
			cout << "δƥ�䵽���� ��ȷ�������ڸ�ҳ��" << endl;
			cout << "��������(��y/n)" << endl;
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
	cout << "�ö��ɹ���" << endl;
	__delay();
}

void User::mark(Song &song)
{
	cout << endl;
	cout << "�����±��������";
	cout << endl << "*************************************************" << endl;
	cout << "                  ��������" << endl;
	cout << "=================================================" << endl;
	cout << "����������֣�1-5�֣�������Խ�߱�ʾԽ����" << endl;
	int star;
	cin >> star;
	if (star > 5) {
		cout << "����ʮ�ָм���Ĺ������ۣ��ѽ���������--5��" << endl;
		star = 5;
	}
	else if (star < 1) {
		cout << "�÷���һ����ʾ���ǻ��д���ߣ���Ĭ�ϸ���Ϊ0" << endl;
		star = 0;
	}
	else cout << "��л������֣��������������ǸĽ���ָ��" << endl;
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
