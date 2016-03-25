#pragma once

#include "PxPhysicsAPI.h"
#include "Libraries\glm\vec3.hpp"


extern glm::vec3 forwardVector;
extern glm::vec3 upVector;

enum
{
	DRIVABLE_SURFACE = 0xffff0000,
	UNDRIVABLE_SURFACE = 0x0000ffff
};

using namespace physx;

/*enum
{
	DRIVABLE_SURFACE = 0xffff0000,
	UNDRIVABLE_SURFACE = 0x0000ffff
};*/

extern PxF32 gSteerVsForwardSpeedData[2 * 8];

//Drivable surface types.
enum
{
	SURFACE_TYPE_TARMAC = 0,
	MAX_NUM_SURFACE_TYPES
};

//Tire types.
enum
{
	TIRE_TYPE_NORMAL = 0,
	TIRE_TYPE_WORN,
	MAX_NUM_TIRE_TYPES
};

extern PxVehicleKeySmoothingData gKeySmoothingData;

extern PxVehiclePadSmoothingData gPadSmoothingData;

extern enum DriveMode;

extern PxF32 gTireFrictionMultipliers[MAX_NUM_SURFACE_TYPES][MAX_NUM_TIRE_TYPES];

enum
{
	COLLISION_FLAG_GROUND = 1 << 0,
	COLLISION_FLAG_WHEEL = 1 << 1,
	COLLISION_FLAG_CHASSIS = 1 << 2,
	COLLISION_FLAG_OBSTACLE = 1 << 3,
	COLLISION_FLAG_DRIVABLE_OBSTACLE = 1 << 4,
	COLLISION_FLAG_BULLET = 1 << 5,
	COLLISION_FLAG_WAYPOINT = 1 << 6,
	COLLISION_FLAG_COLLISION_VOLUME = 1 << 7,
	COLLISION_FLAG_POWERUP = 1 << 8,
	COLLISION_FLAG_SHIELD_POWERUP = 1 << 9,
	COLLISION_FLAG_SPEED_POWERUP = 1 << 10,
	COLLISION_FLAG_DEATH_VOLUME = 1 << 11,
	COLLISION_FLAG_PARTICLE = 1 << 12,
	COLLISION_FLAG_EXPLOSIVELY_DELICIOUS_SUPER = 1 << 13,

	COLLISION_FLAG_GROUND_AGAINST = COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
	COLLISION_FLAG_WHEEL_AGAINST = COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_WAYPOINT,
	COLLISION_FLAG_CHASSIS_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE | COLLISION_FLAG_WAYPOINT | COLLISION_FLAG_COLLISION_VOLUME,
	COLLISION_FLAG_OBSTACLE_AGAINST = COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS, 
	COLLISION_FLAG_DRIVABLE_OBSTACLE_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
	COLLISION_FLAG_BULLET_AGAINST = COLLISION_FLAG_GROUND | COLLISION_FLAG_WHEEL | COLLISION_FLAG_CHASSIS | COLLISION_FLAG_OBSTACLE | COLLISION_FLAG_DRIVABLE_OBSTACLE,
	COLLISION_FLAG_WAYPOINT_AGAINST = COLLISION_FLAG_CHASSIS | COLLISION_FLAG_WHEEL,
	COLLISION_FLAG_COLLISION_VOLUME_AGAINST = COLLISION_FLAG_CHASSIS | COLLISION_FLAG_WHEEL,
	COLLISION_FLAG_POWERUP_AGAINST = COLLISION_FLAG_CHASSIS,
	COLLISION_FLAG_SHIELD_POWERUP_AGAINST = COLLISION_FLAG_BULLET,
	COLLISION_FLAG_SPEED_POWERUP_AGAINST = COLLISION_FLAG_CHASSIS, 
	COLLISION_FLAG_DEATH_VOLUME_AGAINST = COLLISION_FLAG_CHASSIS,
	COLLISION_FLAG_EXPLOSIVELY_DELICIOUS_SUPER_AGAINST = COLLISION_FLAG_CHASSIS,
};
