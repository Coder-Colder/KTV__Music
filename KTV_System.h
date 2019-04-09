#pragma once
#ifndef KTV_SYSTEM_H
#define KTV_SYSTEM_H

#include"Song.h"
#include"Admin.h"
#include"User.h"
#include<algorithm>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include"HashTable.h"

using namespace std;

class KTV_System
{
	vector<Admin*> administrators;    //保存所有管理员指针
	vector<User*>  users;             //保存所有用户指针
	list<Song>     songs;             //保存全部歌曲列表
	HashTable song_table;
	HashTable singer_table;
	string admin_info_file;
	string user_info_file;
	string song_info_file;
public:
	KTV_System();
	~KTV_System();
	void run();
private:
	void userAccess();
	void userLogin();
	void adminAccess();
	void adminLogin();
	void loadSongInfo();
	void loadAdminInfo();
	void loadUserInfo();
	void recordSongInfo();
	void recordAdminInfo();
	void recordUserInfo();
};

#endif