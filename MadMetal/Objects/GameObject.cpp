#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(VAO *vao, Model *model) {
	setVAO(vao);
	setModel(model);
}

GameObject::~GameObject()
{
	delete vao;
	delete model;
}
