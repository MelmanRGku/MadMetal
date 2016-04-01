#include "MapUI.h"
#include "Game Logic\Controllable.h"
#include "Libraries\glm\gtx\vector_angle.hpp"

MapUI::MapUI(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : TexturedObject2D(id, aable, anable, rable)
{
}


MapUI::~MapUI()
{
	delete meowModel;
	delete gargModel;
	delete explosiveModel;
}

float MapUI::clip(float value, float lower, float upper) {
#undef max
#undef min
	return std::max(lower, std::min(value, upper));
}


glm::vec4 MapUI::clip(glm::vec4 value, float lower, float upper) {
#undef max
#undef min
	return glm::vec4(
			std::max(lower, std::min(value.x, upper)),
			std::max(lower, std::min(value.y, upper)),
			std::max(lower, std::min(value.z, upper)),
			std::max(lower, std::min(value.w, upper))
		);
}

void MapUI::drawMap() {
#define PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE (PERCENTAGE_OF_MAP_TO_DISPLAY / 100.f)

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec4 mapVertexCoords;
	{
		PxVec3 playerPos = mainPlayer->getCar()->getActor().getGlobalPose().p;
		glm::vec3 relativePos = (glm::vec3(playerPos.x, playerPos.y, playerPos.z) - trackMinBounds);
		relativePos.x = relativePos.x / trackSize.x;
		relativePos.z = relativePos.z / trackSize.z;

		mainPlayerPosOnMapUI = glm::vec2(relativePos.z, relativePos.x);

		partOfTheMapDisplayed.x = clip(mainPlayerPosOnMapUI.x - PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2, 0, 1);
		partOfTheMapDisplayed.y = clip(mainPlayerPosOnMapUI.y - PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2, 0, 1);
		partOfTheMapDisplayed.z = clip(mainPlayerPosOnMapUI.x + PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2, 0, 1);
		partOfTheMapDisplayed.w = clip(mainPlayerPosOnMapUI.y + PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2, 0, 1);

		cutOffs = glm::vec4(
			-(mainPlayerPosOnMapUI.x - PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2 - partOfTheMapDisplayed.x) / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE,			//left border
			-(mainPlayerPosOnMapUI.y - PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2 - partOfTheMapDisplayed.y) / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE,			//bottom border
			(mainPlayerPosOnMapUI.x + PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2 - partOfTheMapDisplayed.z) / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE,			//right border
			(mainPlayerPosOnMapUI.y + PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE / 2 - partOfTheMapDisplayed.w) / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE			//top border
			);
	}

	{
		glm::vec3 pos = m_animatable->getPosition();
		glm::vec3 size = m_animatable->getScale();

		mapVertexCoords = glm::vec4(
			pos.x - size.x / 2 + size.x * cutOffs.x,				//min x
			pos.y - size.y / 2 + size.y * cutOffs.y,				//min y
			pos.x + size.x / 2 - size.x * cutOffs.z,				//max x
			pos.y + size.y / 2 - size.y * cutOffs.w					//max y
			);

		glColor3f(1.f, 1.f, 1.f);
		Model2D *model = static_cast<Model2D*>(m_renderable->getModel());
		model->getTexture()->Bind(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//bottom left
		glTexCoord2f(std::max(partOfTheMapDisplayed.x, 0.f), std::min(1 - partOfTheMapDisplayed.y, 1.f));
		glVertex2f(mapVertexCoords.x, mapVertexCoords.y);
		//bottom right
		glTexCoord2f(std::min(partOfTheMapDisplayed.z, 1.f), std::min(1 - partOfTheMapDisplayed.y, 1.f));
		glVertex2f(mapVertexCoords.z, mapVertexCoords.y);
		//top right
		glTexCoord2f(std::min(partOfTheMapDisplayed.z, 1.f), std::max(1 - partOfTheMapDisplayed.w, 0.f));
		glVertex2f(mapVertexCoords.z, mapVertexCoords.w);
		//top left
		glTexCoord2f(std::max(partOfTheMapDisplayed.x, 0.f), std::max(1 - partOfTheMapDisplayed.w, 0.f));
		glVertex2f(mapVertexCoords.x, mapVertexCoords.w);
		glEnd();
		model->getTexture()->unBind(GL_TEXTURE_2D);
	}
}


void MapUI::drawPlayers() {

	partOfTheMapDisplayed = clip(partOfTheMapDisplayed, 0, 1);
	for (unsigned int i = 0; i < players->size(); i++) {

		Texture *tex = NULL;
		if (dynamic_cast<MeowMix *>(players->at(i)->getCar()) != NULL)
		{
			tex = meowModel->getTexture();
		}
		if (dynamic_cast<Gargantulous *>(players->at(i)->getCar()) != NULL)
		{
			tex = gargModel->getTexture();
		}
		if (dynamic_cast<ExplosivelyDelicious *>(players->at(i)->getCar()) != NULL)
		{
			tex = explosiveModel->getTexture();
		}
		tex->Bind(GL_TEXTURE_2D);

		PxVec3 playerPos = players->at(i)->getCar()->getActor().getGlobalPose().p;
		glm::vec3 playerDimensions = playerSizes.at(i);
		glm::vec3 relativePos = (glm::vec3(playerPos.x, playerPos.y, playerPos.z) - trackMinBounds);
		relativePos.x = relativePos.x / trackSize.x;
		relativePos.z = relativePos.z / trackSize.z;

		//if out of bound of the displayed map, don't render the player
		if (relativePos.z > partOfTheMapDisplayed.z ||
			relativePos.z < partOfTheMapDisplayed.x ||
			relativePos.x > partOfTheMapDisplayed.w ||
			relativePos.x < partOfTheMapDisplayed.y)
			continue;

		playerDimensions.x = playerDimensions.x / trackSize.x / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE;
		playerDimensions.z = playerDimensions.z / trackSize.z / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE;

		//rescale according to the part that is being displayed
		glm::vec2 relativePosToMainPlayer = glm::vec2(relativePos.z, relativePos.x) - mainPlayerPosOnMapUI;

		glm::vec3 pos = m_animatable->getPosition();
		glm::vec3 size = m_animatable->getScale();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(pos.x + size.x * relativePosToMainPlayer.x / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE, pos.y + size.y * relativePosToMainPlayer.y / PERCENTAGE_OF_MAP_TO_DISPLAY_ZERO_TO_ONE, -1);
		glColor3f(1.f, 1.f, 1.f);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-playerDimensions.z, -playerDimensions.x, 0);
		glTexCoord2f(1, 0);
		glVertex3f(playerDimensions.z, -playerDimensions.x, 0);
		glTexCoord2f(1, 1);
		glVertex3f(playerDimensions.z, playerDimensions.x, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-playerDimensions.z, playerDimensions.x, 0);
		glEnd();

		tex->unBind(GL_TEXTURE_2D);
	}

}


void MapUI::drawBackground() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::vec3 pos = m_animatable->getPosition();
	glm::vec3 size = m_animatable->getScale();

	glColor3f(30 / 255.f, 30 / 255.f, 34 / 255.f);
	glBegin(GL_QUADS);
	glVertex3f(pos.x - size.x / 2, pos.y - size.y / 2, 0);
	glVertex3f(pos.x + size.x / 2, pos.y - size.y / 2, 0);
	glVertex3f(pos.x + size.x / 2, pos.y + size.y / 2, 0);
	glVertex3f(pos.x - size.x / 2, pos.y + size.y / 2, 0);
	glEnd();


}

bool MapUI::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (passNumber < 2)
		return true;

	if (passNumber > 2)
		return false;

	if (type != Renderer::ShaderType::SHADER_TYPE_NONE)
		return false;

	glDisable(GL_DEPTH_TEST);
	drawBackground();
	drawMap();
	drawPlayers();
	glEnable(GL_DEPTH_TEST);

	return false;

}

void MapUI::setPlayers(std::vector<Controllable *> *players) {

	this->players = players;
	for (unsigned int i = 0; i < players->size(); i++) {
		PxVec3 playerSize = players->at(i)->getCar()->getWorldBounds().getDimensions();
		playerSizes.push_back(glm::vec3(playerSize.x, playerSize.y, playerSize.z));
	}

}