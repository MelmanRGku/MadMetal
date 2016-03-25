#include "MeowMix.h"
#include "Factory\GameFactory.h"


MeowMix::MeowMix(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Car(id, style, car, aable, pable, anable, rable)
{
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	m_reloadRateSeconds = 0.15;						//in s
	m_superReloadRateSeconds = 1;
	m_currentHealth = m_maxHealth = 100;
	

	m_superMaxDurationSeconds = 5;
	m_superDurationRemainingSeconds = 0;

	
}


MeowMix::~MeowMix()
{
}

void MeowMix::fire()
{
	if (m_reloadRemainingSeconds > 0)
		return;
	

	

	PxTransform *pos;
	if (m_superDurationRemainingSeconds > 0)
	{
		/*glm::vec4 up = glm::normalize(getModelMatrix() * glm::vec4(0, 1, 0, 0));
		glm::vec4 forward = glm::normalize(getModelMatrix() * glm::vec4(0, 0, 1, 0));
		glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 2) + forward * (getScale().z / 2);
		pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
		GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_EXPLOSIVELY_DELICIOUS, pos, NULL, this);
		delete pos;
		m_reloadRemainingSeconds = m_superReloadRateSeconds;*/

		//PxSweepBuffer hit;              // [out] Sweep results
		//PxGeometry sweepShape = PxSphereGeometry(1);    // [in] swept shape
		//PxTransform initialPose = m_car.getRigidDynamicActor()->getGlobalPose();  // [in] initial shape pose (at distance=0)
		//glm::vec3 forward = getForwardVector();
		//PxVec3 sweepDirection = PxVec3(forward.x, forward.y, forward.z);    // [in] normalized sweep direction
		//bool status = m_scene->sweep(sweepShape, initialPose, sweepDirection, sweepDistance, hit);

	}
	else {
		//if (m_activePowerUp != PowerUpType::NONE)
			//std::cout << "Shooting with powerup \n";
		//else
			//std::cout << "Shooting without Powerup \n";
		m_reloadRemainingSeconds = m_reloadRateSeconds;
		glm::vec4 up = glm::normalize(getModelMatrix() * glm::vec4(0, 1, 0, 0));
		glm::vec4 left = glm::normalize(getModelMatrix() * glm::vec4(-1, 0, 0, 0));
		if (m_lastWeaponShot == LAST_WEAPON_SHOT_LEFT)
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_RIGHT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 3) + left * (getScale().x / 2);
			pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, pos, NULL, this);
			delete pos;
		}
		else
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 3) - left * (getScale().x / 2);
			pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, pos, NULL, this);
			delete pos;
		}
	}
	

}

void MeowMix::update(float dt) {
	Car::update(dt);
	
}

void MeowMix::useSuper() {
	m_superDurationRemainingSeconds = m_superMaxDurationSeconds;
	m_reloadRemainingSeconds = 0;
	m_superGauge = 0;
	m_renderable->setModel(Assets::getModel("UglyCarWithCannon"));
	static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
	m_animatable->updateScale(glm::vec3(0, 2, 0));
}

void MeowMix::unuseSuper() {
	m_renderable->setModel(Assets::getModel("UglyCarWithGuns"));
	static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
	m_animatable->updateScale(glm::vec3(0, -2, 0));
}