#include "MeowMix.h"
#include "Factory\GameFactory.h"
#include "Renderer\CellShaderProgram.h"
#include "Renderer\CellTireShaderProgram.h"


MeowMix::MeowMix(long id, DrivingStyle* style, PxVehicleDrive4W &car, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Renderable3D *rable2) : Car(id, style, car, aable, pable, anable, rable)
{
	rableWheel = rable2;
	m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
	m_reloadRateSeconds = 0.15;						//in s
	m_superReloadRateSeconds = 0;
	m_currentHealth = m_maxHealth = 100;
	
	m_superMaxDurationSeconds = 5;
	m_superDurationRemainingSeconds = 0;

	
}


MeowMix::~MeowMix()
{
	delete rableWheel;
}

void MeowMix::fire()
{
	if (m_reloadRemainingSeconds > 0)
		return;
	
	PxTransform * pos;
	
	if (m_superDurationRemainingSeconds > 0)
	{
		//beam is firing right now
	}
	else {
		m_reloadRemainingSeconds = m_reloadRateSeconds;
		glm::vec4 up = glm::normalize(getModelMatrix() * glm::vec4(0, 1, 0, 0));
		glm::vec4 left = glm::normalize(getModelMatrix() * glm::vec4(-1, 0, 0, 0));
		if (m_lastWeaponShot == LAST_WEAPON_SHOT_LEFT)
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_RIGHT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) +  + left * (getScale().x / 2);
			pos = new PxTransform(weaponPos.x, weaponPos.y, weaponPos.z);
			GameFactory::instance()->makeObject(GameFactory::OBJECT_BULLET_MEOW_MIX, pos, NULL, this);
			delete pos;
		}
		else
		{
			m_lastWeaponShot = LAST_WEAPON_SHOT_LEFT;
			glm::vec4 weaponPos = glm::vec4(getFullPosition(), 1.0) +  - left * (getScale().x / 2);
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
	Car::useSuper();
	m_reloadRemainingSeconds = 0;
	m_superGauge = 0;

	m_renderable->setModel(Assets::getModel("MeowmixDeathComplete"));
	static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);

	PxGeometry * geom[1];
	geom[0] = new PxSphereGeometry(1);
	GameFactory::instance()->makeObject(GameFactory::OBJECT_MEOW_MIX_SUPER, &m_car.getRigidDynamicActor()->getGlobalPose(), geom, this);
	delete geom[0];

	
	
}

void MeowMix::unuseSuper() {
	m_renderable->setModel(Assets::getModel("Meowmixbody"));
	static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
}

bool MeowMix::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber)
{
	if (type == Renderer::ShaderType::SHADER_TYPE_CELLTIRE || passNumber > 1)
	{
		if (type != Renderer::ShaderType::SHADER_TYPE_CELLTIRE || passNumber > 1)
			return false;

		if (rableWheel->getModel() == NULL)
			return false;

		std::vector<Mesh *> *meshes = static_cast<Model3D *>(rableWheel->getModel())->getMeshes();

		glm::mat4x4 modelMatrix = getModelMatrix();

		CellTireShaderProgram *program = static_cast<CellTireShaderProgram *>(renderer->getShaderProgram(Renderer::ShaderType::SHADER_TYPE_CELLTIRE));

		glUniform1f(program->distanceTraveledUniform, distanceTraveled);

		glUniform1i(program->textureUniform, 0);
		glUniformMatrix4fv(program->modelMatrixUniform, 1, false, &modelMatrix[0][0]);
		for (unsigned int i = 0; i < meshes->size(); i++) {
			Mesh *mesh = meshes->at(i);
			if (mesh->hasTexture()) {
				mesh->getTexture()->Bind(GL_TEXTURE0);
				glUniform1i(program->textureValidUniform, true);
			}
			else {
				glUniform1i(program->textureValidUniform, false);
			}
			// Draw mesh
			glBindVertexArray(mesh->getVAO());
			glDrawElements(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices()->size());
			glBindVertexArray(0);
			if (mesh->hasTexture()) {
				mesh->getTexture()->unBind(GL_TEXTURE0);
			}
		}

	}
	else if (type == Renderer::ShaderType::SHADER_TYPE_CELL || passNumber > 1)
	{

		std::vector<Mesh *> *meshes = static_cast<Model3D *>(m_renderable->getModel())->getMeshes();
		CellShaderProgram *program = static_cast<CellShaderProgram *>(renderer->getShaderProgram(Renderer::ShaderType::SHADER_TYPE_CELL));
		glUniform1i(program->textureUniform, 0);

		glm::mat4x4 modelMatrix = getModelMatrix();

		glUniformMatrix4fv(program->modelMatrixUniform, 1, false, &modelMatrix[0][0]);
		for (unsigned int i = 0; i < meshes->size(); i++) {
			Mesh *mesh = meshes->at(i);
			if (mesh->hasTexture()) {
				mesh->getTexture()->Bind(GL_TEXTURE0);
				glUniform1i(program->textureValidUniform, true);
			}
			else {
				glUniform1i(program->textureValidUniform, false);
			}
			// Draw mesh
			glBindVertexArray(mesh->getVAO());
			glDrawElements(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices()->size());
			glBindVertexArray(0);
			if (mesh->hasTexture()) {
				mesh->getTexture()->unBind(GL_TEXTURE0);
			}
		}
	}
	return false;
}