#pragma once
#include "Controllable.h"
#include "ControllableTemplate.h"
#include "Objects\Cars\Car.h"
#include "Objects\CollisionVolume.h"
#include "Game Logic\AIDefinitions.h"

class PathFinding;
class Track;

class AIControllable : public Controllable
{
public:
	AIControllable(ControllableTemplate& aiTemplate);
	~AIControllable();

	void playFrame(double dt);//todo: fearless leader <
	void setCar(Car * toAdd);
	void processPowerups();
	void processFire(std::vector<Controllable *> *players);
private: //helper functions
	void accelerate(float amount);

	void backUp(float amount);
	void processInputAcceleration(float amount);
	void accelerateToNextCollisionVolume();
	void reverse();
	void changeTurning(float turningDirectionValue, float turningAmountValue);
	void checkStuckInWall();
	void updateMovementState();
	void rotateTowardsNextCollisionVolume();

private: //members
	AiStateMovement m_movementState;
	bool m_needsToBackup;
	int m_stuckWallCounter;
	int m_counterReverse;
	float m_stuckRespawnCounterMillis;
	PxVec3 m_stuckPosition;
};