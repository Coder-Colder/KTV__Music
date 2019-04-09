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
	unsigned int ID;      //歌曲ID
	string song_name;     //歌曲名
	string singer;        //歌手名
	string abbr_song;     //歌曲名首拼
	string abbr_singer;   //歌手名首拼
	int star;             //歌曲评分
	bool in_playing;      //播放状态
	int count;            //播放次数
	static int num_song;  //歌曲总数
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



