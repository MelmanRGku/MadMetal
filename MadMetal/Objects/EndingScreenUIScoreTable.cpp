#include "EndingScreenUIScoreTable.h"
#include "Libraries\freeglut\freeglut.h"
#include "Libraries\ftgl\FTGL\ftgl.h"
#include <sstream>


EndingScreenUIScoreTable::EndingScreenUIScoreTable(long id, Audioable *aable, Animatable *anable, Renderable2D *rable, std::vector<ControllableTemplate *> playerTemplates) : Object2D(id, aable, anable, rable)
{
	this->playerTemplates = playerTemplates;
	font = new FTBitmapFont("Assets/Fonts/OpenSans-Bold.ttf");
	fontSize = glutGet(GLUT_WINDOW_HEIGHT) * 0.04;
	xDistBetweenNameAndPlace = fontSize * 5;
	xDistBetweenPlaceAndScore = fontSize * 3;
	yDistBetweenLines = fontSize;
	font->FaceSize(fontSize);
}


EndingScreenUIScoreTable::~EndingScreenUIScoreTable()
{
	delete font;
}

bool EndingScreenUIScoreTable::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	if (type != Renderer::ShaderType::SHADER_TYPE_NONE || passNumber > 1)
		return false;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	glColor4f(1.0, 0.0, 0.0, 1.0);
	// Set the font size and render a small text.	
	glm::vec3 pos = m_animatable->getPosition();
	std::string name, poss, score;
	int yOffset = yDistBetweenLines;


	font->Render("  Name     Pos  Score", -1, FTPoint(pos.x, pos.y - yOffset, pos.z));

	yOffset += yDistBetweenLines;
	for (int i = 0; i < playerTemplates.size(); i++) {


		std::stringstream ss;
		ss << "Player " << playerTemplates.at(i)->getPlayerNumber();
		name = ss.str();


		ss.str(std::string());
		ss << playerTemplates.at(i)->getFinalPosition();
		if (playerTemplates.at(i)->getFinalPosition() == 1)
			ss << "st";
		else if (playerTemplates.at(i)->getFinalPosition() == 2)
			ss << "nd";
		else if (playerTemplates.at(i)->getFinalPosition() == 3)
			ss << "rd";
		else
			ss << "th";
		poss = ss.str();


		ss.str(std::string());
		ss << playerTemplates.at(i)->getFinalScore();
		score = ss.str();


		font->Render(name.c_str(), -1, FTPoint(pos.x, pos.y - yOffset, pos.z));
		font->Render(poss.c_str(), -1, FTPoint(pos.x + xDistBetweenNameAndPlace, pos.y - yOffset, pos.z));
		font->Render(score.c_str(), -1, FTPoint(pos.x + xDistBetweenNameAndPlace + xDistBetweenPlaceAndScore, pos.y - yOffset, pos.z));
		yOffset += yDistBetweenLines;
	}

	glPopAttrib();

	return false;
}

void EndingScreenUIScoreTable::setFontSize(float fontSize) {
	this->fontSize = fontSize;
	font->FaceSize(fontSize);
	xDistBetweenNameAndPlace = fontSize * 5;
	xDistBetweenPlaceAndScore = fontSize * 3;
	yDistBetweenLines = fontSize;
}