#pragma once 
#include "Simulation\PhysicsManager.h"
#include "Objects\ObjectCreators\VehicleCreator.h"
#include <iostream>

class PhysicsFactory
{
public:
	enum PhysicalObjects {
		PHYSICAL_OBJECT_CAR,
		PHYSICAL_OBJECT_DRIVING_BOX,
		PHYSICAL_OBJECT_BOX,
		PHYSICAL_TRIANGLE_MESH,
		PHYSICAL_OBJECT_BULLET_MEOW_MIX,
		PHYSICAL_OBJECT_BULLET_SUPER_VOLCANO,
		PHYSICAL_OBJECT_TRACK,
		WAYPOINT_COLLISION_VOLUME,
		PHYSICAL_OBJECT_TRACK_DRIVABLE,
		PHYSICAL_OBJECT_TRACK_NON_DRIVABLE,
		COLLISION_VOLUME,
		POWER_UP,
		SHIELD_POWERUP,
		PHYSICAL_OBJECT_PARTICLE,
		PHYSICAL_OBJECT_EXPLOSION,
		SPEED_POWERUP,
		ANIMATION_TEST
	};

public:
	PhysicsFactory(){}
	~PhysicsFactory(){}

	PxRigidStatic* createDrivingBox(physx::PxMaterial* material, PxTransform position, PxGeometry *box)
	{
		//Add a plane to the scene.
		PxRigidStatic* collisionBox = PhysicsManager::getPhysicsInstance().createRigidStatic(position);
		collisionBox->createShape(*box, *material);

		//Get the plane shape so we can set query and simulation filter data.
		PxShape* shapes[1];
		collisionBox->getShapes(shapes, 1);

		//Set the query filter data of the ground plane so that the vehicle raycasts can hit the ground.
		physx::PxFilterData qryFilterData;
		setupDrivableSurface(qryFilterData);
		shapes[0]->setQueryFilterData(qryFilterData);

		//Set the simulation filter data of the ground plane so that it collides with the chassis of a vehicle but not the wheels.
		PxFilterData simFilterData;
		simFilterData.word0 = COLLISION_FLAG_GROUND;
		simFilterData.word1 = COLLISION_FLAG_GROUND_AGAINST;
		shapes[0]->setSimulationFilterData(simFilterData);

		return collisionBox;
	}

	void setFilterDataId(long id, PxRigidActor *actor) {
		const PxU32 numShapes = actor->getNbShapes();
		PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
		actor->getShapes(shapes, numShapes);


		for (PxU32 i = 0; i < numShapes; i++) {
			PxFilterData filterData = shapes[i]->getSimulationFilterData();
			filterData.word2 = id;
			shapes[i]->setSimulationFilterData(filterData);
		}

		free(shapes);
	}
		 
	void makeGround(PxRigidActor *actor, bool drivable) {
		const PxU32 numShapes = actor->getNbShapes();
		PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
		actor->getShapes(shapes, numShapes);


		for (PxU32 i = 0; i < numShapes; i++) {
			if (drivable) {
			physx::PxFilterData qryFilterData = shapes[i]->getQueryFilterData();
			setupDrivableSurface(qryFilterData);
			shapes[i]->setQueryFilterData(qryFilterData);
			}

			PxFilterData simFilterData = shapes[i]->getSimulationFilterData();
			simFilterData.word0 = COLLISION_FLAG_GROUND;
			simFilterData.word1 = COLLISION_FLAG_GROUND_AGAINST;
			shapes[i]->setSimulationFilterData(simFilterData);
		}

		free(shapes);
	}
		 
	PxBase *makePhysicsObject(PhysicalObjects actorToMake, long objectId, PxTransform *pos, PxGeometry **geom, PxU32 nbGeom, PxMaterial *material, DrivingStyle *style, PxVec3 *velocity)
	{
		PxBase *toReturn = NULL;

		switch (actorToMake) {
		case PHYSICAL_OBJECT_BOX:
		{
			PxRigidStatic * box = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			box->createShape(*geom[0], *material);
			setFilterDataId(objectId, box);
			toReturn = box;
			break;
		}
		case PHYSICAL_OBJECT_DRIVING_BOX:
		{
			PxRigidStatic * plane = createDrivingBox(material, *pos, geom[0]);
			setFilterDataId(objectId, plane);
			toReturn = plane;
			break;
		}
		case PHYSICAL_OBJECT_CAR:
		{
			VehicleCreator *vc = new VehicleCreator(&PhysicsManager::getPhysicsInstance(), &PhysicsManager::getCookingInstance());
			PxVehicleDrive4W *car = vc->create(style);
			delete vc;
			PxTransform startTransform(PxVec3(0, 3 + (style->getChassisDimensions().y*0.5f + style->getWheelRadius() + 1.0f), 0), PxQuat(PxIdentity));
			PxTransform anotherTransform = pos == NULL ? PxTransform(PxVec3(0), PxQuat(PxIdentity)) : *pos;
			car->getRigidDynamicActor()->setGlobalPose(PxTransform(startTransform.p.x + anotherTransform.p.x, startTransform.p.y + anotherTransform.p.y, startTransform.p.z + anotherTransform.p.z));
			setFilterDataId(objectId, car->getRigidDynamicActor());
			toReturn = car;
			break;
		}
		case PHYSICAL_OBJECT_BULLET_MEOW_MIX:
		{
			PxRigidDynamic * bullet = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_BULLET;
			simFilterData.word1 = COLLISION_FLAG_BULLET_AGAINST;
			
			bullet->createShape(PxBoxGeometry(.3, .3, 1), *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			bullet->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			setFilterDataId(objectId, bullet);
			bullet->setLinearVelocity(*velocity);

			toReturn = bullet;
			break;
		}

		case PHYSICAL_OBJECT_BULLET_SUPER_VOLCANO:
		{
			PxRigidDynamic * bullet = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_BULLET;
			simFilterData.word1 = COLLISION_FLAG_BULLET_AGAINST;
			
			bullet->createShape(PxSphereGeometry(3.f), *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			bullet->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			setFilterDataId(objectId, bullet);
			bullet->setLinearVelocity(*velocity);

			toReturn = bullet;
			break;
		}
		case WAYPOINT_COLLISION_VOLUME:
		{
			PxRigidStatic * wapoint = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_WAYPOINT;
			simFilterData.word1 = COLLISION_FLAG_WAYPOINT_AGAINST;

			wapoint->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			wapoint->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			setFilterDataId(objectId, wapoint);

			toReturn = wapoint;
			break;
		}
		case PHYSICAL_OBJECT_TRACK_DRIVABLE:
		{
			PxRigidStatic* plane = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			for (PxU32 i = 0; i < nbGeom; i++) {
				plane->createShape(*geom[i], *material);
			}
			setFilterDataId(objectId, plane);
			makeGround(plane, true);

			toReturn = plane;
			break;
		}

		case PHYSICAL_OBJECT_TRACK_NON_DRIVABLE:
		{
			PxRigidStatic* plane = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			for (PxU32 i = 0; i < nbGeom; i++) {
				
				plane->createShape(*geom[i], *material);
			}


			const PxU32 numShapes = plane->getNbShapes();
			PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
			plane->getShapes(shapes, numShapes);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_OBSTACLE;
			simFilterData.word1 = COLLISION_FLAG_OBSTACLE_AGAINST;
			for (int i = 0; i < numShapes; i++)
			{
				shapes[i]->setSimulationFilterData(simFilterData);
			}
			setFilterDataId(objectId, plane);
			toReturn = plane;
			break;
		}

		case COLLISION_VOLUME:
		{
			PxRigidStatic * wapoint = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_COLLISION_VOLUME;
			simFilterData.word1 = COLLISION_FLAG_COLLISION_VOLUME_AGAINST;

			wapoint->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			wapoint->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			setFilterDataId(objectId, wapoint);

			toReturn = wapoint;
			break;
		}
		case POWER_UP:
		{
			PxRigidStatic * powerup = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_POWERUP;
			simFilterData.word1 = COLLISION_FLAG_POWERUP_AGAINST;

			powerup->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			powerup->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			setFilterDataId(objectId, powerup);

			toReturn = powerup;
			break;
		}
		case SHIELD_POWERUP:
		{
							   PxRigidStatic * powerup = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
							   PxFilterData simFilterData;
							   simFilterData.word0 = COLLISION_FLAG_SHIELD_POWERUP;
							   simFilterData.word1 = COLLISION_FLAG_SHIELD_POWERUP_AGAINST;

							   powerup->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

							   PxShape* shapes[1];
							   powerup->getShapes(shapes, 1);
							   shapes[0]->setSimulationFilterData(simFilterData);
							   shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
							   shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

							   setFilterDataId(objectId, powerup);

							   toReturn = powerup;
							   break;
		}
		case SPEED_POWERUP:
		{
							  PxRigidStatic * powerup = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
							  PxFilterData simFilterData;
							  simFilterData.word0 = COLLISION_FLAG_SPEED_POWERUP;
							  simFilterData.word1 = COLLISION_FLAG_POWERUP_AGAINST;

							  powerup->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

							  PxShape* shapes[1];
							  powerup->getShapes(shapes, 1);
							  shapes[0]->setSimulationFilterData(simFilterData);
							  shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
							  shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

							  setFilterDataId(objectId, powerup);

							  toReturn = powerup;
							  break;
		}
		case ANIMATION_TEST:
		{
			PxRigidStatic * powerup = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);

			powerup->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			toReturn = powerup;
			break;
		}
		case PHYSICAL_OBJECT_PARTICLE:
		{
										 PxRigidStatic * particle = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
										 
										 
										 PxFilterData simFilterData;
										 simFilterData.word0 = 0;
										 simFilterData.word1 = 0;

										 particle->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

										 PxShape* shapes[1];
										 particle->getShapes(shapes, 1);
										 shapes[0]->setSimulationFilterData(simFilterData);
										 shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
										 shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

										 setFilterDataId(objectId, particle);
										 
										 toReturn = particle;
										 break;
		}

		case PHYSICAL_OBJECT_EXPLOSION:
		{
										 PxRigidStatic * explosion = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);


										 PxFilterData simFilterData;
										 simFilterData.word0 = 0;
										 simFilterData.word1 = 0;

										 explosion->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

										 PxShape* shapes[1];
										 explosion->getShapes(shapes, 1);
										 shapes[0]->setSimulationFilterData(simFilterData);
										 shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
										 shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

										 setFilterDataId(objectId, explosion);

										 toReturn = explosion;
										 break;
		}
		}


		return toReturn;
	}

	
private: //members
	//enum of physics objects to make

	
};