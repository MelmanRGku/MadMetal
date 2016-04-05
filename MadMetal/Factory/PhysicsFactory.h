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
		PHYSICAL_OBJECT_TRACK_WALLS,
		PHYSICAL_OBJECT_CAR_TRIGGER_VOLUME,
		COLLISION_VOLUME,
		POWER_UP,
		SHIELD_POWERUP,
		PHYSICAL_OBJECT_PARTICLE,
		PHYSICAL_OBJECT_EXPLOSION,
		PHYSICAL_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER,
		PHYSICAL_OBJECT_GARGANTULOUS_SUPER_BULLET,
		PHYSICAL_OBJECT_GARGANTULOUS_BULLET,
		PHYSICAL_OBJECT_GARGANTULOUS_SUPER_VOLUME,
		PHYSICAL_OBJECT_MEOW_MIX_SUPER,
		SPEED_POWERUP,
		ANIMATION_TEST,
		DEATH_VOLUME,
		PHYSICAL_OBJECT_GOO_MONSTER,
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
		 
	PxBase *makePhysicsObject(PhysicalObjects actorToMake, long objectId, PxTransform *pos = NULL, PxGeometry **geom = NULL, PxU32 nbGeom = 0, PxMaterial *material = NULL, DrivingStyle *style = NULL, PxVec3 *velocity = NULL)
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
			//car->getRigidDynamicActor()->setAngularDamping(PX_MAX_F32);
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

		case PHYSICAL_OBJECT_GARGANTULOUS_BULLET:
		{
			PxRigidDynamic * bullet = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
			bullet->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_BULLET;
			simFilterData.word1 = COLLISION_FLAG_BULLET_AGAINST;

			bullet->createShape(PxBoxGeometry(2, 2, 4), *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

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
		case PHYSICAL_OBJECT_GARGANTULOUS_SUPER_BULLET:
		{
			PxRigidDynamic * bullet = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
			bullet->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			bullet->setLinearDamping(0);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_GARGANTULOUS_SUPER_BULLET;
			simFilterData.word1 = COLLISION_FLAG_GARGANTULOUS_SUPER_BULLET_AGAINST;

			bullet->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			bullet->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);


			setFilterDataId(objectId, bullet);

			toReturn = bullet;
			break;
		}
		case PHYSICAL_OBJECT_GARGANTULOUS_SUPER_VOLUME:
		{
			PxRigidDynamic * volume = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
			volume->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			volume->setLinearDamping(0);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_GARGANTULOUS_SUPER_VOLUME;
			simFilterData.word1 = COLLISION_FLAG_GARGANTULOUS_SUPER_VOLUME_AGAINST;

			volume->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			volume->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);


			setFilterDataId(objectId, volume);

			toReturn = volume;
			break;
		}
		case PHYSICAL_OBJECT_MEOW_MIX_SUPER:
		{
			PxRigidDynamic * beam = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_MEOW_MIX_SUPER;
			simFilterData.word1 = COLLISION_FLAG_MEOW_MIX_SUPER_AGAINST;

			beam->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

			PxShape* shapes[1];
			beam->getShapes(shapes, 1);
			shapes[0]->setSimulationFilterData(simFilterData);
			shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			setFilterDataId(objectId, beam);
											   
			toReturn = beam;
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
			free(shapes);
			setFilterDataId(objectId, plane);
			toReturn = plane;
			break;
		}

		case PHYSICAL_OBJECT_TRACK_WALLS:
		{
			PxRigidStatic* walls = PhysicsManager::getPhysicsInstance().createRigidStatic(*pos);
			for (PxU32 i = 0; i < nbGeom; i++) {
				 walls->createShape(*geom[i], *material);
			}


			const PxU32 numShapes = walls->getNbShapes();
			PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
			walls->getShapes(shapes, numShapes);
			PxFilterData simFilterData;
			simFilterData.word0 = COLLISION_FLAG_OBSTACLE;
			simFilterData.word1 = COLLISION_FLAG_OBSTACLE_AGAINST;
			for (int i = 0; i < numShapes; i++)
			{
			   shapes[i]->setSimulationFilterData(simFilterData);
			}
			setFilterDataId(objectId, walls);
			toReturn = walls;
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
		case DEATH_VOLUME:
		{
							 PxRigidDynamic * deathVolume = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
							 deathVolume->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
							 PxFilterData simFilterData;
							 simFilterData.word0 = COLLISION_FLAG_DEATH_VOLUME;
							 simFilterData.word1 = COLLISION_FLAG_DEATH_VOLUME_AGAINST;

							 deathVolume->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

							 PxShape* shapes[1];
							 deathVolume->getShapes(shapes, 1);
							 shapes[0]->setSimulationFilterData(simFilterData);
							 shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
							 shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
							 

							 setFilterDataId(objectId, deathVolume);

							 toReturn = deathVolume;
							 break;
		}
		case PHYSICAL_OBJECT_GOO_MONSTER:
		{
							 PxRigidDynamic * gooMonster = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
							 PxFilterData simFilterData;
							 simFilterData.word0 = COLLISION_FLAG_GOO_MONSTER;
							 simFilterData.word1 = COLLISION_FLAG_GOO_MONSTER_AGAINST;

							 gooMonster->createShape(*geom[0], *PhysicsManager::getPhysicsInstance().createMaterial(0.5, 0.3, 0.1f));

							 PxShape* shapes[1];
							 gooMonster->getShapes(shapes, 1);
							 shapes[0]->setSimulationFilterData(simFilterData);
							 shapes[0]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
							 shapes[0]->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);


							 setFilterDataId(objectId, gooMonster);

							 toReturn = gooMonster;
							 break;
		}
		case PHYSICAL_OBJECT_EXPLOSIVELY_DELICIOUS_SUPER:
		{
															PxRigidDynamic * explosion = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
															explosion->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
															explosion->setLinearDamping(0);
															PxFilterData simFilterData;
															simFilterData.word0 = COLLISION_FLAG_EXPLOSIVELY_DELICIOUS_SUPER;
															simFilterData.word1 = COLLISION_FLAG_EXPLOSIVELY_DELICIOUS_SUPER_AGAINST;

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
										 PxRigidDynamic * particle = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
										 particle->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
										 
										 particle->setLinearDamping(0);
										 
										 PxFilterData simFilterData;
										 simFilterData.word0 = COLLISION_FLAG_PARTICLE;
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
										 PxRigidDynamic * explosion = PhysicsManager::getPhysicsInstance().createRigidDynamic(*pos);
										 explosion->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

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