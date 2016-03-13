#define M_PI (3.14159265359)

#include "TestObject.h"
#include <iostream>
#include "Cars/Car.h"
#include "Factory\GameFactory.h"

TestObject::TestObject(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable, Animation *aniable)
: m_renderable(rable)
, m_physicable(pable)
, m_animatable(anable)
, m_audioable(aable)
, id(id)
, m_animation(aniable)
{
}


TestObject::~TestObject()
{
	delete m_renderable;
	delete m_animatable;
	delete m_physicable;
	delete m_audioable;

}

glm::mat4x4 TestObject::getModelMatrix() {
	return m_physicable->getPhysicsModelMatrix() * m_animatable->getModelMatrix() * m_renderable->getInitialModelMatrix();
}


glm::vec3 TestObject::getFullRotation() { 
	PxQuat rotation = m_physicable->getActor().getGlobalPose().q;
	return glm::eulerAngles(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z)) + m_animatable->getRotation(); 
}

bool TestObject::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber)
{
	if (type != Renderer::ShaderType::SHADER_TYPE_CELL || passNumber > 1)
		return false;

	if (m_renderable->getModel() == NULL)
		return false;

	std::vector<Mesh *> *meshes = m_renderable->getModel()->getMeshes();

	glm::mat4x4 modelMatrix = getModelMatrix();

	CellShaderProgram *program = static_cast<CellShaderProgram *>(renderer->getShaderProgram(Renderer::ShaderType::SHADER_TYPE_CELL));

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

	return false;
}

glm::vec3 TestObject::getPosition() {
	PxVec3 pos = m_physicable->getActor().getGlobalPose().p;
	return glm::vec3(pos.x, pos.y, pos.z);
}

void TestObject::setSound(Sound theSound)
{
	m_sound = theSound;
}

void TestObject::playSound()
{
	
	m_audioable->getAudioHandle().queAudioSource(&this->getActor(), m_sound);
}

void TestObject::startAnimation()
{
	if (!m_animation == NULL)
	{
		start = clock();
		previousModel = m_renderable->getModel();
		m_renderable->setModel(m_animation->theModels[0], true, true);
		animating = true;
		current = 0;
	}
}

void TestObject::updateAnimation()
{
	if (!m_animation == NULL)
	{

		if (animating)
		{
			if (clock() < start + m_animation->ticksPerFrame[current])
			{
			}
			else
			{
				start = clock();
				current++;
				if (current >= m_animation->theModels.size())
				{
					animating = false;
					m_renderable->setModel(previousModel, true, true);
				}
				else
				{
					m_renderable->setModel(m_animation->theModels[current], true, true);
				}
			}
		}
	}
}