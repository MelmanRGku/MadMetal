#include "Camera.h"
#include <iostream>
#include "Libraries\glm\gtx\rotate_vector.hpp"


#define CAMERA_ROTATION_SPEED 0.1
#define CAMERA_GRAVITY_SPEED 0.01
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

void Camera::rotateCamera(float degrees)
{
	if (degrees != 0)
	{
		m_rotation -= glm::vec3(0, degrees * m_rotateScalar, 0);
		m_currentPos = m_lookAt + glm::rotate((m_desiredPos - m_lookAt), m_rotation.y, glm::vec3(0, 1, 0));
		m_recentlyMoved = true;
		
	}
	else {
		m_recentlyMoved = false;
		
	}
	

}

void Camera::update(double dtMilli)
{
	m_lookAt = glm::vec3(m_toFollow->getActor().getGlobalPose().p.x, m_toFollow->getActor().getGlobalPose().p.y, m_toFollow->getActor().getGlobalPose().p.z);
	m_desiredPos = m_lookAt - m_toFollow->getForwardVector() * m_distance;

	if (!m_recentlyMoved)
	{
		/*/for each rotation out of wak
		if (abs(m_currentPos.x - m_desiredPos.x) > 0.1)
		{
			m_currentPos = glm::rotate((m_currentPos - m_lookAt), m_gravityScalar, glm::vec3(0, 1, 0));
		} 
		if (abs (m_currentPos.y - m_desiredPos.y) > 0.1)
		{
			//m_currentPos = glm::rotate((m_currentPos - m_lookAt), m_gravityScalar, glm::vec3(0, 1, 0));
		}
		if (abs(m_currentPos.z - m_desiredPos.z) > 0.1)
		{
			//m_currentPos = glm::rotate((m_currentPos - m_lookAt), m_gravityScalar, glm::vec3(0, 0, 1));
		}
		*/
	}

}

