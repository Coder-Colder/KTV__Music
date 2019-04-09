#pragma once
#ifndef  SONG_H
#define  SONG_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Song
{
	unsigned int ID;      //����ID
	string song_name;     //������
	string singer;        //������
	string abbr_song;     //��������ƴ
	string abbr_singer;   //��������ƴ
	int star;             //��������
	bool in_playing;      //����״̬
	int count;            //���Ŵ���
	static int num_song;  //��������
	friend class Admin;
public:
	Song();
	~Song() { num_song--; }
	Song(const Song & song);
	Song(const Song && song);
	bool isPreciseTarSong(string tar_song);
	bool isAmbiguousTarSong(string tar_song);
	bool isPreciseTarSinger(string tar_singer);
	bool isAmbiguousTarSinger(string tar_singer);
	bool isOn() const { return in_playing; }
	void play() { in_playing = true; }
	void setStar(int star) { Song::star = star; }
	string getSongName() const { return song_name; }
	string getSingerName() const { return singer; }
	unsigned int getID() const { return ID; }
	int getCount() const { return count; }
	int getStar()const { return star; }
	Song &operator=(const Song && song);
	Song &operator=(const Song & song);
	friend bool operator == (const Song one, const Song another);
	friend bool operator > (const Song one, const Song another);
	friend bool operator < (const Song one, const Song another);
	friend istream&operator>>(istream&in, Song&song);
	friend ostream&operator<<(ostream&out, const Song&song);
	friend ifstream&operator>>(ifstream&f_in, Song&song);
	friend ofstream&operator<<(ofstream&f_out, const Song&song);
	friend istringstream&operator>>(istringstream&in, Song &song);
};

bool operator == (Song one, Song another);
bool operator > (Song one, Song another);
bool operator < (Song one, Song another);


#endif // ! SONG_H



