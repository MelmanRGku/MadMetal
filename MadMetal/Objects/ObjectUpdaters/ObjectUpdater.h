#pragma once
class ObjectUpdater
{
protected:
	long totalDuration, currentDuration;			//in milliseconds

public:
	ObjectUpdater();
	~ObjectUpdater();
	virtual void update(long dt) = 0;
	virtual bool ended() { return currentDuration >= totalDuration; }
	virtual void restart() { currentDuration = 0; }
	
};

