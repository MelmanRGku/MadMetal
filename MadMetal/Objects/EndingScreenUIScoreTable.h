#pragma once

#include "Object2D.h"
#include "Game Logic\ControllableTemplate.h"

class ScoreTable;
class FTBitmapFont;

class EndingScreenUIScoreTable : public Object2D
{
private:
	FTBitmapFont *font;
	int xDistBetweenNameAndPlace;
	int xDistBetweenPlaceAndScore;
	int yDistBetweenLines;
	float fontSize;
	std::string ownerName;
	std::vector<ControllableTemplate *> playerTemplates;
public:
	EndingScreenUIScoreTable(long id, Audioable *aable, Animatable *anable, Renderable2D *rable, std::vector<ControllableTemplate *> playerTemplates);
	~EndingScreenUIScoreTable();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setFontSize(float fontSize);
	float getFontSize() { return fontSize; }
	void setOwnerName(std::string name) { ownerName = name; }
};