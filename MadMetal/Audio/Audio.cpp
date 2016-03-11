#include "Audio.h"
#include "Sound.h"
#include <iostream>
#include <fstream>
#include <string>


AudioChannel::~AudioChannel()
{
	m_sound->setChannel(-1);
	m_audioPosition = NULL;
}



//set up audio library
void Audio::initializeLibrary(char * fileToLoad)
{

	std::ifstream stream;
	stream.open("Audio/Library.txt");
	std::string line;
	if (stream.is_open())
	{
		std::string filename;
		bool reached= false;;
		int pos = 0;
		Mix_Chunk * chunk;
		while (getline(stream, line))
		{
			while (pos < line.length())
			{
				if (reached)
				{
					filename = filename + line[pos];
				}
				if (line[pos] == ' ')
				{
					reached = true;
				}

				pos++;
			}
			std::cout << filename << std::endl;
			char * test = "Assets/Audio/";
			std::string thefile = test + filename;
			chunk = Mix_LoadWAV(thefile.c_str());
			if (chunk == NULL)
			{
				std::cout << "File Failed to Load \n";
			}
			m_library.push_back(chunk);
			

			pos = 0;
			reached = false;
			filename.clear();
		}


	}
	else
	{
		std::cout << "File reading error" << std::endl;
	}

}


void Audio::update()
{
	//std::cout << m_audioChannels.size()<< std::endl;
	for (unsigned int i = 0; i < m_audioChannels.size(); i++)
	{
		if (m_audioChannels[i]->getSound() == NULL 
			||!Mix_Playing(m_audioChannels[i]->getSound()->getChannel()))
		{
			delete m_audioChannels[i];
			m_audioChannels.erase(m_audioChannels.begin() + i);
		}
		else if (m_audioChannels[i]->getSound()->getChannel())
		{
			//do nothing for now
		}
		else 
		{
			m_audioChannels[i]->updateAudio(m_listener);
		}
		
		
		
	}
	
}
		
void Audio::queAudioSource(PxRigidActor * sourcePosition, Sound* toPlay, int loopCount)
{
	
	//pass a refrence of the channel number in 'toPlay' to the audio channel 
	//will allow channel changes to be mirrored in the toPlay bookmark
	AudioChannel * toAdd = new AudioChannel(sourcePosition, toPlay);
			
	//set the audio channel to the next available channel, and play the specified sound
	
	toAdd->getSound()->setChannel(Mix_PlayChannel(-1, m_library[toPlay->getLibraryIndex()], loopCount));
	
	//add new channel to the list of currently playing sounds
	m_audioChannels.push_back(toAdd);
	
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
	//std::cout << distance << std::endl;
	Mix_SetPosition(m_sound->getChannel(), Sint16(angle), Uint8(distance));
	return true;
}

void Audio::loadMusic(char * file)
{
	music = Mix_LoadMUS("Assets/Audio/musmettatonneo.wav");
	Mix_PlayMusic(music, -1);
}