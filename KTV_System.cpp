#include "KTV_System.h"
#include <conio.h>
#include <iomanip>
#include <Windows.h>

void _delay() {
	cout << endl;
	for (int i = 0; i < 300000000; i++)
		if (i % 100000000 == 0)cout << "\r即将跳转......." << 3 - i / 100000000;
	cout.clear();
	cin.sync();
}

KTV_System::KTV_System() {
	admin_info_file = "Admin.txt";
	user_info_file = "User.txt";
	song_info_file = "Song.txt";
	loadAdminInfo();
	loadUserInfo();
	loadSongInfo();
	for (list<Song>::iterator it = songs.begin(); it != songs.end(); it++) {
		song_table.add(it, it->getSongName());
		singer_table.add(it, it->getSingerName());
	}
}


KTV_System::~KTV_System() {
	recordAdminInfo();
	recordSongInfo();
	recordUserInfo();
}

void KTV_System::run() {
	while (1) {
		system("cls");
		cout << endl << endl << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t|              KTV点歌系统              |" << endl;
		cout << "\t\t\t|=======================================|" << endl;
		cout << "\t\t\t|               <主界面>                |" << endl;
		cout << "\t\t\t|=======================================|" << endl;
		cout << "\t\t\t|             1 管理员登陆              |" << endl;
		cout << "\t\t\t|             2 用户通道                |" << endl;
		cout << "\t\t\t|             3 退出系统                |" << endl;
		cout << "\t\t\t*****************************************" << endl;
		cout << "\t\t\t请选择[ ]\b\b";
		int key;
		do {//确保键值正确
			key = _getche();
			_getche();
		} while (key != '1' && key != '2' && key != '3' );
		switch (key){
		case '1':adminAccess(); break;
		case '2':userAccess(); break;
		case '3':return;
		}
	}
}

void KTV_System::userAccess() {
	system("cls");
	cout << endl << endl << endl;
	cout << "\t\t\t*****************************************" << endl;
	cout << "\t\t\t|              用户通道                 |" << endl;
	cout << "\t\t\t|***************************************|" << endl;
	cout << "\t\t\t|             1 注册新账户              |" << endl;
	cout << "\t\t\t|             2 登陆已有账户            |" << endl;
	cout << "\t\t\t|             3 以访客身份进入          |" << endl;
	cout << "\t\t\t|             4 返回                    |" << endl;
	cout << "\t\t\t*****************************************" << endl;
	cout << "\t\t\t请选择[ ]\b\b";
	int key;
	do {
		key = _getche();
		_getche();
	} while (key != '1' && key != '2'&&key != '3'&&key!='4');
	User *user;
	switch (key) {
	case '2':if (!users.empty()) {
		userLogin();
		break;
	}
			 else cout << endl << endl << "系统暂无可登陆账户！  让我们注册一个吧！" << endl;
		_delay();
	case '1':user = user = User::sign_up();
		users.push_back(user);
		user->main_menu(songs); break;
	case '3':user = new User;
		user->main_menu(songs); break;
	case '4':return;
	}
	
}

void KTV_System::adminLogin() {
	system("cls");
	string temp;
	COORD name_pos, passw_pos,end_pos;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                       管理员登陆                         " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         用户名："; GetConsoleScreenBufferInfo(hOut, &bInfo); name_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	cout << endl;
	GetConsoleScreenBufferInfo(hOut, &bInfo); end_pos = bInfo.dwCursorPosition;
	SetConsoleCursorPosition(hOut, name_pos);
	cin >> temp;
	vector<Admin*>::iterator tar = find_if(administrators.begin(), administrators.end(),
								[=](Admin* p)->bool {return p->getName() == temp; });
	DWORD x;
	while (tar == administrators.end()) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, name_pos, &x);
		SetConsoleCursorPosition(hOut, { name_pos.X + 42,name_pos.Y });
		cout << "× 该用户名不存在！" << endl;
		SetConsoleCursorPosition(hOut, end_pos);
		cout << "是否重新输入(按y/n)" << endl;
		int key;
		do {
			key = _getch();
			_getch();
		} while (key != 'n' && key != 'y' && key != 'N' && key != 'Y');
		if (key == 'n' || key == 'N')return;
		FillConsoleOutputCharacterA(hOut, ' ', 21, end_pos, &x);
		FillConsoleOutputCharacterA(hOut, ' ', 21, { name_pos.X + 42,name_pos.Y }, &x);
		SetConsoleCursorPosition(hOut, name_pos);
		cin >> temp;
		tar = find_if(administrators.begin(), administrators.end(), [=](Admin* p)->bool {return p->getName() == temp; });
	}
	FillConsoleOutputCharacterA(hOut, ' ', 21, { name_pos.X + 42,name_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { name_pos.X + 42,name_pos.Y }); cout << "√" << endl;

	SetConsoleCursorPosition(hOut, passw_pos);
	cin >> temp;
	while (!(*tar)->login(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, passw_pos, &x);
		SetConsoleCursorPosition(hOut, { passw_pos.X + 42,name_pos.Y });
		cout << "×" << endl;
		if ((*tar)->getWrong() == 3)goto END;
		SetConsoleCursorPosition(hOut, end_pos);
		cout << "密码已输入错误"<<(*tar)->getWrong()<<"次(最多3次)" << endl;
		cout << "是否继续登陆(按y/n)" << endl;
		int key;
		do {
			key = _getch();
			_getch();
		} while (key != 'n' && key != 'y' && key != 'N' && key != 'Y');
		if (key == 'n' || key == 'N')return;
		FillConsoleOutputCharacterA(hOut, ' ', 30, end_pos, &x);
		FillConsoleOutputCharacterA(hOut, ' ', 30, { end_pos.X,end_pos.Y + 1 }, &x);
		SetConsoleCursorPosition(hOut, passw_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 21, { passw_pos.X + 42,passw_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos.X + 42,passw_pos.Y }); cout << "√" << endl;
	SetConsoleCursorPosition(hOut, end_pos);
	cout << "登陆成功！" << endl;
	_delay();
	(*tar)->main_menu(songs);
	return;
END:;
	system("cls");
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t           登陆失败！  账号被锁定！                      " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	_delay();
}

void KTV_System::adminAccess() {
	system("cls");
	cout << endl << endl << endl;
	cout << "\t\t\t*****************************************" << endl;
	cout << "\t\t\t|              管理员通道               |" << endl;
	cout << "\t\t\t|***************************************|" << endl;
	cout << "\t\t\t|             1 注册新账户              |" << endl;
	cout << "\t\t\t|             2 登陆已有账户            |" << endl;
	cout << "\t\t\t|             3 返回                    |" << endl;
	cout << "\t\t\t*****************************************" << endl;
	cout << "\t\t\t请选择[ ]\b\b" ;
	int key;
	do {
		key = _getche();
		_getche();
	} while (key != '1' && key != '2'&&key!='3' );
	Admin *admin;
	switch (key) {
	case '2':if (!administrators.empty()) {
		adminLogin();
		break;
	}
			 else cout << endl << endl << "系统暂无可登陆账户！  让我们注册一个吧！" << endl;
		_delay();
	case '1':admin = Admin::sign_up();
		administrators.push_back(admin);
		admin->main_menu(songs); break;
	case '3':return;
	}
}

void KTV_System::userLogin() {
	system("cls");
	string temp;
	COORD name_pos, passw_pos, end_pos;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	cout << endl << endl << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t                        用户登陆                          " << endl;
	cout << "\t\t\t**********************************************************" << endl;
	cout << "\t\t\t         用户名："; GetConsoleScreenBufferInfo(hOut, &bInfo); name_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t         密码："; GetConsoleScreenBufferInfo(hOut, &bInfo); passw_pos = bInfo.dwCursorPosition;
	cout << endl << "\t\t\t**********************************************************" << endl;
	cout << endl;
	GetConsoleScreenBufferInfo(hOut, &bInfo); end_pos = bInfo.dwCursorPosition;
	SetConsoleCursorPosition(hOut, name_pos);
	cin >> temp;
	vector<User*>::iterator tar = find_if(users.begin(), users.end(),
		[=](User* p)->bool {return p->getName() == temp; });
	DWORD x;
	while (tar == users.end()) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, name_pos, &x);
		SetConsoleCursorPosition(hOut, { name_pos.X + 42,name_pos.Y });
		cout << "× 该用户名不存在！" << endl;
		SetConsoleCursorPosition(hOut, end_pos);
		cout << "是否重新输入(按y/n)" << endl;
		int key;
		do {
			key = _getch();
			_getch();
		} while (key != 'n' && key != 'y' && key != 'N' && key != 'Y');
		if (key == 'n' || key == 'N')return;
		FillConsoleOutputCharacterA(hOut, ' ', 21, end_pos, &x);
		FillConsoleOutputCharacterA(hOut, ' ', 21, { name_pos.X + 42,name_pos.Y }, &x);
		SetConsoleCursorPosition(hOut, name_pos);
		cin >> temp;
		tar = find_if(users.begin(), users.end(),[=](User* p)->bool {return p->getName() == temp; });
	}
	FillConsoleOutputCharacterA(hOut, ' ', 21, { name_pos.X + 42,name_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { name_pos.X + 42,name_pos.Y }); cout << "√" << endl;

	SetConsoleCursorPosition(hOut, passw_pos);
	cin >> temp;
	while (!(*tar)->login(temp)) {
		FillConsoleOutputCharacterA(hOut, ' ', 42, passw_pos, &x);
		SetConsoleCursorPosition(hOut, { passw_pos.X + 42,name_pos.Y });
		cout << "×" << endl;
		SetConsoleCursorPosition(hOut, end_pos);
		cout << "密码已输入错误" << endl;
		cout << "是否继续登陆(按y/n)" << endl;
		int key;
		do {
			key = _getch();
			_getch();
		} while (key != 'n' && key != 'y' && key != 'N' && key != 'Y');
		if (key == 'n' || key == 'N')return;
		FillConsoleOutputCharacterA(hOut, ' ', 30, end_pos, &x);
		FillConsoleOutputCharacterA(hOut, ' ', 30, { end_pos.X,end_pos.Y + 1 }, &x);
		SetConsoleCursorPosition(hOut, passw_pos);
		cin >> temp;
	}
	FillConsoleOutputCharacterA(hOut, ' ', 21, { passw_pos.X + 42,passw_pos.Y }, &x);
	SetConsoleCursorPosition(hOut, { passw_pos.X + 42,passw_pos.Y }); cout << "√" << endl;
	SetConsoleCursorPosition(hOut, end_pos);
	cout << "登陆成功！" << endl;
	cin.ignore(1024, '\n');
	_delay();
	(*tar)->main_menu(songs);
}

void KTV_System::loadSongInfo() {
	ifstream f_in;
	f_in.open(song_info_file);
	do {
		while (!f_in.eof() && (f_in.peek() == ' ' || f_in.peek() == '\n'))f_in.get();//排除空白符对文件结束判断的干扰
		if (!f_in.eof()) {
			Song song;
			f_in >> song;
			songs.push_back(song);
		}
	} while (!f_in.eof());
	f_in.close();
}

void KTV_System::loadAdminInfo() {
	ifstream f_in;
	f_in.open(admin_info_file);
	do {
		while (!f_in.eof() && (f_in.peek() == ' ' || f_in.peek() == '\n'))f_in.get();//排除空白符对文件结束判断的干扰
		if (!f_in.eof()) {
			Admin *p_admin = new Admin;
			f_in >> *(p_admin);
			administrators.push_back(p_admin);
		}
	} while (!f_in.eof());
	f_in.close();
}

void KTV_System::loadUserInfo() {
	ifstream f_in;
	f_in.open(user_info_file);
	do {
		while (!f_in.eof() && (f_in.peek() == ' ' || f_in.peek() == '\n'))f_in.get();//排除空白符对文件结束判断的干扰
		if (!f_in.eof()) {
			User *p_user = new User;
			f_in >> *(p_user);
			users.push_back(p_user);
		}
	} while (!f_in.eof());
	f_in.close();
}

void KTV_System::recordSongInfo() {
	ofstream f_out;
	f_out.open(song_info_file);
	list<Song>::iterator cur = songs.begin();
	while (cur != songs.end()) {
		f_out << *cur << endl;
		cur++;
	}
	f_out.close();
}

void KTV_System::recordAdminInfo() {
	ofstream f_out;
	f_out.open(admin_info_file);
	vector<Admin*>::iterator cur = administrators.begin();
	while (cur != administrators.end()) {
		f_out << *(*cur) << endl;
		cur++;
	}
	f_out.close();
}

void KTV_System::recordUserInfo() {
	ofstream f_out;
	f_out.open(user_info_file);
	vector<User*>::iterator cur = users.begin();
	while (cur != users.end()) {
		f_out << *(*cur) << endl;
		cur++;
	}
	f_out.close();
}
