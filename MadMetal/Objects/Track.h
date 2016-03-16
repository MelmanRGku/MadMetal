#pragma once

#include "Object3D.h"

class Track : public Object3D
{
public:
	Track(long id, Audioable *aable, Physicable *pable, Animatable *anable, Renderable3D *rable, Object3D *drivablePart, Object3D *nonDrivablePart);
	~Track();
	bool draw(Renderer *renderer, Renderer::ShaderType type, int passNumber);
	Object3D *getDrivablePart() { return drivablePart; }
	
	void playTrackMusic();

private: //members
	Object3D *drivablePart,
		*nonDrivablePart;
	
	
};
