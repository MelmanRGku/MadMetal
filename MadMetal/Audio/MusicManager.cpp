#include "MusicManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

MusicManager::MusicManager(Audio &audio) : m_audio(audio)
{
	addSong(TrackMusicSound());
	addSong(VengefulOneSong());
	addSong(NumaNumaYeiSong());
}


MusicManager::~MusicManager()
{
}


void MusicManager::addSong(Sound song) {
	m_songs.push_back(song);	
}

void MusicManager::playSong(int index) {
	m_audio.playMusic(m_songs.at(index), 1);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_UI_DISTURBED_SONG, NULL, NULL, NULL);
}

void MusicManager::changeSong() {
	srand(time(NULL));
	int songIndex = 0;
	do {
		songIndex = rand() % m_songs.size();
	} while (songIndex == m_currentSong.getLibraryIndex());
	m_currentSong = m_songs.at(songIndex);
	playSong(songIndex);
}

void MusicManager::update() {
	if (Audio::getMusicFinished()) {
		changeSong();
	}
}