#pragma once
class ObjectUpdater
{
protected:
	double totalDuration;				//in milliseconds
	double currentDuration;			//in milliseconds

public:
	ObjectUpdater();
	~ObjectUpdater();
	virtual void update(float dt) = 0;
	virtual bool ended() { return currentDuration >= totalDuration; }
	virtual void restart() { currentDuration = 0; }
	
};

