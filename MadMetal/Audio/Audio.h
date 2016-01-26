#include <vector>
#include <iostream>

class Audio
{
private:
	std::vector<int> channelsPlaying;
	int soundRegister[10];
public:
	void update()
	{
		std::cout << "Audio is updating ...\n";
	}
	void playNewSound(int soundIndex)
	{
		std::cout << "New Sounds Added.... \n";
	}
};