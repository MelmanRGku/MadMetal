#pragma once
#include "Audio.h"


class Sound
{
public:
	Sound() {}
	virtual ~Sound(){}
	virtual int getIndex() = 0;

protected: //members
	int m_index;

	
};

class AccelerationSound : public Sound
{
	AccelerationSound()
	{
		m_index = 1;
	};
	virtual ~AccelerationSound(){};
	int getIndex() { return m_index; };
	
};