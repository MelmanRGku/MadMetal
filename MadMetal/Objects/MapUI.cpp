#include "MapUI.h"
#include "Game Logic\Controllable.h"
#include "Libraries\glm\gtx\vector_angle.hpp"

MapUI::MapUI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : TexturedObject2D(id, aable, anable, rable)
{
}


MapUI::~MapUI()
{
	delete playerModel;
}

bool MapUI::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;

	TexturedObject2D::draw(renderer, type, passNumber);

	playerModel->getTexture()->Bind(GL_TEXTURE_2D);
	for (unsigned int i = 0; i < players->size(); i++) {
		PxVec3 playerPos = players->at(i)->getCar()->getActor().getGlobalPose().p;
		glm::vec3 playerDimensions = playerSizes.at(i);
		glm::vec3 relativePos = (glm::vec3(playerPos.x, playerPos.y, playerPos.z) - trackMinBounds);
		relativePos.x = relativePos.x / trackSize.x;
		relativePos.z = relativePos.z / trackSize.z;
		playerDimensions.x = playerDimensions.x / trackSize.x / 2;
		playerDimensions.z = playerDimensions.z / trackSize.z / 2;


		glm::vec3 pos = m_animatable->getPosition();
		glm::vec3 size = m_animatable->getScale();
		glm::vec2 playerPosOnMapUI = glm::vec2(pos.x - size.x / 2 + relativePos.z * size.x, pos.y - size.y / 2 + relativePos.x * size.y);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(playerPosOnMapUI.x, playerPosOnMapUI.y, -1);
		glm::vec2 normalVector = glm::normalize(glm::vec2(0, -1));
		glm::vec2 forwardVector = glm::normalize(glm::vec2(players->at(i)->getCar()->getForwardVector().x, players->at(i)->getCar()->getForwardVector().z));
		float angle = glm::degrees(glm::orientedAngle(normalVector, forwardVector));
		glRotatef(angle, 0, 0, -1);


		if (players->at(i)->getCar()->getId() == mainPlayer->getCar()->getId())
			glColor3f(1.f, 1.f, 1.f);
		else
			glColor3f(0.5f, 0.5f, 0.5f);

		
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-playerDimensions.z, -playerDimensions.x, 0);
		glTexCoord2f(1, 0);
		glVertex3f(playerDimensions.z, -playerDimensions.x, 0);
		glTexCoord2f(1, 1);
		glVertex3f(playerDimensions.z, playerDimensions.x, 0);
		glTexCoord2f(0, 1);
		glVertex3f(- playerDimensions.z, playerDimensions.x, 0);
		glEnd();
		
	}
	playerModel->getTexture()->unBind(GL_TEXTURE_2D);

	return false;

}

void MapUI::setPlayers(std::vector<Controllable *> *players) {

	this->players = players;
	for (unsigned int i = 0; i < players->size(); i++) {
		PxVec3 playerSize = players->at(i)->getCar()->getWorldBounds().getDimensions();
		playerSizes.push_back(glm::vec3(playerSize.x, playerSize.y, playerSize.z));
	}

}