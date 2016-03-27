#include "UIScoreTable.h"
#include "ScoreTable.h"


UIScoreTable::UIScoreTable(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
{
	font = new FTBitmapFont("Assets/Fonts/OpenSans-Bold.ttf");
	fontSize = glutGet(GLUT_WINDOW_HEIGHT) * 0.05;
	xDistBetweenNameAndPlace = fontSize * 5;
	xDistBetweenPlaceAndScore = fontSize * 3;
	yDistBetweenLines = fontSize;
	font->FaceSize(fontSize);
}


UIScoreTable::~UIScoreTable()
{
}

void UIScoreTable::setScoreTable(ScoreTable *table) {
	m_table = table; 
}

bool UIScoreTable::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
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

	std::vector<std::string> names = m_table->getPlayerNames(), 
		points = m_table->getPlayerPointsStrings(),
		positionsInRace = m_table->getPlayerPositionsInRaceStrings();

	font->Render("  Name     Pos  Score", -1, FTPoint(pos.x, pos.y, pos.z));

	int yOffset = yDistBetweenLines;
	for (int i = 0; i < names.size(); i++) {
		if (ownerName.compare(names.at(i)) == 0)
			font->Render("    You", -1, FTPoint(pos.x, pos.y - yOffset, pos.z));
		else 
			font->Render(names.at(i).c_str(), -1, FTPoint(pos.x, pos.y - yOffset, pos.z));
		font->Render(positionsInRace.at(i).c_str(), -1, FTPoint(pos.x + xDistBetweenNameAndPlace, pos.y - yOffset, pos.z));
		font->Render(points.at(i).c_str(), -1, FTPoint(pos.x + xDistBetweenNameAndPlace + xDistBetweenPlaceAndScore, pos.y - yOffset, pos.z));
		yOffset += yDistBetweenLines;
	}

	glPopAttrib();

	return false;
}

void UIScoreTable::setFontSize(float fontSize) {
	this->fontSize = fontSize; 
	font->FaceSize(fontSize);
	xDistBetweenNameAndPlace = fontSize * 5;
	xDistBetweenPlaceAndScore = fontSize * 3;
	yDistBetweenLines = fontSize;
}