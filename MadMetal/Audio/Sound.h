#pragma once
#include "Audio.h"


class Sound
{
public:
	Sound() 
	{
		m_currentChannel = -1;
	}
	virtual ~Sound(){}

	virtual int& getChannel()
	{
		return m_currentChannel;
	}

	virtual void setChannel(int channel)
	{
		m_currentChannel = channel;
	}

	virtual int getLibraryIndex() {
		return m_libraryIndex;
	}

	virtual void setLibraryIndex(int index){
		m_libraryIndex = index;
	}

protected: //members
	int m_libraryIndex;
	int m_currentChannel;
};

class AccelerationSound : public Sound
{
public:
	AccelerationSound()
	{
		m_libraryIndex = 2;
	};
	virtual ~AccelerationSound(){};
};

class CarIdleSound : public Sound
{
public:
	CarIdleSound()
	{
		m_libraryIndex = 0;
	};
	virtual ~CarIdleSound(){};

};
