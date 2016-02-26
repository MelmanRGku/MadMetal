#include "RenderableObject.h"

RenderableObject::RenderableObject()
{
}

RenderableObject::~RenderableObject()
{
}

void RenderableObject::drawThis(Renderer *renderer) {
	std::vector<Mesh *> *meshes = getModel()->getMeshes();

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

void RenderableObject::draw(Renderer *renderer) {
	drawThis(renderer);
}

glm::mat4x4 RenderableObject::getModelMatrix() {
	return getPhysicsModelMatrix() * getLocalModelMatrix() * getInitialModelMatrix();
}