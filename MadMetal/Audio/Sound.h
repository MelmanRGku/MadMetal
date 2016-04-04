#pragma once

class Sound
{
public:
	Sound()
	{
		m_currentChannel = -1;
	}
	virtual ~Sound(){}

	virtual int getChannel()
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


//-----------------------------------------------------------------
//----------------------------SOUNDS-------------------------------
//-----------------------------------------------------------------

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

class StartBeepSound : public Sound
{
public:
	StartBeepSound() : Sound()
	{
		m_libraryIndex = 8;
	}
	virtual ~StartBeepSound() {}
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

class GargantulousSuperSound : public Sound
{
public:
	GargantulousSuperSound() : Sound()
	{
		m_libraryIndex = 9;
	};
	virtual ~GargantulousSuperSound(){};
};

class MeowmixSuperSound : public Sound
{
public:
	MeowmixSuperSound() : Sound()
	{
		m_libraryIndex = 10;
	};
	virtual ~MeowmixSuperSound(){};
};


class SizzleSound : public Sound
{
public:
	SizzleSound() : Sound()
	{
		m_libraryIndex = 12;
	};
	virtual ~SizzleSound(){};
};

class BoomSound : public Sound
{
public:
	BoomSound() : Sound()
	{
		m_libraryIndex = 13;
	};
	virtual ~BoomSound(){};
};

class TrainSound : public Sound
{
public:
	TrainSound() : Sound()
	{
		m_libraryIndex = 11;
	};
	virtual ~TrainSound(){};
};

class RocketSound : public Sound
{
public:
	RocketSound() : Sound()
	{
		m_libraryIndex = 15;
	};
	virtual ~RocketSound(){};
};

class RegenSound : public Sound
{
public:
	RegenSound() : Sound()
	{
		m_libraryIndex = 14;
	};
	virtual ~RegenSound(){};
};

class ExplosivelyDeliciousSuperSound : public Sound
{
public:
	ExplosivelyDeliciousSuperSound() : Sound()
	{
		m_libraryIndex = 16;
	};
	virtual ~ExplosivelyDeliciousSuperSound(){};
};

class MenuButtonClickSound : public Sound
{
public:
	MenuButtonClickSound() : Sound()
	{
		m_libraryIndex = 17;
	};
	virtual ~MenuButtonClickSound(){};
};

class MenuButtonChangeSound : public Sound
{
public:
	MenuButtonChangeSound() : Sound()
	{
		m_libraryIndex = 18;
	};
	virtual ~MenuButtonChangeSound(){};
};

class MenuBackButtonSound : public Sound
{
public:
	MenuBackButtonSound() : Sound()
	{
		m_libraryIndex = 19;
	};
	virtual ~MenuBackButtonSound(){};
};

class MenuButtonNextPrevSound : public Sound
{
public:
	MenuButtonNextPrevSound() : Sound()
	{
		m_libraryIndex = 20;
	};
	virtual ~MenuButtonNextPrevSound(){};
};

class CarExplodeSound : public Sound
{
public:
	CarExplodeSound() : Sound()
	{
		m_libraryIndex = 21;
	};
	virtual ~CarExplodeSound(){};
};

class BulletReflectSound : public Sound
{
public:
	BulletReflectSound() : Sound()
	{
		m_libraryIndex = 22;
	};
	virtual ~BulletReflectSound(){};
};

class CarAccelerationSound : public Sound
{
public:
	CarAccelerationSound() : Sound()
	{
		m_libraryIndex = 23;
	};
	virtual ~CarAccelerationSound(){};
};

class ShieldPowerupSound : public Sound
{
public:
	ShieldPowerupSound() : Sound()
	{
		m_libraryIndex = 24;
	};
	virtual ~ShieldPowerupSound(){};
};

//-----------------------------------------------------------------
//--------------------------END SOUNDS-----------------------------
//-----------------------------------------------------------------
















//-----------------------------------------------------------------
//-----------------------------SONGS-------------------------------
//-----------------------------------------------------------------

class AllGoodThingsIAmTheEnemySong : public Sound
{
public:
	AllGoodThingsIAmTheEnemySong() : Sound()
	{
		m_libraryIndex = 0;
	};
	virtual ~AllGoodThingsIAmTheEnemySong(){};
};

class DisturbedVengefulOneSong : public Sound
{
public:
	DisturbedVengefulOneSong() : Sound()
	{
		m_libraryIndex = 1;
	};
	virtual ~DisturbedVengefulOneSong(){};
};

class SickPuppiedYoureGoingDownSong : public Sound
{
public:
	SickPuppiedYoureGoingDownSong() : Sound()
	{
		m_libraryIndex = 2;
	};
	virtual ~SickPuppiedYoureGoingDownSong(){};
};

class MetalMusicDarknessFallsSong : public Sound
{
public:
	MetalMusicDarknessFallsSong() : Sound()
	{
		m_libraryIndex = 3;
	};
	virtual ~MetalMusicDarknessFallsSong(){};
};

class CrysisTwoThemeSong : public Sound
{
public:
	CrysisTwoThemeSong() : Sound()
	{
		m_libraryIndex = 4;
	};
	virtual ~CrysisTwoThemeSong(){};
};

//-----------------------------------------------------------------
//---------------------------END SONGS-----------------------------
//-----------------------------------------------------------------