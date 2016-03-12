#include "Model2D.h"


Model2D::Model2D()
{
}

Model2D::Model2D(Texture *texture) : texture(texture) {

}

Model2D::~Model2D()
{
	delete texture;
}
