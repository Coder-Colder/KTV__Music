#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include"Song.h"
#include<list>
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class HashTable
{
	int prime;
	struct Table {
		list<list<Song>::iterator> line;
	}*table;

public:
	HashTable();
	~HashTable();
	void findAndPushBack(string word, vector<list<Song>::iterator>& v,int mode);
	void add(list<Song>::iterator it,string word);
private:
	int Hash(string word);
};
#endif // !



