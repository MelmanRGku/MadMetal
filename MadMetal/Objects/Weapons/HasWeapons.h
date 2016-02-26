#pragma once

#include "../RenderableObject.h"

class HasWeapons{
	
public:

	HasWeapons() {};
	virtual ~HasWeapons() {};

	virtual glm::vec3 getNextBulletPos() = 0;
	virtual void shoot() = 0;
	virtual void addWeapon(RenderableObject* weapon) { m_weapons.push_back(weapon); }

protected: //members
	std::vector<RenderableObject*> m_weapons;

};