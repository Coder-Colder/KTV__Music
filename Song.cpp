#include "Song.h"

int Song::num_song = 0;

bool isNeeded(string src, string tar)  //Ä£ºı±È½Ï
{
	unsigned int j = 0;
	for (unsigned int i = 0; i < src.size(); i++)
	{
		if (src[i] == tar[j])
		{
			j++;
			if (j == tar.size())break;
		}
	}
	if (j == tar.size())return true;
	else return false;
}

Song::Song() {
	num_song++;
	ID = num_song;
	song_name = "";
	singer = "";
	abbr_song = "";
	abbr_singer = "";
	star = 0;
	in_playing = false;
	count = 0;
}

Song::Song(const Song & song){
	num_song++;
	ID = song.ID;
	song_name = song.song_name;
	singer = song.singer;
	abbr_song = song.abbr_song;
	abbr_singer = song.abbr_singer;
	star = song.star;
	in_playing = song.in_playing;
	count = song.count;
}

Song::Song(const Song && song){
	num_song++;
	ID = song.ID;
	song_name = song.song_name;
	singer = song.singer;
	abbr_song = song.abbr_song;
	abbr_singer = song.abbr_singer;
	star = song.star;
	in_playing = song.in_playing;
	count = song.count;
}

bool Song::isPreciseTarSong(string tar_song) {
	if (song_name == tar_song)return true;
	else return false;
}

bool Song::isAmbiguousTarSong(string tar_song) {
	return isNeeded(abbr_song, tar_song);
}

bool Song::isPreciseTarSinger(string tar_singer) {
	if (singer == tar_singer)return true;
	else return false;
}

bool Song::isAmbiguousTarSinger(string tar_singer) {
	return isNeeded(abbr_singer, tar_singer);
}

/*bool Song::operator== (Song another) {
	if (song_name == another.song_name) return singer == another.singer;
	else return false;
}

bool Song::operator>(Song another) {
	if (singer == another.singer)return abbr_song > another.abbr_song;
	else return singer > another.singer;
}

bool Song::operator<(Song another){
	if (singer == another.singer)return abbr_song < another.abbr_song;
	else return singer < another.singer;
}
*/
Song &Song::operator=(const Song && song) {
	num_song++;
	ID = song.ID;
	song_name = song.song_name;
	singer = song.singer;
	abbr_song = song.abbr_song;
	abbr_singer = song.abbr_singer;
	star = song.star;
	in_playing = song.in_playing;
	count = song.count;
	return *this;
}

Song &Song::operator=(const Song & song) {
	num_song++;
	ID = song.ID;
	song_name = song.song_name;
	singer = song.singer;
	abbr_song = song.abbr_song;
	abbr_singer = song.abbr_singer;
	star = song.star;
	in_playing = song.in_playing;
	count = song.count;
	return *this;
}

bool operator==(const Song one, const Song another){
	if (one.song_name == another.song_name) return one.singer == another.singer;
	else return false;
}

bool operator>(const Song one, const Song another){
	if (one.singer == another.singer)return one.abbr_song > another.abbr_song;
	else return one.singer > another.singer;
}

bool operator<(const Song one, const Song another){
	if (one.singer == another.singer)return one.abbr_song < another.abbr_song;
	else return one.singer < another.singer;
}

istream & operator>>(istream & in, Song & song) {
	string s;
	getline(in, s);
	if (s.find('|') == string::npos) {
		istringstream iss(s);
		iss >> song.song_name;
		iss >> song.singer;
		iss >> song.abbr_song;
		while (!iss.eof() && (iss.peek() == ' ' || iss.peek() == '\n'))iss.get();
		if (!iss.eof())iss >> song.abbr_singer;
			
	}
	else {
		istringstream iss(s);
		getline(iss, song.song_name, '|');
		getline(iss, song.singer, '|');
		getline(iss, song.abbr_song, '|');
		while (!iss.eof() && (iss.peek() == ' ' || iss.peek() == '\n'))iss.get();//·ÀÖ¹¿Õ°×·û¸ÉÈÅÁ÷½áÊø·ûµÄÅĞ¶Ï
		if (!iss.eof())getline(iss, song.abbr_singer, '|');
	}
	return in;
}

ostream & operator<<(ostream & out, const Song & song)
{
	out << song.ID << "\t\t" << song.song_name << "\t\t" << song.singer << "\t\t" << song.star ;
	return out;
}

ifstream & operator>>(ifstream & f_in, Song & song)
{
	string s;
	getline(f_in, s);
	if (s.find('|') == string::npos) {
		istringstream iss(s);
		iss >> song.song_name;
		iss >> song.singer;
		iss >> song.abbr_song;
		while (!iss.eof() && (iss.peek() == ' ' || iss.peek() == '\n'))iss.get();
		if (!iss.eof())iss >> song.abbr_singer;
	}
	else {
		istringstream iss(s);
		stringstream trans;
		s.clear();
		getline(iss, s, '|');
		trans << s;
		trans >> song.ID;
		s.clear();
		getline(iss, s, '|');
		trans << s;
		trans >> song.star;
		s.clear();
		getline(iss, s, '|');
		trans << s;
		trans >> song.count;
		getline(iss, song.song_name, '|');
		getline(iss, song.singer, '|');
		getline(iss, song.abbr_song, '|');
		while (!iss.eof() && (iss.peek() == ' ' || iss.peek() == '\n'))iss.get();//·ÀÖ¹¿Õ°×·û¸ÉÈÅÁ÷½áÊø·ûµÄÅĞ¶Ï
		if (!iss.eof())getline(iss, song.abbr_singer,'|');
	}
	return f_in;
}

ofstream & operator<<(ofstream & f_out, const Song & song)
{
	f_out << song.ID << '|' << song.star << '|' << song.count << '|' << song.song_name 
		<< '|' << song.singer << '|' << song.abbr_song << '|';
	if (song.abbr_singer != "")f_out << song.abbr_singer << '|';
	return f_out;
}

istringstream & operator>>(istringstream & in, Song & song)
{
	string s;
	getline(in, s);
	if (s.find('|') == string::npos) {
		istringstream iss(s);
		iss >> song.song_name;
		iss >> song.singer;
		iss >> song.abbr_song;
		while (!iss.eof() && (iss.peek() == ' ' || iss.peek() == '\n'))iss.get();
		if (!iss.eof())iss >> song.abbr_singer;
	}
	else {
		istringstream iss(s);
		getline(iss, song.song_name, '|');
		getline(iss, song.singer, '|');
		getline(iss, song.abbr_song, '|');
		while (!iss.eof() && (iss.peek() == ' ' || iss.peek() == '\n'))iss.get();//·ÀÖ¹¿Õ°×·û¸ÉÈÅÁ÷½áÊø·ûµÄÅĞ¶Ï
		if (!iss.eof())getline(iss, song.abbr_singer, '|');
	}
	return in;
}
