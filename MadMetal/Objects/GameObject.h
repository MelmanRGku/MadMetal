#pragma once

#include "Model.h"
#include "../Renderer/VAO.h"

class GameObject
{
public:
	VAO *vao;
	Model *model;

	GameObject();
	GameObject(VAO *vao, Model *model);
	~GameObject();
	void setVAO(VAO *vao) { this->vao = vao; }
	void setModel(Model *model) { this->model = model; }
};

