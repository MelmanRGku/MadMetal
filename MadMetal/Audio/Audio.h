#pragma once
#include "Libraries/sdl/SDL.h"
#include "Libraries/sdl/SDL_mixer.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "Objects\Object.h"
#include "Sound.h"
#define NUM_CHANNELS 50

class AudioChannel;
class Sound;

class Audio
{
private:
	
	std::vector<Mix_Chunk *> m_library;
	PxRigidActor * m_listener;


public:
	std::vector<AudioChannel *> m_audioChannels;
	Audio()
	{
		SDL_Init(SDL_INIT_AUDIO);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Error: " << Mix_GetError() << std::endl;
			
		}
		//set max amount of channels to mix
		Mix_AllocateChannels(NUM_CHANNELS);
		//todo:: load from file?
		initializeLibrary("");
	}

	~Audio()
	{
		Mix_CloseAudio();
		SDL_Quit();
	}

	void assignListener(PxRigidActor* listener) { m_listener = listener; }
	void removeListener();
	void stopSources();
	void stopSource(int channel);
	void pauseSources();
	void resumeSources();
	void initializeLibrary(char * fileToLoad);
	void queAudioSource(PxRigidActor * sourcePosition, Sound& toPlay, int loopCount = 0);
	void update();

};





class AudioChannel
{
private:
	int &m_channelNum; 
	PxRigidActor * m_audioPosition;
public:
	AudioChannel(PxRigidActor * position, int &channel) : m_audioPosition(position), m_channelNum(channel){}
	~AudioChannel()
	{ 
		m_channelNum = -1;
		m_audioPosition = NULL;
	}

	int getChannelNum() { return m_channelNum; }
	void setChannelNum(int channel) { m_channelNum = channel; }
	bool updateAudio(PxRigidActor * listener);

};




