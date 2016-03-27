#include "GaugeBar.h"


GaugeBar::GaugeBar(long id, Audioable *aable, Animatable *anable, Renderable2D *rable, Model2D *currentGaugeModel, std::vector<Model2D *> completeGaugeModels) : TexturedObject2D(id, aable, anable, rable), currentGaugeModel(currentGaugeModel), completeGaugeModels(completeGaugeModels)
{
	gaugePercentage = 0.f;
	timeBetweenFullGaugeBarFramesSeconds = .07f;
}


GaugeBar::~GaugeBar()
{
	delete currentGaugeModel;
	for (Model2D *model : completeGaugeModels) {
		delete model;
	}
}

bool GaugeBar::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	bool toReturn = false;
	if (TexturedObject2D::draw(renderer, type, passNumber)) {
		toReturn = true;
	}

	if (passNumber < 2)
		return true;

	if (passNumber > 2)
		return false || toReturn;

	if (type != Renderer::ShaderType::SHADER_TYPE_NONE)
		return false || toReturn;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec3 pos = m_animatable->getPosition();
	glm::vec3 size = m_animatable->getScale();
	//x - minx, y - miny, z - maxx, w - maxy
	glm::vec4 gaugeParams = glm::vec4(pos.x - size.x / 5, pos.y - size.y / 7, pos.x + 1.3 * size.x / 4, pos.y - size.y / 23);
	glColor3f(1.f, 1.f, 1.f);
	currentGaugeModel->getTexture()->Bind(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(gaugeParams.x, gaugeParams.y);
	glTexCoord2f(gaugePercentage, 1);
	glVertex2f(gaugeParams.x + (gaugeParams.z - gaugeParams.x) * gaugePercentage, gaugeParams.y);
	glTexCoord2f(gaugePercentage, 0);
	glVertex2f(gaugeParams.x + (gaugeParams.z - gaugeParams.x) * gaugePercentage, gaugeParams.w);
	glTexCoord2f(0, 0);
	glVertex2f(gaugeParams.x, gaugeParams.w);
	glEnd();
	currentGaugeModel->getTexture()->unBind(GL_TEXTURE_2D);

	if (currentCompleteGaugeModel != NULL) {
		//x - minx, y - miny, z - maxx, w - maxy
		glm::vec4 effectParams = glm::vec4(pos.x - size.x / 4, pos.y - size.y / 3, pos.x + 1.5 * size.x / 4, pos.y - size.y / 9);
		currentCompleteGaugeModel->getTexture()->Bind(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(effectParams.x, effectParams.y);
		glTexCoord2f(1, 1);
		glVertex2f(effectParams.z, effectParams.y);
		glTexCoord2f(1, 0);
		glVertex2f(effectParams.z, effectParams.w);
		glTexCoord2f(0, 0);
		glVertex2f(effectParams.x, effectParams.w);
		glEnd();
		currentCompleteGaugeModel->getTexture()->unBind(GL_TEXTURE_2D);
	}

	return false || toReturn;
}

void GaugeBar::update(float dt) {
	TexturedObject2D::update(dt);
	if (gaugePercentage >= 1) {
		currentFrameTimeSeconds += dt;
		if (currentFrameTimeSeconds > timeBetweenFullGaugeBarFramesSeconds) {
			currentFrameTimeSeconds = 0;
			currentCompleteGaugeModelIndex++;
			if (currentCompleteGaugeModelIndex >= completeGaugeModels.size()) {
				currentCompleteGaugeModelIndex = 0;
			}
			currentCompleteGaugeModel = completeGaugeModels.at(currentCompleteGaugeModelIndex);
		}
	}
	else {
		currentCompleteGaugeModel = NULL;
	}
}


void GaugeBar::setGaugePercentage(float percentage) {
	gaugePercentage = percentage; 
	if (gaugePercentage >= 1 && currentCompleteGaugeModel == NULL) {
		currentCompleteGaugeModel = completeGaugeModels.at(0);
		currentFrameTimeSeconds = 0;
		currentCompleteGaugeModelIndex = 0;
	}
}