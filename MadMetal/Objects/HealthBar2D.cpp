#include "HealthBar2D.h"


HealthBar2D::HealthBar2D(long id, Audioable *aable, Animatable *anable, Renderable2D *rable, Model2D *currentHealthModel, Model2D *lostHealthModel) : TexturedObject2D(id, aable, anable, rable), currentHealthModel(currentHealthModel), lostHealthModel(lostHealthModel)
{
	healthPercentage = 0.f;
}


HealthBar2D::~HealthBar2D()
{
	delete currentHealthModel;
	delete lostHealthModel;
}

bool HealthBar2D::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	bool toReturn = false;
	if (TexturedObject2D::draw(renderer, type, passNumber)) {
		toReturn = true;
	}

	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false || toReturn;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec3 pos = m_animatable->getPosition();
	glm::vec3 size = m_animatable->getScale();
	//x - minx, y - miny, z - maxx, w - maxy
	glm::vec4 healthParams = glm::vec4(pos.x - size.x / 22, pos.y - size.y / 8, pos.x + 1.77 * size.x / 4, pos.y + size.y / 13);
	glColor3f(1.f, 1.f, 1.f);
	currentHealthModel->getTexture()->Bind(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(healthParams.x, healthParams.y); 
	glTexCoord2f(healthPercentage, 1);
	glVertex2f(healthParams.x + (healthParams.z - healthParams.x) * healthPercentage, healthParams.y);
	glTexCoord2f(healthPercentage, 0);
	glVertex2f(healthParams.x + (healthParams.z - healthParams.x) * healthPercentage, healthParams.w);
	glTexCoord2f(0, 0);
	glVertex2f(healthParams.x, healthParams.w);
	glEnd();
	currentHealthModel->getTexture()->unBind(GL_TEXTURE_2D);

	lostHealthModel->getTexture()->Bind(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(healthPercentage, 1);
	glVertex2f(healthParams.x + (healthParams.z - healthParams.x) * healthPercentage, healthParams.y);
	glTexCoord2f(0, 1);
	glVertex2f(healthParams.z, healthParams.y);
	glTexCoord2f(0, 0);
	glVertex2f(healthParams.z, healthParams.w);
	glTexCoord2f(healthPercentage, 0);
	glVertex2f(healthParams.x + (healthParams.z - healthParams.x) * healthPercentage, healthParams.w);
	glEnd();
	lostHealthModel->getTexture()->unBind(GL_TEXTURE_2D);


	return false || toReturn;
}
