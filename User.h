#pragma once
#ifndef USER_H
#define USER_H

#include<list>
#include<vector>
#include<algorithm>
#include"Song.h"
#include<fstream>
#include<string>

using namespace std;

class User
{
	string name;            //用户名
	string password;        //密码
	unsigned int phone;	    //密保手机
	list<Song> in_queue;    //播放队列
	list<Song> out_queue;   //已唱队列
public:
	User();
	~User() {}
	bool login(string passw){ return password == passw; }
	string getName() {return name;}
	void main_menu(list<Song>& src);
	friend ifstream&operator>>(ifstream&f_in, User &user);
	friend ofstream&operator<<(ofstream&f_out, const User&user);
	static User*sign_up();
private:
	template<typename pfunc>
	void findSongAndPushBack( list<Song>&src, vector<list<Song>::iterator> &v, pfunc const &pf);
	void resetPassword();
	int pickSongBySinger( list<Song>& src);
	int pickSongBySongName( list<Song>& src);
	int pickSongByAbbr(list<Song>& src);
	int pickSongFromAll( list<Song> & src);
	void display1(list<Song>::iterator first, list<Song>::iterator end, int page, int total_page, int num=10);
	void display2(vector<list<Song>::iterator>::iterator first, vector<list<Song>::iterator>::iterator end);
	void cutSong();
	void showInQueue();
	void substractSong(list<Song>::iterator& first, list<Song>::iterator end);
	void pushToTop(list<Song>::iterator first, list<Song>::iterator end);
	void mark(Song&song);
};


ifstream&operator>>(ifstream&f_in, User &user);
ofstream&operator<<(ofstream&f_out, const User&user);

#endif // !USER_H



