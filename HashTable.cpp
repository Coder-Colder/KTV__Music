#include "HashTable.h"



HashTable::HashTable()
{
	prime = 233;
	table = new Table[prime];
}


HashTable::~HashTable()
{
	delete[]table;
}

void HashTable::findAndPushBack(string word, vector<list<Song>::iterator>& v,int mode)
{
	int index = Hash(word);
	v.clear();
	if (mode == 1) {
		for (list<list<Song>::iterator>::iterator it = table[index].line.begin(); it != table[index].line.end(); it++) {
			if ((*it)->getSongName() == word)v.push_back(*it);
		}
	}
	else if (mode == 2) {
		for (list<list<Song>::iterator>::iterator it = table[index].line.begin(); it != table[index].line.end(); it++) {
			if ((*it)->getSingerName() == word)v.push_back(*it);
		}
	}
}

void HashTable::add(list<Song>::iterator it, string word)
{
	int index = Hash(word);
	table[index].line.push_back(it);
}

int HashTable::Hash(string word)
{
	int res = 0;
	for (const char *c = word.c_str(); *c != '\0'; ++c) {
		res = res * 26 + ((*c - 'a')>0? (*c - 'a'):-(*c - 'a'));
		res = res % prime;
	}
	return res;
}
