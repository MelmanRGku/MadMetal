#include "BombExplosion.h"
#include "Cars\Car.h"

BombExplosion::BombExplosion(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, float duration, Car *owner) : AnimatedExplosion(id, aable, pable, anable, rable, duration, false), owner(owner)
{
	m_maxDamage = 35;
}


BombExplosion::~BombExplosion()
{
}

void BombExplosion::onCarHit(Car *car) {

	if (car == owner)
		return;

	for (Car *carHit : carsHit) {
		if (car == carHit)
			return;
	}

	PxShape* shapes[1];
	m_physicable->getActor().getShapes(shapes, 1);
	PxSphereGeometry geom;
	shapes[0]->getSphereGeometry(geom);
	PxVec3 actorPos = m_physicable->getActor().getGlobalPose().p;
	glm::vec3 thisPos = glm::vec3(actorPos.x, actorPos.y, actorPos.z);
	float distanceBetweenCarAndCenterOfExplosion = glm::length(thisPos - car->getGlobalPose());
	float damageMultiplier = 1 - distanceBetweenCarAndCenterOfExplosion / geom.radius;
	float damageToDeal = m_maxDamage * damageMultiplier;
	if (car->getActivePowerUpType() != PowerUpType::DEFENSE) {
		if (car->takeDamage(damageToDeal)) {
			owner->addDamageDealt(damageToDeal);
		}
	}

	carsHit.push_back(car);
}
