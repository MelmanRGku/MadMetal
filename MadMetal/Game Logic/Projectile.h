#pragma once
#include "Controllable.h"
#include "Objects\RenderableObject.h"
#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile
{
private:
	float m_damage;
	RenderableObject * m_projectileModel;
	
public:
	Projectile(char * fileName)
	{
		//load from file name
	}
	void setObject(RenderableObject * obj)
	{
		m_projectileModel = obj;
	}

	RenderableObject * getObject()
	{
		return m_projectileModel;
	}


};

#endif