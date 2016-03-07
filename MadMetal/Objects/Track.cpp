#include "Track.h"

Track::Track(long id, Audioable &aable, Physicable &pable, Animatable &anable, Renderable &rable, Audio* audio, TestObject *drivablePart, TestObject *nonDrivablePart) : TestObject(id, aable, pable, anable, rable, audio), drivablePart(drivablePart), nonDrivablePart(nonDrivablePart)
{
}

Track::~Track()
{

}

bool Track::draw(Renderer *renderer, Renderer::ShaderType type, int passNumber) {
	
	//do nothing
	return false;

}