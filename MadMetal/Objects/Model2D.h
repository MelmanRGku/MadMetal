#pragma once

#include "Texture.h"
#include "Model.h"

class Model2D : public Model
{
private:
	Texture *texture;

public:
	Model2D();
	Model2D(Texture *texture);
	~Model2D();
	Texture *getTexture() { return texture; }
};

