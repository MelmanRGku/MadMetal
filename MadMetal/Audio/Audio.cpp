#include "Audio.h"
#include <iostream>

void Audio::update()
{
	float listenerX;
	float listenerY;
	float sourceX;
	float sourceY;
	int channelNum;

	/*TODO Delete this comment */


	for (unsigned int i = 0; i < positionalSources.size(); i++)
	{
		
		if (!Mix_Playing(channelNum = positionalSources[i].getChannelNum()))
		{
			std::cout << "removed a dynamic source \n";
			positionalSources.erase(positionalSources.begin() + i);
			

		}
		else if (Mix_Paused(channelNum))
		{
			//do nothing
			
		}
		else 
		{
			//get position of dynamic source
			positionalSources[i].getSourcePosition(sourceX, sourceY);
			listener->getPosition(listenerX, listenerY);

			//get distance in relation to listener
			sourceX = sourceX - listenerX;
			sourceY = sourceY - listenerY;
			float distance = sqrt((powf(sourceX, 2) + powf(sourceY, 2)));
			double angle;

			//convert position of source relative to listener to SDL_Mixer orientation:
			/*
			0/360 - in front
			90 - to the left
			180 - behind
			270 - to the left
			*/

			if (sourceX == 0)
			{
				if (sourceY < 0)
					angle = 180;
				else
					angle = 0;
			}
			else
			{
				
				angle = atan((sourceY / sourceX));
				angle *= 180 / 3.14;

				//convert to Mixer orientation
				if (sourceX < 0)
					angle =270 - angle;
				else
					angle = 90 - angle;
			}

			//------ remove later-----------
			distance *= 190; // used for testing with analog joystick, remove when replacing with real object
			distance = distance > 255 ? 255 : distance;
			//-------------------------------

			Mix_SetPosition(channelNum, angle, distance );
			
		}
	}
}


bool Audio::quePositionalSource(DummyPosition **position)
{

	Mix_Chunk * chunk = Mix_LoadWAV("Assets/Audio/laugh.wav");
	if (chunk == NULL)
	{
		std::cout << "AHHHHH";
		return false;
	}

	positionalSources.push_back(PositionalAudioSource(position, Mix_PlayChannel(-1, chunk, 0)));
	return true;
}



bool Audio::queStaticSource(int sourceID)
{
	Mix_Chunk * staticChunk = Mix_LoadWAV("Assets/Audio/menu_sound_1.wav");
	if (staticChunk == NULL)
	{
		std::cout << "AHHHHH";
		return false;
	}

	Mix_PlayChannel(-1, staticChunk, 0);
	return true;
}

void Audio::pauseSources()
{
	Mix_Pause(-1);
}

void Audio::resumeSources()
{
	Mix_Resume(-1);
}

void Audio::stopSources()
{
		Mix_HaltChannel(-1);	
}

/////////////////////////// getter functions for positional audio source wrapper /////////////////////////
void PositionalAudioSource::getSourcePosition(float &x, float &y)
{
	audioSource->getPosition(x, y);
}

int PositionalAudioSource::getChannelNum()
{
	return channelNum;
}


/////////////////////////// Temp functions to simulate a positional object //////////////////////////
void DummyPosition::getPosition(float &x, float &y)
{
	x = xpos;
	y = ypos;
}

void DummyPosition::movePosition(float x, float y)
{
	xpos += x;
	ypos += y;
}
void DummyPosition::setPosition(float x, float y)
{
	xpos = x;
	ypos = y;
}

