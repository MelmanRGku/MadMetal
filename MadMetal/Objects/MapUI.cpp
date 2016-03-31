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

bool MapUI::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;


	//----------------------------------------------------------
	//--------------DRAW THE MAP--------------------------------
	//----------------------------------------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#define PERCENTAGE_OF_MAP_TO_DISPLAY 40
#define PERCENTAGE_OF_MAP_TO_DISPLAY_IN_MAP_COORDS (PERCENTAGE_OF_MAP_TO_DISPLAY / 100.f)
	glm::vec4 partOfTheMapDisplayed;
	{
		PxVec3 playerPos = mainPlayer->getCar()->getActor().getGlobalPose().p;
		glm::vec3 relativePos = (glm::vec3(playerPos.x, playerPos.y, playerPos.z) - trackMinBounds);
		relativePos.x = relativePos.x / trackSize.x;
		relativePos.z = relativePos.z / trackSize.z;
		glm::vec2 playerPosOnMapUI = glm::vec2(relativePos.z, relativePos.x);
		partOfTheMapDisplayed.x = playerPosOnMapUI.x - PERCENTAGE_OF_MAP_TO_DISPLAY_IN_MAP_COORDS;
		partOfTheMapDisplayed.y = playerPosOnMapUI.y - PERCENTAGE_OF_MAP_TO_DISPLAY_IN_MAP_COORDS;
		partOfTheMapDisplayed.z = playerPosOnMapUI.x + PERCENTAGE_OF_MAP_TO_DISPLAY_IN_MAP_COORDS;
		partOfTheMapDisplayed.w = playerPosOnMapUI.y + PERCENTAGE_OF_MAP_TO_DISPLAY_IN_MAP_COORDS;
	}

	{
		glm::vec3 pos = m_animatable->getPosition();
		glm::vec3 size = m_animatable->getScale();
		glColor3f(1.f, 1.f, 1.f);
		Model2D *model = static_cast<Model2D*>(m_renderable->getModel());
		model->getTexture()->Bind(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		float bottomCutOff = (partOfTheMapDisplayed.w > 1) ? partOfTheMapDisplayed.w - 1 : 0;
		float topCutOff = (partOfTheMapDisplayed.y < 0) ? -partOfTheMapDisplayed.y : 0;
		float rightCutOff = (partOfTheMapDisplayed.x < 0) ? -partOfTheMapDisplayed.x : 0;
		float leftCutOff = (partOfTheMapDisplayed.z > 1) ? partOfTheMapDisplayed.z - 1 : 0;
		//bottom left
		glTexCoord2f(std::max(partOfTheMapDisplayed.x, 0.f), std::min(1 - partOfTheMapDisplayed.y, 1.f));
		glVertex2f(pos.x - size.x / 2 + leftCutOff * size.x, pos.y - size.y / 2 + bottomCutOff * size.y);
		//bottom right
		glTexCoord2f(std::min(partOfTheMapDisplayed.z, 1.f), std::min(1 - partOfTheMapDisplayed.y, 1.f));
		glVertex2f(pos.x + size.x / 2 - rightCutOff * size.x, pos.y - size.y / 2 + bottomCutOff * size.y);
		//top right
		glTexCoord2f(std::min(partOfTheMapDisplayed.z, 1.f), std::max(1 - partOfTheMapDisplayed.w, 0.f));
		glVertex2f(pos.x + size.x / 2 - rightCutOff * size.x, pos.y + size.y / 2 - topCutOff * size.y);
		//top left
		glTexCoord2f(std::max(partOfTheMapDisplayed.x, 0.f), std::max(1 - partOfTheMapDisplayed.w, 0.f));
		glVertex2f(pos.x - size.x / 2 + leftCutOff * size.x, pos.y + size.y / 2 - topCutOff * size.y);
		glEnd();
		model->getTexture()->unBind(GL_TEXTURE_2D);
	}

	//----------------------------------------------------------
	//-------------- END DRAW THE MAP---------------------------
	//----------------------------------------------------------









	//----------------------------------------------------------
	//--------------DRAW THE PLAYERS----------------------------
	//----------------------------------------------------------


	for (unsigned int i = 0; i < players->size(); i++) {

		if (dynamic_cast<MeowMix *>(players->at(i)->getCar()) != NULL)
		{
			meowModel->getTexture()->Bind(GL_TEXTURE_2D);
		}
		if (dynamic_cast<Gargantulous *>(players->at(i)->getCar()) != NULL)
		{
			gargModel->getTexture()->Bind(GL_TEXTURE_2D);
		}
		if (dynamic_cast<ExplosivelyDelicious *>(players->at(i)->getCar()) != NULL)
		{
			explosiveModel->getTexture()->Bind(GL_TEXTURE_2D);
		}
		PxVec3 playerPos = players->at(i)->getCar()->getActor().getGlobalPose().p;
		glm::vec3 playerDimensions = playerSizes.at(i);
		glm::vec3 relativePos = (glm::vec3(playerPos.x, playerPos.y, playerPos.z) - trackMinBounds);
		relativePos.x = relativePos.x / trackSize.x;
		relativePos.z = relativePos.z / trackSize.z;

		playerDimensions.x = (playerDimensions.x / (trackSize.x * 2 * (partOfTheMapDisplayed.w - partOfTheMapDisplayed.y))) * 2;
		playerDimensions.z = (playerDimensions.z / (trackSize.z * 2 * (partOfTheMapDisplayed.z - partOfTheMapDisplayed.x))) * 2;

		//if out of bound of the displayed map, don't render the player
		if (relativePos.z > partOfTheMapDisplayed.z ||
			relativePos.z < partOfTheMapDisplayed.x ||
			relativePos.x > partOfTheMapDisplayed.w ||
			relativePos.x < partOfTheMapDisplayed.y)
			continue;

		//rescale according to the part that is being displayed
		relativePos.x = (relativePos.x - partOfTheMapDisplayed.y) / (partOfTheMapDisplayed.w - partOfTheMapDisplayed.y);
		relativePos.z = (relativePos.z - partOfTheMapDisplayed.x) / (partOfTheMapDisplayed.z - partOfTheMapDisplayed.x);


		glm::vec3 pos = m_animatable->getPosition();
		glm::vec3 size = m_animatable->getScale();
		glm::vec2 playerPosOnMapUI = glm::vec2(pos.x - size.x / 2 + relativePos.z * size.x, pos.y - size.y / 2 + relativePos.x * size.y);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(playerPosOnMapUI.x, playerPosOnMapUI.y, -1);
//		glm::vec2 normalVector = glm::normalize(glm::vec2(0, -1));
//		glm::vec2 forwardVector = glm::normalize(glm::vec2(players->at(i)->getCar()->getForwardVector().x, players->at(i)->getCar()->getForwardVector().z));
//		float angle = glm::degrees(glm::orientedAngle(normalVector, forwardVector));
//		glRotatef(angle, 0, 0, -1);


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

		if (dynamic_cast<MeowMix *>(players->at(i)->getCar()) == NULL)
		{
			meowModel->getTexture()->unBind(GL_TEXTURE_2D);
		}
		if (dynamic_cast<Gargantulous *>(players->at(i)->getCar()) == NULL)
		{
			gargModel->getTexture()->unBind(GL_TEXTURE_2D);
		}
		if (dynamic_cast<ExplosivelyDelicious *>(players->at(i)->getCar()) == NULL)
		{
			explosiveModel->getTexture()->unBind(GL_TEXTURE_2D);
		}
	}



	//----------------------------------------------------------
	//--------------END DRAW THE PLAYERS------------------------
	//----------------------------------------------------------

	return false;

}

void MapUI::setPlayers(std::vector<Controllable *> *players) {

	this->players = players;
	for (unsigned int i = 0; i < players->size(); i++) {
		PxVec3 playerSize = players->at(i)->getCar()->getWorldBounds().getDimensions();
		playerSizes.push_back(glm::vec3(playerSize.x, playerSize.y, playerSize.z));
	}

}