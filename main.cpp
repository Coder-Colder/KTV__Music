#include<iostream>
#include<fstream>
using namespace std;
#include<list>
#include<vector>
#include"Song.h"
#include<conio.h>
#include"KTV_System.h"

int main()
{
	KTV_System *system=new KTV_System;
	system->run();
	//list<Song>songs;
	//ifstream f_in;
	//f_in.open("Song.txt");
	//do {
	//	while (!f_in.eof() && (f_in.peek() == ' ' || f_in.peek() == '\n'))f_in.get();//ÅÅ³ı¿Õ°×·û¶ÔÎÄ¼ş½áÊøÅĞ¶ÏµÄ¸ÉÈÅ
	//	if (!f_in.eof()) {
 //			Song song;
	//		f_in >> song;
	//		songs.push_back(song);
	//	}
	//} while (!f_in.eof());
	//f_in.close();
	///*User user;
	//user.main_menu(songs);*/
	//Admin admin;
	//admin.main_menu(songs);
	system->~KTV_System();
	return 0;
}

















































//************************  list and string ³õÌ½  *******************************//

/*list<string>hahaha;
string a;
hahaha.push_back("·Å¸öÆ¨");
cout << *hahaha.begin() << endl;
cout << hahaha.size() << endl;
cin >> a;
hahaha.push_back(a);
cout<<a.size();
for (unsigned int i = 0; i < a.size(); i++)
	cout << a[i]<<" ";
cout << endl;
vector< list<string>::iterator>pointer;
for (list<string>::iterator cur = hahaha.begin(); cur != hahaha.end(); cur++)
{
	cout << *cur << endl;
	pointer.push_back(cur);
}
for (unsigned int i = 0; i < pointer.size(); i++)
	cout << *pointer[i] << endl;
string b;
cin >> b;
if (isNeeded(a, b))cout << "yes" << endl;
else cout << "no" << endl;*/

//****************************************************************************//


//************************** istream ³õÌ½ ************************************//

/*fstream f_in;
f_in.open(".\\test1.txt", fstream::out);
f_in << "hello world|My name is liyi|" << endl;
f_in.close();
f_in.open(".\\test1.txt", fstream::out | fstream::in);
string file_in;
string s;
char temp[256];
f_in.getline(temp, 256);
file_in.assign(temp);
s.assign(temp, file_in.find('|'));
cout << s;
f_in.close();*/

//***************************************************************************//