#include "MeowMix.h"
#include "Factory\GameFactory.h"

MeowMix::MeowMix(long id, DrivingStyle& style, PxVehicleDrive4W &car, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable) : Car(id, style, car, aable, pable, anable, rable)
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
	

	

	if (m_superDurationRemainingSeconds > 0)
	{
		glm::vec4 up = glm::normalize(m_animatable.getModelMatrix() * glm::vec4(0, 1, 0, 0));
		glm::vec4 forward = glm::normalize(m_animatable.getModelMatrix() * glm::vec4(0, 0, 1, 0));
		glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 2) + forward * (getScale().z / 2);
		GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_SUPER_VOLCANO, new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z), NULL, this);
		m_reloadRemainingSeconds = m_superReloadRateSeconds;

	}
	else {
		m_reloadRemainingSeconds = m_reloadRateSeconds;
		glm::vec4 up = glm::normalize(m_animatable.getModelMatrix() * glm::vec4(0, 1, 0, 0));
		glm::vec4 left = glm::normalize(m_animatable.getModelMatrix() * glm::vec4(-1, 0, 0, 0));
		if (m_lastWeaponShot == LAST_WEAPON_SHOT_LEFT)
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_RIGHT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 2) + left * (getScale().x / 2);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z), NULL, this);
		}
		else
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) + up * (getScale().y / 2) - left * (getScale().x / 2);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z), NULL, this);
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
	m_renderable.setModel(Assets::getModel("UglyCarWithCannon"), true, true);
	m_animatable.updateScale(glm::vec3(0, 2, 0));
}

void MeowMix::unuseSuper() {
	m_renderable.setModel(Assets::getModel("UglyCarWithGuns"), true, true);
	m_animatable.updateScale(glm::vec3(0, -2, 0));
}