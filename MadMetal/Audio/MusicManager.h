#pragma once

#include "Audio.h"
#include "Factory\GameFactory.h"

class MusicManager
{
private:
	Audio& m_audio;
	std::vector<Sound> m_songs;
	Sound m_currentSong;

	void addSong(Sound song);
	void playSong(int index);
public:
	MusicManager(Audio &audio);
	~MusicManager();

	void changeSong();
	void update();
};

