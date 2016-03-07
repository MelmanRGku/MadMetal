#pragma once

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

	void setChannel(int channel)
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
	AccelerationSound() : Sound()
	{
		
		m_libraryIndex = 1;
	};
	virtual ~AccelerationSound(){};
};

class CarIdleSound : public Sound
{
public:
	CarIdleSound() : Sound()
	{
		m_libraryIndex = 0;
	};
	virtual ~CarIdleSound(){};

};

class GunShotSound : public Sound
{
public:
	GunShotSound() : Sound()
	{
		m_libraryIndex = 7;
	};
	virtual ~GunShotSound(){};
};

class ExplosionSound: public Sound
{
public:
	ExplosionSound() : Sound()
	{
		m_libraryIndex = 3;
	};
	virtual ~ExplosionSound(){};
};

class BulletCarCollisionSound : public Sound
{
public:
	BulletCarCollisionSound() : Sound()
	{
		m_libraryIndex = 5;
	};
	virtual ~BulletCarCollisionSound(){};
};

class ChassisCrashSound : public Sound
{
public:
	ChassisCrashSound() : Sound()
	{
		m_libraryIndex = 5;
	};
	virtual ~ChassisCrashSound(){};
};