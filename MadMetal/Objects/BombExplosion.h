#pragma once

#include "AnimatedExplosion.h"

class Car;

class BombExplosion : public AnimatedExplosion
{
private:
	std::vector<Car *> carsHit;
	Car *owner;
	float m_maxDamage;
public:
	BombExplosion(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float duration, Car *owner);
	~BombExplosion();
	void onCarHit(Car *car);
};

