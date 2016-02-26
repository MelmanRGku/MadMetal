#pragma once
#include "Libraries/sdl/SDL.h"
#include "Libraries/sdl/SDL_mixer.h"
#include <iostream>
#include <vector>
#include <cmath>
#define NUM_CHANNELS 20

class PositionalAudioSource;

class DummyPosition
{
private:
	float xpos;
	float ypos;

public:
	DummyPosition()
	{
		xpos = ypos = 0;
	}
	DummyPosition(float x, float y) : xpos(x), ypos(y){}

	void getPosition(float &x, float &y);
	void movePosition(float x, float y);
	void setPosition(float x, float y);
};


class Audio
{
private:
	std::vector<PositionalAudioSource> positionalSources;
	DummyPosition * listener;

public:
	Audio()
	{
		SDL_Init(SDL_INIT_AUDIO);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Error: " << Mix_GetError() << std::endl;
			
		}
		//set max amount of channels to mix
		Mix_AllocateChannels(NUM_CHANNELS);
		listener = new DummyPosition(0,0);
	}

	~Audio()
	{
		Mix_CloseAudio();
		SDL_Quit();
	}
	void assignListener(DummyPosition **listener);
	void removeListener();
	void stopSources();
	void pauseSources();
	void resumeSources();
	
	bool quePositionalSource(DummyPosition **position);
	bool queStaticSource(int sourceID);
	void update();

};





class PositionalAudioSource
{
private:
	DummyPosition * audioSource = new DummyPosition();

	int channelNum;
public:
	PositionalAudioSource(DummyPosition ** position, int channel) : channelNum(channel), audioSource(*position){}
	~PositionalAudioSource(){}

	int getChannelNum();
	void getSourcePosition(float &x, float &y);

};



