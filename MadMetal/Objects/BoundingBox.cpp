#include "BoundingBox.h"
#include <float.h>

BoundingBox::BoundingBox()
{
	minX = minY = minZ = DBL_MAX;
	maxX = maxY = maxZ = -DBL_MAX;
}


BoundingBox::~BoundingBox()
{
}


void BoundingBox::addPosition(glm::vec3 pos) {
	if (pos.x > maxX)
		maxX = pos.x;


	if (pos.y > maxY)
		maxY = pos.y;


	if (pos.z > maxZ)
		maxZ = pos.z;

	if (pos.x < minX)
		minX = pos.x;

	if (pos.y < minY)
		minY = pos.y;

	if (pos.z < minZ)
		minZ = pos.z;
}

void BoundingBox::finalize() {
	sizeX = maxX - minX;
	sizeY = maxY - minY;
	sizeZ = maxZ - minZ;
	centerX = minX + sizeX / 2;
	centerY = minY + sizeY / 2;
	centerZ = minZ + sizeZ / 2;
}