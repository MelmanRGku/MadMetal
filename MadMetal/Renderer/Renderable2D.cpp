#include "Renderable2D.h"

#define ZERO_TO_ONE(x) (x == 0 ? 1 : x)

Renderable2D::~Renderable2D() {}

Renderable2D::Renderable2D(Model2D* Model) : Renderable(Model)
{

}