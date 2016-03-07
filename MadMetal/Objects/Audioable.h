#pragma once
#include "Audio\Audio.h"
class Audioable {
private:
	Audio& m_audioHandle;
public:
	Audioable(Audio& audioHandle) : m_audioHandle(audioHandle) {  }
	virtual ~Audioable() { }
	Audio& getAudioHandle(){ return m_audioHandle; }
};