#pragma once
#include "Text2D.h"
#include <string>

class DisplayMessage : public TestObject
{
public:
	DisplayMessage(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable *rable) : TestObject(id, aable, pable, anable, rable, NULL)
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
		m_message->setPos(m_centerOfScreen);
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