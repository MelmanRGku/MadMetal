#pragma once

#include <vector>
#include "ObjectUpdater.h"

class ObjectUpdaterSequence : public ObjectUpdater
{
private:
	std::vector<ObjectUpdater *> updaters;
	int type, totalNumberOfTimes, 
		currentNumberOfTimes = 0,
		currentStep = 0;

public:
	static const int TYPE_ONCE = 0,
		TYPE_MULTIPLE_TIMES = 1,
		TYPE_INFINITE = 2;

	ObjectUpdaterSequence(int type);
	ObjectUpdaterSequence(int type, int numberOfTimes);
	~ObjectUpdaterSequence();
	void update(long dt);
	bool ended();
	void addObjectUpdater(ObjectUpdater *obj);
	void restart();
};

