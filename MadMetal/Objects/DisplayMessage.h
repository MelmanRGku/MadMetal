#pragma once
#include "Text2D.h"
#include <string>
#include "Libraries\freeglut\freeglut.h"

class DisplayMessage : public Object2D
{
public:
	DisplayMessage(long id, Audioable *aable, Animatable *anable, Renderable2D *rable) : Object2D(id, aable, anable, rable)
	{
		m_centerOfScreen = glm::vec3(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, 0);
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
	void setCenterOfScreen(glm::vec3 center) { m_centerOfScreen = center; }
	virtual void update(float dtMillis)
	{
		if ((m_messageLife += dtMillis) >= 0)
		{
			m_message->setString("");
		}

	}
	void setFontSize(float size)  { m_message->setFontSize(size); }
	void resetFontSize() { m_message->resetFontSize(); }
	Text2D *getText2D() { return m_message; }
private: // members
	float m_messageLife;
	glm::vec3 m_centerOfScreen;
	Text2D* m_message;
};