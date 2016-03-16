#pragma once
#include "Audio\Audio.h"
#include "Audio\Sound.h"

class AudioFactory
{
public:
	AudioFactory(Audio& audioHandle) : m_audioHandle(audioHandle){}
	~AudioFactory(){}

	enum Sounds {
		SOUND_ACCELERATION,
		SOUND_SHOOT,
		SOUND_IMPACT
	};

	Sound * makeSound(Sounds soundToMake)
	{
		switch (soundToMake) {
		case SOUND_ACCELERATION:
			return new AccelerationSound();
		}
		
	}

	Audio& getAudioHandle() { return m_audioHandle; }
private: //members
	Audio& m_audioHandle;
	//todo:: make these!!!
	//list of Sounds
	//enum sound types
};