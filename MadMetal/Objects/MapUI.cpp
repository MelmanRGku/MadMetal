#include "MapUI.h"
#include "Game Logic\Controllable.h"

MapUI::MapUI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : TexturedObject2D(id, aable, anable, rable)
{
}


MapUI::~MapUI()
{
}

bool MapUI::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;

	TexturedObject2D::draw(renderer, type, passNumber);

	for (unsigned int i = 0; i < players->size(); i++) {
		PxVec3 playerPos = players->at(i)->getCar()->getActor().getGlobalPose().p;
		glm::vec3 playerDimensions = playerSizes.at(i);
		glm::vec3 relativePos = (glm::vec3(playerPos.x, playerPos.y, playerPos.z) - trackMinBounds);
		relativePos.x = relativePos.x / trackSize.x;
		relativePos.z = relativePos.z / trackSize.z;
		playerDimensions.x = playerDimensions.x / trackSize.x / 2;
		playerDimensions.z = playerDimensions.z / trackSize.z / 2;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glm::vec3 pos = m_animatable->getPosition();
		glm::vec3 size = m_animatable->getScale();
		glm::vec2 playerPosOnMapUI = glm::vec2(pos.x - size.x / 2 + relativePos.z * size.x, pos.y - size.y / 2 + relativePos.x * size.y);
		if (players->at(i)->getCar()->getId() == mainPlayer->getCar()->getId())
			glColor3f(0.f, 1.f, 0.f);
		else
			glColor3f(1.f, 1.f, 1.f);
		glBegin(GL_QUADS);
		glVertex3f(playerPosOnMapUI.x - playerDimensions.z, playerPosOnMapUI.y - playerDimensions.x, -1);
		glVertex3f(playerPosOnMapUI.x + playerDimensions.z, playerPosOnMapUI.y - playerDimensions.x, -1);
		glVertex3f(playerPosOnMapUI.x + playerDimensions.z, playerPosOnMapUI.y + playerDimensions.x, -1);
		glVertex3f(playerPosOnMapUI.x - playerDimensions.z, playerPosOnMapUI.y + playerDimensions.x, -1);
		glEnd();
	}

	return false;

}

void MapUI::setPlayers(std::vector<Controllable *> *players) {

	this->players = players;
	for (unsigned int i = 0; i < players->size(); i++) {
		PxVec3 playerSize = players->at(i)->getCar()->getWorldBounds().getDimensions();
		playerSizes.push_back(glm::vec3(playerSize.x, playerSize.y, playerSize.z));
	}

}