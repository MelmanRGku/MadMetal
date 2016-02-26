#pragma once
#include "Audio\Sound.h"

class AudioFactory
{
public:
	AudioFactory(Audio& audioHandle) : m_audioHandle(audioHandle){}
	~AudioFactory(){}

	/*
		Sound * makeSound(Enum soundToMake)
		{
			Big switch statement utilizing the enum sound types
		}
	*/
private: //members
	Audio& m_audioHandle;
	//todo:: make these!!!
	//list of Sounds
	//enum sound types
};