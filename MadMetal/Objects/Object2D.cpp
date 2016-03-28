#define M_PI (3.14159265359)

#include "Object2D.h"

Object2D::Object2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : TestObject(id, aable, anable, rable)
{
}


Object2D::~Object2D()
{

}

glm::mat4x4 Object2D::getModelMatrix() {
	return m_animatable->getModelMatrix();
}

bool Object2D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber)
{
	//if (type != Renderer::ShaderType::SHADER_TYPE_CELL || passNumber > 1)
	//	return false;

	//if (m_renderable->getModel() == NULL)
	//	return false;

	//std::vector<Mesh *> *meshes = m_renderable->getModel()->getMeshes();

	//glm::mat4x4 modelMatrix = getModelMatrix();

	//CellShaderProgram *program = static_cast<CellShaderProgram *>(renderer->getShaderProgram(Renderer::ShaderType::SHADER_TYPE_CELL));

	//glUniform1i(program->textureUniform, 0);
	//glUniformMatrix4fv(program->modelMatrixUniform, 1, false, &modelMatrix[0][0]);
	//for (unsigned int i = 0; i < meshes->size(); i++) {
	//	Mesh *mesh = meshes->at(i);
	//	if (mesh->hasTexture()) {
	//		mesh->getTexture()->Bind(GL_TEXTURE0);
	//		glUniform1i(program->textureValidUniform, true);
	//	}
	//	else {
	//		glUniform1i(program->textureValidUniform, false);
	//	}
	//	// Draw mesh
	//	glBindVertexArray(mesh->getVAO());
	//	glDrawElements(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, 0);
	//	//glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices()->size());
	//	glBindVertexArray(0);
	//	if (mesh->hasTexture()) {
	//		mesh->getTexture()->unBind(GL_TEXTURE0);
	//	}
	//}

	//return false;
	return false;
}

void Object2D::playSound()
{

	m_audioable->getAudioHandle().queAudioSource(NULL, m_sound);
}

void Object2D::update(float dt) {
	TestObject::update(dt);
}