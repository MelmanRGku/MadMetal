#include "Audio.h"
#include <iostream>

//set up audio library
void Audio::initializeLibrary(char * fileToLoad)
{
	//to do: make into a file parsing method? 
	//to do: fill with sounds
	Mix_Chunk * chunk = Mix_LoadWAV("Assets/Audio/car_idle.wav");
	if (chunk == NULL)
	{
		std::cout << "ABORT \n";
	}
	m_library.push_back(chunk);

	Mix_Chunk * chunk2 = Mix_LoadWAV("Assets/Audio/menu_sound_1.wav");
	if (chunk == NULL)
	{
		std::cout << "ABORT \n";
	}
	m_library.push_back(chunk2);

	Mix_Chunk * chunk3 = Mix_LoadWAV("Assets/Audio/mario.wav");
	if (chunk == NULL)
	{
		std::cout << "ABORT \n";
	}
	m_library.push_back(chunk3);
}


void Audio::update()
{

	for (unsigned int i = 0; i < m_audioChannels.size(); i++)
	{
		if (!Mix_Playing(m_audioChannels[i]->getChannelNum()))
		{
			delete m_audioChannels[i];
			m_audioChannels.erase(m_audioChannels.begin() + i);
		}
		else if (Mix_Paused(m_audioChannels[i]->getChannelNum()))
		{
			//do nothing for now
		}
		else 
		{
			m_audioChannels[i]->updateAudio(m_listener);
		}
	}
	
}
		
void Audio::queAudioSource(PxRigidActor * sourcePosition, Sound& toPlay, int loopCount)
{
	//pass a refrence of the channel number in 'toPlay' to the audio channel 
	//will allow channel changes to be mirrored in the toPlay bookmark
	AudioChannel * toAdd = new AudioChannel(sourcePosition, toPlay.getChannel());
			
	//set the audio channel to the next available channel, and play the specified sound
	toAdd->setChannelNum(Mix_PlayChannel(-1, m_library[toPlay.getLibraryIndex()], loopCount));
	
	//add new channel to the list of currently playing sounds
	m_audioChannels.push_back(toAdd);
	std::cout << "Qued Sound \n";
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

void Audio::stopSource(int channel)
{
	Mix_HaltChannel(channel);
}

//todo:: need to incorporate forward vector into calculations!!

bool AudioChannel::updateAudio(PxRigidActor * listener)
{
	float listenerX = 0 , listenerY =0, sourceX =0, sourceY =0;
	if (listener != NULL)
	{
		listenerX = listener->getGlobalPose().p.x;
		listenerY = listener->getGlobalPose().p.y;
	}
	if (m_audioPosition != NULL)
	{
		sourceX = m_audioPosition->getGlobalPose().p.x;
		sourceY = m_audioPosition->getGlobalPose().p.y;
	}

			//get distance in relation to listener
			sourceX = sourceX - listenerX;
			sourceY = sourceY - listenerY;
			float distance = sqrt((powf(sourceX, 2) + powf(sourceY, 2)));
	distance = distance == 0 ? 0.1 : distance;
	
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
			angle = 270 - angle;
				else
					angle = 90 - angle;
			}

			//------ remove later-----------
	
			distance = distance > 255 ? 255 : distance;
			//-------------------------------
	std::cout << distance << std::endl;
	Mix_SetPosition(m_channelNum, Sint16(angle), Uint8(distance));
	return true;
}
