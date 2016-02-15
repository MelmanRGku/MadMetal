#pragma once

#include "Libraries\glm\vec3.hpp"

class BoundingBox
{
private:
	double minX, minY, minZ,
		maxX, maxY, maxZ,
		sizeX, sizeY, sizeZ,
		centerX, centerY, centerZ;
public:
	BoundingBox();
	~BoundingBox();
	void addPosition(glm::vec3 pos);
	void finalize();
	double getMinX() { return minX; }
	double getMinY() { return minY; }
	double getMinZ() { return minZ; }
	double getMaxX() { return maxX; }
	double getMaxY() { return maxY; }
	double getMaxZ() { return maxZ; }
	double getSizeX() { return sizeX; }
	double getSizeY() { return sizeY; }
	double getSizeZ() { return sizeZ; }
	double getCenterX() { return centerX; }
	double getCenterY() { return centerY; }
	double getCenterZ() { return centerZ; }
};

