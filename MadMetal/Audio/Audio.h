#pragma once
#include "Libraries/sdl/SDL.h"
#include "Libraries/sdl/SDL_mixer.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "Objects\Object.h"
#include "Sound.h"
#define NUM_CHANNELS 50

class DynamicAudioSource;

class Audio
{
private:
	std::vector<AudioSource> m_audioSources;
	std::vector<Mix_Chunk *> m_library;
	PxRigidActor * m_listener;


public:

	enum SourceType
	{
		eStaticLocation, //source doesn't move after started
		eDynamicLocation, //source can move after starting
		eInteractive //source may interupt after starting ie. braking?
	};

	Audio()
	{
		SDL_Init(SDL_INIT_AUDIO);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Error: " << Mix_GetError() << std::endl;
			
		}
		//set max amount of channels to mix
		Mix_AllocateChannels(NUM_CHANNELS);
		
	}

	~Audio()
	{
		Mix_CloseAudio();
		SDL_Quit();
	}
	void assignListener(PxRigidActor* listener);
	void removeListener();
	void stopSources();
	void pauseSources();
	void resumeSources();
	void initialize();
	bool queAudioSource(PxRigidActor * audioSource, Sound& toPlay, SourceType audioType, int loopCount = 0);
	
	void update();

};





class AudioSource
{
private:
	int &m_channelNum;
	PxRigidActor * m_audioSource;
public:
	AudioSource(PxRigidActor * source, int &channel) : m_audioSource(m_audioSource), m_channelNum(channel){}
	~AudioSource(){ m_audioSource = NULL; }

	int getChannelNum();
	virtual bool updateAudio(PxRigidActor * listener);

};




