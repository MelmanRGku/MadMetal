#pragma once
#include "Controllable.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile
{
private:
	float m_damage;
	Controllable * owner;
public:
	Projectile();


};

#endif