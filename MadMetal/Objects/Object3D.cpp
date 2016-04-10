#define M_PI (3.14159265359)

#include "Object3D.h"

Object3D::Object3D(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Animation *aniable) : TestObject(id, aable, anable, rable)
, m_physicable(pable), m_animation(aniable)
{
}


Object3D::~Object3D()
{
	if (m_physicable != NULL)
	delete m_physicable;

}

glm::mat4x4 Object3D::getModelMatrix() {
	return m_physicable->getPhysicsModelMatrix() * m_animatable->getModelMatrix() * static_cast<Renderable3D *>(m_renderable)->getInitialModelMatrix();
}


glm::vec3 Object3D::getFullRotation() {
	PxQuat rotation = m_physicable->getActor().getGlobalPose().q;
	return glm::eulerAngles(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z)) + m_animatable->getRotation();
}

bool Object3D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber)
{
	if (type != Renderer::ShaderType::SHADER_TYPE_CELL || passNumber > 1)
		return false;

	if (m_renderable->getModel() == NULL)
		return false;

	std::vector<Mesh *> *meshes = static_cast<Model3D *>(m_renderable->getModel())->getMeshes();

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

glm::vec3 Object3D::getPosition() {
	PxVec3 pos = m_physicable->getActor().getGlobalPose().p;
	return glm::vec3(pos.x, pos.y, pos.z);
}

void Object3D::playSound()
{
	m_audioable->getAudioHandle().queAudioSource(&this->getActor(), m_sound);
}

void Object3D::startAnimation()
{
	if (!m_animation == NULL)
	{
		start = clock();
		previousModel = m_renderable->getModel();
		m_renderable->setModel(m_animation->theModels[0]);
		static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
		animating = true;
		current = 0;
	}
}

void Object3D::updateAnimation()
{
	if (!m_animation == NULL)
	{

		if (animating)
		{
			//if enough time has passed
			if (clock() >= start + m_animation->ticksPerFrame[current])
			{
				start = clock();
				current++;
				if (current >= m_animation->theModels.size())
				{
					animating = false;
					m_renderable->setModel(previousModel);
					static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
				}
				else
				{
					m_renderable->setModel(m_animation->theModels[current]);
					static_cast<Renderable3D *>(m_renderable)->adjustModel(true, true);
				}
			}
		}
	}
}