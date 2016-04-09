#include "Settings.h"
#include "Waypoint.h"

int Waypoint::globalID = 0;

Waypoint::Waypoint(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable) : Object3D(id, aable, pable, anable, rable, NULL)
{
	m_index = Waypoint::globalID;
	m_id = m_index;
	Waypoint::globalID++;
	m_highCost = 99999.0;
	m_isValid = true;

	m_position = pable->getActor().getGlobalPose().p;
}


Waypoint::~Waypoint()
{
}

const int& Waypoint::getIndex()
{
	return Waypoint::m_index;
}

void Waypoint::addAdjecentWaypoint(Waypoint* waypoint)
{
	m_adjecentWaypoints.push_back(waypoint);
}

bool Waypoint::isValid()
{
	return m_isValid;
}

bool Waypoint::isFinish() {
	return m_isFinish;
}

void Waypoint::setValid(bool isValid)
{
	m_isValid = isValid;
	if (isValid)
	{
		m_highCost = 0.0;
	}
	else
	{
		m_highCost = 999999.0;
	}
}


void Waypoint::setFinish(bool finish) {
	m_isFinish = finish;
}

int Waypoint::getId()
{
	return m_id;
}

void Waypoint::setId(int id)
{
	m_id = id;
}

void Waypoint::setHighCost(float highCost)
{
	m_highCost = highCost;
}
float Waypoint::getHighCost()
{
	return m_highCost;
}


bool Waypoint::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
#ifdef _RENDER_WAYPOINT
	if (!isValid())
		return false;
	if (passNumber < 2)
		return true;

	if (passNumber > 2)
		return false;

	if (type != Renderer::ShaderType::SHADER_TYPE_CELL)
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
#else
	return false;
#endif
}

void Waypoint::resetGlobalId() {
	globalID = 0;
}