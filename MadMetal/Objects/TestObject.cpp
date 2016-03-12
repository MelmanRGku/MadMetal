#define M_PI (3.14159265359)

#include "TestObject.h"
#include <iostream>
#include "Cars/Car.h"
#include "Factory\GameFactory.h"

TestObject::TestObject(long id, Audioable *aable, Animatable *anable, Renderable *rable)
: m_renderable(rable)
, m_animatable(anable)
, m_audioable(aable)
, id(id)
{
}


TestObject::~TestObject()
{
	delete m_renderable;
	delete m_animatable;
	delete m_audioable;

}

void TestObject::setSound(Sound theSound)
{
	m_sound = theSound;
}