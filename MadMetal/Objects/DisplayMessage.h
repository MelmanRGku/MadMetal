#pragma once
#include "Text2D.h"
#include <string>

class DisplayMessage : public Object2D
{
public:
	DisplayMessage(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
	{
		m_centerOfScreen = glm::vec3(std::stof(Settings::getSetting("screenWidth")) / 2, std::stof(Settings::getSetting("screenHeight")) / 2, 0);
	}
	~DisplayMessage(){ 
	
	}

	void setText2D(Text2D * text2d) { m_message = text2d; }
	
	void initializeMessage(std::string text, float durationSeconds) 
	{
		m_messageLife = -durationSeconds;
		m_message->setString(text);
		m_message->setPosition(m_centerOfScreen);
	}
	virtual void update(float dtMillis)
	{
		if ((m_messageLife += dtMillis) >= 0)
		{
			m_message->setString("");
		}

	}
	void setFontSize(float size)  { m_message->setFontSize(size); }
	void resetFontSize() { m_message->resetFontSize(); }
private: // members
	float m_messageLife;
	glm::vec3 m_centerOfScreen;
	Text2D* m_message;
};