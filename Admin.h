#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include"Song.h"
#include<list>
#include<vector>
#include<sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

class Admin
{
	string name;            //用户名
	string password;        //密码
	unsigned int phone;     //密保手机
	int wrong;              //密码输入错误次数
public:
	Admin();
	~Admin() {}
	bool login(string passw);
	string getName() { return name; }
	unsigned int getPhone() { return phone; }
	int getWrong() { return wrong; }
	void main_menu(list<Song>&src);
	friend ifstream&operator>>(ifstream&f_in, Admin&admin);
	friend ofstream&operator<<(ofstream&f_out, const Admin&admin);
	static Admin*sign_up();
private:
	int changePassword();
	int display(list<Song>&src);
	void showSong(list<Song>::iterator first, list<Song>::iterator end,int page,int total_page, int num = 10);
	void mergeSongList(list<Song>&src,list<Song>&newlist);
	void addOneSong(list<Song>&src);
	void addSomeSong(list<Song>&src);
	int substractSong(list<Song>&src);
	bool subsConfirm(list<Song>&src, list<Song>::iterator tar);
	int substract1(list<Song>&src);
	int substract2(list<Song>&src);
	int substract3(list<Song>&src);
	int substract4(list<Song>&src);
	int rankSong(list<Song>&src);
	void modifySong(list<Song>&src);
	template<typename pfunc>
	void findSongAndPushBack(list<Song>&src,vector< list<Song>::iterator> &v, pfunc const &pf);
	void updateSongID(list<Song>::iterator first, list<Song>::iterator end,int number_of_fisrt);
};

ifstream&operator>>(ifstream&f_in, Admin&admin);
ofstream&operator<<(ofstream&f_out, const Admin&admin);

#endif
