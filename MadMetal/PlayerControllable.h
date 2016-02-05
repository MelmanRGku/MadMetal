#include "Controllable.h"
#include "Input\GamePad.h"
class PlayerControllable : public Controllable
{
private:
	GamePad * m_gamePad;

public:
	PlayerControllable(GameObject * normalModel, GamePad * gamePad);
	~PlayerControllable();
	void playFrame(double dt);
};