#include "Renderable.h"

Renderable::~Renderable() {}

Renderable::Renderable(Model* Model)
{
	setModel(Model);
}

void Renderable::setModel(Model *model)
{
	m_model = model;
}