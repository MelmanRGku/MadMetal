#include "DeathPit.h"

DeathPit::DeathPit(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{

}

DeathPit::~DeathPit()
{


}

void DeathPit::setRespawnLocation(PxVec3 respawnLocation)
{
	m_respawnLocation = respawnLocation;
}