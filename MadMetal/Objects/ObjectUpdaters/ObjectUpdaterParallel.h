#pragma once

#include <vector>
#include "ObjectUpdater.h"

class ObjectUpdaterParallel : public ObjectUpdater
{
private:
	std::vector<std::pair<ObjectUpdater *, int>> updaters;
	int type, totalNumberOfTimes;
	bool completed = false;

public:
	static const int TYPE_ONCE = 0,
		TYPE_MULTIPLE_TIMES = 1,
		TYPE_INFINITE = 2;

	ObjectUpdaterParallel(int type);
	ObjectUpdaterParallel(int type, int numberOfTimes);
	~ObjectUpdaterParallel();
	void update(long dt);
	bool ended();
	void addObjectUpdater(ObjectUpdater *obj);
	void restart();
};