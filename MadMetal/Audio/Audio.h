#pragma once
#include "Libraries/sdl/SDL.h"
#include "Libraries/sdl/SDL_mixer.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "Sound.h"
#include "Objects\Object.h"
#define NUM_CHANNELS 100

class AudioChannel;
class Car;

class Audio
{
private:
	std::vector<Mix_Chunk *> m_chunkLibrary;
	std::vector<Mix_Music *> m_musicLibrary;
	std::vector<Car *> m_listeners;
	static bool m_musicPlaying;


public:
	std::vector<AudioChannel *> m_audioChannels;
	Audio()
	{
		
		SDL_Init(SDL_INIT_AUDIO);
		SDL_Init(MIX_INIT_MP3);
		SDL_Init(MUS_MP3);
		SDL_Init(MUS_WAV);
		SDL_Init(MUS_OGG);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Error: " << Mix_GetError() << std::endl;
			
		}
		//set max amount of channels to mix
		Mix_AllocateChannels(NUM_CHANNELS);
		//todo:: load from file?
		initializeMusicLibrary();
		initializeChunkLibrary();
		Mix_HookMusicFinished(setMusicFinished);
	}

	~Audio()
	{
		for (int i = 0; i < m_audioChannels.size(); i++)
		{
			delete m_audioChannels[i];
		}
		m_audioChannels.clear();

		for (int i = 0; i < m_chunkLibrary.size(); i++)
		{
			Mix_FreeChunk(m_chunkLibrary[i]);
		}
		m_chunkLibrary.clear();

		for (int i = 0; i < m_musicLibrary.size(); i++)
		{
			Mix_FreeMusic(m_musicLibrary[i]);
		}
		m_musicLibrary.clear();

		Mix_CloseAudio();
		SDL_Quit();
	}

	void assignListener(Car* listener) { m_listeners.push_back(listener); }
	void clearListeners() { m_listeners.clear(); }
	void removeListener();
	void stopSources();
	void stopSource(int channel);
	void pauseSources();
	void resumeSources();
	void initializeChunkLibrary(char * fileToLoad = "Audio/ChunkLibrary.txt");
	void initializeMusicLibrary(char * fileToLoad = "Audio/MusicLibrary.txt");
	void queAudioSource(PxRigidActor * sourcePosition, Sound toPlay, float volumeScalar = 1, bool updatePosition = false, int loopCount = 0);
//	bool queAudioSource(int sourceID);
	void update();
	void playMusic(Sound toPlay, int loopCount = -1);
	void stopMusic();
	void setMusicVolume(int value);
	void resetMusicVolume();

	static void setMusicFinished();
	static bool getMusicFinished();

};





class AudioChannel
{
private:
	
	PxRigidActor * m_audioPosition;
	int m_playingChannel;
	bool m_updatePosition;
	float m_volumeScalar;
public:
	AudioChannel(PxRigidActor * position, bool updatePosition, float volumeScalar) : m_audioPosition(position),  m_updatePosition(updatePosition), m_volumeScalar(volumeScalar){}
	~AudioChannel()
	{
		
	}

	bool setAudioPosition(std::vector<Car *> listeners);
	bool needsUpdate(){ return m_updatePosition; }
	void setChannel(int channel)
	{
		m_playingChannel = channel;
	}
	int getChannel(){ return m_playingChannel; }
};




