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
		if (i % 100000000 == 0)cout << "\r������ת......." << 3 - i / 100000000;
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
		cout << "���������������3�Σ��˻��ѱ�������ʧȥ����Ȩ�ޣ�" << endl;
		cout << "��ǰ���˻���֤����--����������˳�����" << endl;
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
		cout << "\t\t\t|             <����Ա����>              |" << endl;
		cout << "\t\t\t|=======================================|" << endl;
		cout << "\t\t\t|             1 ���и���                |" << endl;
		cout << "\t\t\t|             2 ��Ӹ���                |" << endl;
		cout << "\t\t\t|             3 �����������            |" << endl;
		cout << "\t\t\t|             4 ɾ������                |" << endl;
		cout << "\t\t\t|             5 ��������                |" << endl;
		cout << "\t\t\t|             6 �޸�����                |" << endl;
		cout << "\t\t\t|            ESC �˷�������             |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		int key;
		do {//ȷ����ֵ��ȷ
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
	cout << "\t\t\t                       ����Աע��                         " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         �û�����"; GetConsoleScreenBufferInfo(hOut, &bInfo); name_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         ���룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         ȷ�����룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         �ܱ��ֻ�:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	SetConsoleCursorPosition(hOut, name_pos);
	cin >> temp;
	DWORD x;
	while (!legalName(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 41, name_pos, &x);
		SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y });
		cout << "����ԱID������20���ַ���ֻ���ɴ�Сд��ĸ���������,����������" << endl;
		SetConsoleCursorPosition(hOut, name_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { name_pos.X + 41,name_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { name_pos.X + 41,name_pos.Y }); cout << "��" << endl;
	p->name = temp;

	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	while (!legalPassw(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 43, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 43,passw_pos1.Y });
		cout << "���벻����12���ַ�������ͬʱ������Сд��ĸ������,����������" << endl;
		SetConsoleCursorPosition(hOut, passw_pos1);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 60, { passw_pos1.X + 43,passw_pos1.Y }, &x);
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
	FillConsoleOutputCharacterA(hOut, ' ', 19, { passw_pos2.X + 39,passw_pos2.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos2.X + 39,passw_pos2.Y }); cout << "��" << endl;
	SetConsoleCursorPosition(hOut, phone_pos);

	cin >> p->phone;
	SetConsoleCursorPosition(hOut, { phone_pos.X + 40,phone_pos.Y }); cout << "��" << endl;
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
	cout << "\t\t\t                       ��������                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         ԭ���룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos1 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         �����룺"; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos2 = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         ȷ��������:"; GetConsoleScreenBufferInfo(hOut, &bInfo); phone_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	SetConsoleCursorPosition(hOut, passw_pos1);
	cin >> temp;
	DWORD x;
	while (temp != password) {
		FillConsoleOutputCharacterA(hOut, ' ', 44, passw_pos1, &x);
		SetConsoleCursorPosition(hOut, { passw_pos1.X + 44,passw_pos1.Y });
		cout << "���������  " <<"ʣ��"<<3-(++wrong)<<"��"<< endl;
		SetConsoleCursorPosition(hOut, passw_pos1);
		if (wrong == 3)goto END;
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 20, { passw_pos1.X + 44,passw_pos1.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos1.X + 44,passw_pos1.Y }); cout << "��" << endl;

	SetConsoleCursorPosition(hOut, passw_pos2);
	cin >> temp;
	while (!legalPassw(temp)) {
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
	while (temp!=password) {
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
	delay();
	return 0;
END:
	system("cls");
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                �˻�������                                " << endl;
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
		cout << "��ESC���������棬��ENTER���ع���Ա����" << endl;
		int value1, value2;
		do {//�ų��û��������ļ�ֵ
			value1 = _getch();
			value2 = _getch();
		} while (!(value2 == 72 || value2 == 80 || value1 == 13 || value1 == 27));
		if (value1 == 13)return 0;
		else if (value1 == 27)return -1;
		else {
			switch(value2) {
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

void Admin::showSong(list<Song>::iterator first, list<Song>::iterator end, int page, int total_page, int num){
	cout << endl << endl;
	cout << setfill('*') << setw(114) << '*' << endl;
	cout << setfill(' ') << '|' << std::right << setw(61) << "<ȫ������>" << setw(52) << '|' << endl;
	cout << '|' << setfill('=') << setw(113) << '|' << endl;
	cout << '|' << setfill(' ') << " ����ID " << std::left << setw(28) << "  ������" << setw(19) << " ������" << setw(15) << "��������ƴ" << setw(12)
		<< "��������ƴ" << setw(10) << "��������" << setw(10) << "���Ŵ���" << setw(10) << "����״̬" << '|' << endl;
	for (int i = 0; i < num&&first!=end; i++) {
		cout << "|" << std::right << setw(6) << first->ID << "  " << std::left << setw(28) << first->song_name << setw(20) << first->singer
			<< setw(15) << first->abbr_song << setw(14) << first->abbr_singer << setw(9) << first->star << setw(8)
			<< first->count << setw(10) << (first->in_playing ? "���ڲ���" : "δ�ڲ���") << '|' << endl;
		first++;
	}
	cout << setfill('*') << setw(114) << '*' << endl;
	cout << setfill(' ') <<std::right <<"��" << page << "ҳ ��" << total_page << "ҳ  ��һҳ(��) ��һҳ(��)" << setw(114) << endl;
}

void Admin::mergeSongList(list<Song>& src,list<Song>& newlist) {
	list<Song>:: iterator  it = newlist.begin();
	while (it != newlist.end()) {                                     //�����ظ��ĸ�������src��
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
	cout << "�����������Ϣ(������|������|��������ƴ|��������ƴ|)------����-1�˳�" << endl;
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
		cout << "������ӳɹ���" << endl;
		delay();
	}
	else {
		cout << "�������ʧ�ܣ�   �����Ѵ��ڣ�" << endl;
		delay();
	}
}

void Admin::addSomeSong(list<Song>& src){
	system("cls");
	cin.sync();
	cout << "����������ļ���---------����Ϊ-1������һ�����" << endl;
	string file_name;
	cin >> file_name;
	if (file_name == "-1") {
		cin.ignore();
		return;
	}
	cin.ignore();
	ifstream f_in;
	f_in.open(file_name);
	while (!f_in.is_open()) {  //ȷ���ļ���ȷ��
		cout << "�ļ���ʧ�ܣ���ȷ���Ƿ������ȷ·��" << endl;
		cout << "����������ļ���---------����Ϊ-1������һ�����" << endl;
		getline(cin, file_name);
		if (file_name == "-1") {
			cin.ignore();
			return;
		}
		f_in.open(file_name);
	}
	list<Song>new_song_list;
	while (!f_in.eof()) {  //�������
		Song newsong;
		f_in >> newsong;
		new_song_list.push_back(newsong);
		while (!f_in.eof() && (f_in.peek() == ' ' || f_in.peek() == '\n'))f_in.get();//��ֹ�ļ�β�հ׷����Ŷ��ļ��������ж�
	}
	f_in.close();
	int total = new_song_list.size();
	mergeSongList(src, new_song_list);
	cout << "�ܼ�" << total << "�׸���" << endl;
	if (!new_song_list.empty()) {
		cout << "����" << new_song_list.size() << "�׸�������ʧ�ܣ�" << endl;
		cout << "ԭ���������Ѿ����ڣ�" << endl;
		cout << "δ����������£�" << endl;
		list<Song>::iterator cur = new_song_list.begin();
		int count = 1;
		while (cur != new_song_list.end()) {
			cout << count<< " " << cur->song_name << "\t\t" << cur->singer << endl;
			count++; cur++;
		}
		cout << "��ENTER������" << endl;
		cin.get();
	}
	cout << "�������������" << endl;
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
			//�ҵ���ҳ��ʾ���������һ�׵�β��
			count++; last++;
		}
		showSong(first, src.end(),page, src.size() / 10 + 1);
		cout << "�ҵ�Ҫɾ������Ŀ�������ż���ɾ��-----ESC���ع���Ա���桢��B�򷵻���һ�����" << endl;
		int value1, value2;
		do {//�ų��û��������ļ�ֵ
			value1 = _getch();
			value2 = _getch();
		} while (!(value1 >= '0' && value1 <= '9' || value2 == 72 || value2 == 80 || value1 == 'b'|| value1 == 'B' || value1 == 27));
		if (value1 == 'b' || value1 == 'B')return 0;  //�û�����B
		else if (value1 == 27)return -1;  //�û�����ESC
		else if (value2 == 0) {   
			//�û�������Ŀ����
			unsigned int number;
			char c = (char)value1;
			cout << c;         
			cin.putback(c);         //����_getch()����һ���ַ�
			cin >> number;
			cin.ignore();
			list<Song>::iterator tar = find_if(first, last, [=](Song s)->bool {return s.getID() == number; });
			if (tar == last) cout << "���������󣬵�ǰҳ�޸���Ŀ��" << endl;
			else {
				if (tar == first) {
					first++;
					if (subsConfirm(src, tar)) cout << "ɾ���ɹ���" << endl;
					else first--;
				}
				else if (subsConfirm(src, tar)) cout << "ɾ���ɹ���" << endl;
			}
			delay();
		}
		else {   //�û���ҳ
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

int Admin::substract2(list<Song>& src)
{
	while (1) {
		system("cls");
		cin.sync();
		cout << "������Ҫɾ���ĸ�����------����-1�򷵻���һ�����" << endl;
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
			cout << "δ�ҵ�ƥ���������ȷ������������Ƿ���ȷ �� �ø�������������" << endl;
			cout << "����������߽���(��y/n)--------��ESCֱ�ӷ��ع���Ա����" << endl;
			switch (pressKey1()){
			case 'n':case'N':return 0;
			case 27:return -1;
			}
			delay();
		}
		else {
			while (to_delete.size() != 0) {
				system("cls");
				cout << "�鵽�ĸ������£�" << endl;
				for (unsigned int i = 0; i < to_delete.size(); i++)
					cout << to_delete[i]->ID << "  " << to_delete[i]->song_name << "  " << to_delete[i]->singer << endl;
				cout << "����������ɾ����Ӧ����" << endl;
				cout << "����0����ɾ��" << endl;
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
					cout << "��Ŀ����������" << endl;
					cout << "��������(��y/n)-------��ESCֱ�ӷ��ع���Ա�˵�" << endl;
					switch (pressKey1()) {
					case 'n':case'N':return 0;
					case 27:return -1;
					}
				}
				else {
					if (subsConfirm(src, *i)) {//ȷ��ɾ��
						cout << "ɾ���ɹ���" << endl;
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
		cout << "������Ҫɾ���ĸ�����------����-1���������ɾ��" << endl;
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
			cout << "δ�ҵ�ƥ���������ȷ������������Ƿ���ȷ �� ���������޸ø��ֵ���Ŀ" << endl;
			cout << "����������߽���(��y/n)--------��ESCֱ�ӷ��ع���Ա����" << endl;
			switch (pressKey1()) {
			case 'n':case'N':return 0;
			case 27:return -1;
			}
			delay();
		}
		else {
			while (to_delete.size() != 0) {
				system("cls");
				cout << "�鵽�ĸ������£�" << endl;
				for (unsigned int i = 0; i < to_delete.size(); i++)
					cout << to_delete[i]->ID << "  " << to_delete[i]->song_name << "  " << to_delete[i]->singer << endl;
				cout << "����������ɾ����Ӧ����" << endl;
				cout << "����0����ɾ��" << endl;
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
					cout << "��Ŀ����������" << endl;
					cout << "��������(��y/n)-------��ESCֱ�ӷ��ع���Ա�˵�" << endl;
					switch (pressKey1()) {
					case 'n':case'N':return 0;
					case 27:return -1;
					}
				}
				else if (subsConfirm(src, *i)) {//ȷ��ɾ��
					cout << "ɾ���ɹ���" << endl;
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
		cout << "������Ҫ���ҵ���ƴ------����-1���������ɾ��" << endl;
		string name;
		cin >> name;
		if (name == "-1") {
			cin.ignore();
			return 0;
		}
		vector<list<Song>::iterator> to_delete_by_song;
		vector<list<Song>::iterator> to_delete_by_singer;
		to_delete_by_song.clear();
		to_delete_by_singer.clear();						//ģ�����Ҹ���
		findSongAndPushBack(src, to_delete_by_song, [=](Song s)->bool {return s.isAmbiguousTarSong(name); });
		findSongAndPushBack(src, to_delete_by_singer, [=](Song s)->bool {return s.isAmbiguousTarSinger(name); });
		if (!to_delete_by_song.empty() || !to_delete_by_singer.empty()) {
			while (!to_delete_by_song.empty() || !to_delete_by_singer.empty()) {
				system("cls");
				vector<list<Song>::iterator>::iterator i1 = to_delete_by_song.begin();
				vector<list<Song>::iterator>::iterator i2 = to_delete_by_singer.begin();
				if (!to_delete_by_song.empty()){
					cout << "����������ѯ���" << endl;
					for (; i1 != to_delete_by_song.end(); i1++)
						cout << (*i1)->ID<<"  "<<(*i1)->song_name<<"  "<<(*i1)->singer << endl;
				}
				if (!to_delete_by_singer.empty()) {
					cout << "����������ѯ���" << endl;
					for (; i2 != to_delete_by_singer.end(); i2++)
						cout << (*i2)->ID << "  " << (*i2)->song_name << "  " << (*i2)->singer << endl;
				}
				cout << "���������IDɾ����Ӧ����" << endl;
				cout << "����0����" << endl;
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
						cout << "��Ŀ����������" << endl;
						cout << "��������(��y/n)-------��ESCֱ�ӷ��ع���Ա�˵�" << endl;
						switch (pressKey1()) {
						case 'n':case'N':return 0;
						case 27:return -1;
						}
					}
					else if (subsConfirm(src, *tar)) {//ȷ��ɾ��
						cout << "ɾ���ɹ���" << endl;
						to_delete_by_singer.erase(tar);
						delay();
					}
				}
				else if (subsConfirm(src, *tar)) {//ȷ��ɾ��
						cout << "ɾ���ɹ���" << endl;
						to_delete_by_song.erase(tar);
						delay();
				}
			} 
		}
		else{
			cout << "���ź���û�в鵽�����Ŀ" << endl;
			cout << "��������(��y/n)-------��ESCֱ�ӷ��ع���Ա�˵�" << endl;
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
		cout << "\t\t\t|            <����ɾ������>             |" << endl;
		cout << "\t\t\t|=======================================|" << endl;
		cout << "\t\t\t|            1 �߲鿴��ɾ               |" << endl;
		cout << "\t\t\t|            2 ��������ɾ��             |" << endl;
		cout << "\t\t\t|            3 ��������ɾ��             |" << endl;
		cout << "\t\t\t|            4 ģ������Ҫɾ������Ŀ     |" << endl;
		cout << "\t\t\t|          ENTER ����ɾ��               |" << endl;
		cout << "\t\t\t|          ESC   �˷�������             |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		int key;
		do {//ȷ����ֵ��ȷ
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
	cout << "Ҫɾ���ĸ�����" << tar->song_name << "   " << tar->singer << endl;
	cout << "ȷ��ɾ��(��y/n)" << endl;
	int key;
	do {
		key = _getch();
		_getch();
	} while (key != 89 && key != 78 && key != 110 && key != 121 && key != 27);
	if (key == 89 || key == 121) {//ȷ��ɾ��
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
	cout << "\t\t\t|            <�����������>             |" << endl;
	cout << "\t\t\t|             1 ��������                |" << endl;
	cout << "\t\t\t|             2 ��������                |" << endl;
	cout << "\t\t\t|             3 �����Ŵ���              |" << endl;
	cout << "\t\t\t|             4 ����������              |" << endl;
	cout << "\t\t\t|           ENTER ��������              |" << endl;
	cout << "\t\t\t|           ESC   �˷�������            |" << endl;
	cout << "\t\t\t*****************************************" << endl;
	int key;
	do {//ȷ����ֵ��ȷ
		key = _getch();
		_getch();
	} while (key != '1' && key != '2' && key != '3' && key != '4' && key != 27 && key != 13);
	switch (key) {
	case '1':src.sort([](Song s1, Song s2)->bool {return s1.getSingerName() < s2.getSingerName(); });
		cout << "����ɹ�!"<<endl; break;
	case '2':src.sort([](Song s1, Song s2)->bool {return s1.getSongName() < s2.getSongName(); });
		cout << "����ɹ�!" << endl; break;
	case '3':src.sort([](Song s1, Song s2)->bool {return s1.getCount() < s2.getCount(); });
		cout << "����ɹ�" << endl; break;
	case '4':src.sort([](Song s1, Song s2)->bool {return s1.getStar() < s2.getStar(); });
		cout << "����ɹ�" << endl; break;
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
