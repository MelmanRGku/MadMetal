#include "Camera.h"
#include <iostream>
#include "Libraries\glm\gtx\rotate_vector.hpp"
#include "Factory\GameFactory.h"

#define CAMERA_ROTATION_SPEED 0.1f
#define CAMERA_GRAVITY_SPEED 0.001f
#define PI 3.14159265359
Camera::Camera()
{

	m_rotateScalar = CAMERA_ROTATION_SPEED;
	m_gravityScalar = CAMERA_GRAVITY_SPEED;
	m_distance = 15; 
	m_distanceDt = .05f;
	m_distanceMin = 3;
	m_distanceMax = 20;
	m_recentlyMoved = false;
	m_inclinationAngle = 70.0f;

	m_currentPos = glm::vec3(0, 0, m_distance);

	m_lookAt = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
	m_rotation = glm::vec3(0, 0, 0);

}

Camera::Camera(Object3D * object)
{
	m_rotateScalar = CAMERA_ROTATION_SPEED;
	m_gravityScalar = CAMERA_GRAVITY_SPEED;
	m_distance = 50;
	m_recentlyMoved = false;

	if (object != NULL)
	{
		m_toFollow = object;
		m_currentPos = m_toFollow->getForwardVector() * (-m_distance);
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
	m_toFollow = NULL;
}

glm::vec3 Camera::getLookAt(){ return m_lookAt; }
glm::vec3 Camera::getPosition(){ return m_currentPos; }
glm::vec3 Camera::getUpVector() { return m_up; }


void Camera::setToFollow(Object3D * object)
{
	m_toFollow = object;
	m_up = glm::vec3(0, 1, 0);
	m_currentPos = m_toFollow->getForwardVector() * -m_distance;
}

void Camera::rotateCamera(float xpos, float ypos)
{

	//m_currentPos.x += xpos;
	//m_currentPos.z += ypos;
	/*to do: 
		1. Make it so rotation only effects x and y coords, z will be be bouncy? Need to implement that in update aswell
		*/
	float rotate = (float)acos(xpos);

		if (ypos > 0 )
		{ 
			
			//m_lookAt += glm::vec3(0, ypos, 0);
			if(xpos <= 0)
			{
				m_currentPos = m_lookAt + glm::rotate((m_currentPos - m_lookAt), (float)(PI / 2 + rotate), glm::vec3(0, 1, 0));
				

			}
			else {
				m_currentPos = m_lookAt + glm::rotate((m_currentPos - m_lookAt), (float)(PI / 2 + rotate), glm::vec3(0, 1, 0));
			}
		}
		else {
		
			if (xpos <= 0)
			{
				m_currentPos = m_lookAt + glm::rotate(glm::normalize(m_currentPos - m_lookAt), (float)(PI / 2 - rotate), glm::vec3(0, 1, 0)) * m_distance;
			

			}
			else {
				m_currentPos = m_lookAt + glm::rotate(glm::normalize(m_currentPos - m_lookAt), (float)(PI / 2 - rotate), glm::vec3(0, 1, 0)) * m_distance;
			}
		}
		
}

void Camera::update(double dtMilli)
{
	
	m_lookAt = glm::vec3(m_toFollow->getGlobalPose().x, m_toFollow->getGlobalPose().y, m_toFollow->getGlobalPose().z);
	m_desiredPos = (m_toFollow->getFullPosition() - m_toFollow->getForwardVector() * m_distance);
	m_currentPos = glm::vec3(m_desiredPos.x, m_toFollow->getFullPosition().y + 7.0f, m_desiredPos.z);
	
	PxRaycastBuffer buf;
	PxQueryFilterData fd(PxQueryFlag::eSTATIC);

	glm::vec3 cameraDirection = glm::normalize(m_lookAt - m_currentPos);
	PxVec3 rayPos = PxVec3(m_currentPos.x, m_currentPos.y, m_currentPos.z);
	PxVec3 rayDir = PxVec3(cameraDirection.x, cameraDirection.y, cameraDirection.z);

	GameFactory::instance()->sceneRayCast(rayPos, rayDir, glm::distance(m_lookAt, m_currentPos) - 5.f, buf, PxHitFlags(PxHitFlag::eMESH_BOTH_SIDES), fd);

	if (buf.hasBlock) {
		PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*1);
		buf.block.actor->getShapes(shapes, 1);
		if (shapes[0]->getSimulationFilterData().word0 == COLLISION_FLAG_OBSTACLE) {
			m_distance = glm::distance(m_lookAt, m_currentPos) - buf.block.distance - .5f;
		}
		free(shapes);
	}
	else {
		m_distance += m_distanceDt;
		if (m_distance > m_distanceMax)
			m_distance = m_distanceMax;

		m_lookAt = glm::vec3(m_toFollow->getGlobalPose().x, m_toFollow->getGlobalPose().y, m_toFollow->getGlobalPose().z);
		m_desiredPos = (m_toFollow->getFullPosition() - m_toFollow->getForwardVector() * m_distance);
		m_currentPos = glm::vec3(m_desiredPos.x, m_toFollow->getFullPosition().y + 7.0f, m_desiredPos.z);
		glm::vec3 cameraDirection = glm::normalize(m_lookAt - m_currentPos);
		PxVec3 rayPos = PxVec3(m_currentPos.x, m_currentPos.y, m_currentPos.z);
		PxVec3 rayDir = PxVec3(cameraDirection.x, cameraDirection.y, cameraDirection.z);

		//perform the raycast again
		GameFactory::instance()->sceneRayCast(rayPos, rayDir, glm::distance(m_lookAt, m_currentPos) - 5.f, buf, PxHitFlags(PxHitFlag::eMESH_ANY));
		if (buf.hasBlock) {
			PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)* 1);
			buf.block.actor->getShapes(shapes, 1);
			if (shapes[0]->getSimulationFilterData().word0 == COLLISION_FLAG_OBSTACLE) {
				m_distance = glm::distance(m_lookAt, m_currentPos) - buf.block.distance - .5f;
			}
			free(shapes);
		}
	}

}

void Camera::setLookAt(glm::vec3 eye, glm::vec3 at, glm::vec3 up) {
	m_currentPos = eye;
	m_lookAt = at;
	m_up = up;
}


glm::mat4x4 Camera::getMatrix() {
	return glm::lookAt(
		m_currentPos,
		m_lookAt,
		m_up
		);
}