#include "Camera.h"
#include <iostream>
#include "Libraries\glm\gtx\rotate_vector.hpp"


#define CAMERA_ROTATION_SPEED 0.1f
#define CAMERA_GRAVITY_SPEED 0.001f
#define PI 3.14159265359
Camera::Camera()
{

	m_rotateScalar = CAMERA_ROTATION_SPEED;
	m_gravityScalar = CAMERA_GRAVITY_SPEED;
	m_distance = 10;
	m_recentlyMoved = false;


	m_currentPos = glm::vec3(0, 0, m_distance);

	m_lookAt = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
	m_rotation = glm::vec3(0, 0, 0);

}

Camera::Camera(Object * object)
{
	m_rotateScalar = CAMERA_ROTATION_SPEED;
	m_gravityScalar = CAMERA_GRAVITY_SPEED;
	m_distance = 10;
	m_recentlyMoved = false;

	if (object != NULL)
	{
		m_toFollow = object;
		m_currentPos = m_desiredPos = m_toFollow->getForwardVector() * (-m_distance);
		m_lookAt = m_toFollow->getPosition();
		m_up = glm::vec3(0, 1, 0);
		m_rotation = glm::vec3(0, 0, 0);
	}
	else {
		std::cout << "Null pointer passed to Camera constructor \n";
	}
}


Camera::~Camera()
{
	delete m_toFollow;
}

glm::vec3 Camera::getLookAt(){ return m_lookAt; }
glm::vec3 Camera::getPosition(){ return m_currentPos; }
glm::vec3 Camera::getUpVector() { return m_up; }


void Camera::setToFollow(Object * object)
{
	m_toFollow = object;
	m_currentPos = m_desiredPos = m_toFollow->getForwardVector() * (-m_distance);
	m_lookAt = m_toFollow->getPosition();
	m_up = glm::vec3(0, 1, 0);
	m_rotation = glm::vec3(0, 0, 0);
}

void Camera::rotateCamera(float xpos, float ypos)
{

	/*to do: 
		1. Make it so rotation only effects x and y coords, z will be be bouncy? Need to implement that in update aswell
		*/
	float rotate = (float)acos(xpos);
		if (ypos > 0 )
		{
			if(xpos <= 0)
			{
				m_currentPos = m_lookAt + glm::rotate((m_desiredPos - m_lookAt), (float)(PI / 2 + rotate), glm::vec3(0, 1, 0));
				

			}
			else {
				m_currentPos = m_lookAt + glm::rotate((m_desiredPos - m_lookAt), (float)(PI / 2 + rotate), glm::vec3(0, 1, 0));
			}
		}
		else {
		
			if (xpos <= 0)
			{
				m_currentPos = m_lookAt + glm::rotate((m_desiredPos - m_lookAt), (float)(PI / 2 - rotate), glm::vec3(0, 1, 0));
			

			}
			else {
				m_currentPos = m_lookAt + glm::rotate((m_desiredPos - m_lookAt), (float)(PI / 2 - rotate), glm::vec3(0, 1, 0));
			}
		}
		m_currentPos.y = 3;
	
	
	
	

}

void Camera::update(double dtMilli)
{

	/*to do:
	1. Add functionality so z will be be tracked over time.
	2. Add functionality so camera will 'lean' as the player goes around a turn
		-Need to look at turning forces on car?
	*/

	m_lookAt = glm::vec3(m_toFollow->getActor().getGlobalPose().p.x, 3, m_toFollow->getActor().getGlobalPose().p.z);
	m_desiredPos = m_lookAt - m_toFollow->getForwardVector() * m_distance;
	glm::vec3 temp = m_lookAt - m_currentPos;
	float theta = glm::dot(glm::normalize(glm::vec2(m_desiredPos.x, m_desiredPos.z)), glm::normalize(glm::vec2(temp.x, temp.z)));
	
	//std::cout << theta << std::endl;
	//std::cout << temp.x * m_desiredPos.x + temp.z * m_desiredPos.z << std::endl;
	
	//std::cout << m_currentPos.x << "," << m_currentPos.y << "," << m_currentPos.z << std::endl;
	//std::cout << m_desiredPos.x << "," << m_desiredPos.y << "," << m_desiredPos.z << std::endl << std::endl;
	/*
	//find angle between the current and desired position of camera
	float theta = glm::dot(glm::normalize(m_currentPos), glm::normalize(m_desiredPos));
	
	if (theta < 1)
	{
		//find normal to the two vectors
		glm::vec3 rotationAxis = glm::cross(m_currentPos, m_desiredPos);
		m_currentPos = m_lookAt + glm::rotate((m_currentPos - m_lookAt), m_gravityScalar, rotationAxis);
	}

	

	
	
	//std::cout << theta <<std::endl;
	*/
		
	

}

