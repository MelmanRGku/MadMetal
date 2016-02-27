#define M_PI (3.14159265359)

#include "TestObject.h"
#include <iostream>
#include "Cars/Car.h"

TestObject::TestObject(Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio& audio)
: m_renderable(rable)
, m_physicable(pable)
, m_animatable(anable)
, m_audioable(aable)
, m_audio(audio)
{

}


TestObject::~TestObject()
{
}

glm::mat4x4 TestObject::getModelMatrix() {
	return m_physicable.getPhysicsModelMatrix() * m_animatable.getModelMatrix();
}

void TestObject::draw(Renderer *renderer)
{
	if (m_renderable.getModel() == NULL)
		return;

	std::vector<Mesh *> *meshes = m_renderable.getModel()->getMeshes();

	glm::mat4x4 modelMatrix = getModelMatrix();

	glUniform1i(renderer->getShaderProgram()->textureUniform, 0);
	glUniformMatrix4fv(renderer->getShaderProgram()->modelMatrixUniform, 1, false, &modelMatrix[0][0]);
	for (unsigned int i = 0; i < meshes->size(); i++) {
		Mesh *mesh = meshes->at(i);
		if (mesh->hasTexture()) {
			mesh->getTexture()->Bind(GL_TEXTURE0);
			glUniform1i(renderer->getShaderProgram()->textureValidUniform, true);
		}
		else {
			glUniform1i(renderer->getShaderProgram()->textureValidUniform, false);
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

