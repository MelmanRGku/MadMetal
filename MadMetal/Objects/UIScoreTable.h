#pragma once

#include "Object2D.h"

class ScoreTable;
class FTBitmapFont;

class UIScoreTable : public Object2D
{
private:
	ScoreTable *m_table;
	FTBitmapFont *font;
	int xDistBetweenNameAndPlace;
	int xDistBetweenPlaceAndScore;
	int yDistBetweenLines;
	float fontSize;
	std::string ownerName;
public:
	UIScoreTable(long id, Audioable *aable, Animatable *anable, Renderable2D *rable);
	~UIScoreTable();
	void setScoreTable(ScoreTable *table);
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	void setFontSize(float fontSize);
	float getFontSize() { return fontSize; }
	void setOwnerName(std::string name) { ownerName = name; }
};

