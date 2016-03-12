#include "Audio.h"
#include "Sound.h"
#include "Objects\Cars\Car.h"

#include <iostream>
#include <fstream>
#include <string>




//set up audio library
void Audio::initializeMusicLibrary(char * fileToLoad)
{
	std::ifstream stream;
	stream.open(fileToLoad);
	std::string line;
	if (stream.is_open())
	{
		std::string filename;
		bool reached = false;;
		int pos = 0;
		Mix_Music * music;
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
			//std::cout << filename << std::endl;
			char * test = "Assets/Audio/";
			std::string thefile = test + filename;
			music = Mix_LoadMUS(thefile.c_str());
			if (music == NULL)
			{
				std::cout << "File Failed to Load \n";
			}
			m_musicLibrary.push_back(music);

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

//set up audio library
void Audio::initializeChunkLibrary(char * fileToLoad)
{
	std::ifstream stream;
	stream.open(fileToLoad);
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
			//std::cout << filename << std::endl;
			char * test = "Assets/Audio/";
			std::string thefile = test + filename;
			chunk = Mix_LoadWAV(thefile.c_str());
			if (chunk == NULL)
			{
				std::cout << "File Failed to Load \n";
			}
			m_chunkLibrary.push_back(chunk);
			
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
	for (unsigned int i = 0; i < m_audioChannels.size(); i++)
	{
		if (!Mix_Playing(m_audioChannels[i]->getChannel()))
		{
			delete m_audioChannels[i];
			m_audioChannels.erase(m_audioChannels.begin() + i);
		}
		else if (m_audioChannels[i]->needsUpdate())
		{
			m_audioChannels[i]->setAudioPosition(m_listener);
		}
		
		
	}
	
}
		
void Audio::queAudioSource(PxRigidActor * sourcePosition, Sound toPlay, float volumeScalar, bool updatePosition, int loopCount)
{
	
	AudioChannel * toAdd = new AudioChannel(sourcePosition, updatePosition, volumeScalar);
			
	//set the audio channel to the next available channel, and play the specified sound
	
	toAdd->setChannel(Mix_FadeInChannel(-1, m_chunkLibrary[toPlay.getLibraryIndex()], loopCount, 200));
	toAdd->setAudioPosition(m_listener);
	toPlay.setChannel(toAdd->getChannel());
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

bool AudioChannel::setAudioPosition(Car * listener)
{
	//if sound has stopped playing, return 
	if (!Mix_Playing(m_playingChannel))
{
		return false;
	}

	//calculate distance between the listener and source. 
	float listenerX = 0 , listenerZ =0, sourceX =0, sourceZ =0;
	if (m_audioPosition != NULL)
	{
		if (listener != NULL)
		{
			listenerX = listener->getActor().getGlobalPose().p.x;
			listenerZ = listener->getActor().getGlobalPose().p.z;
		}
	
		sourceX = m_audioPosition->getGlobalPose().p.x;
		sourceZ = m_audioPosition->getGlobalPose().p.z;
	}

			sourceX = sourceX - listenerX;
	sourceZ = sourceZ - listenerZ;
	float distance = sqrt((powf(sourceX, 2) + powf(sourceZ, 2))) + (1 - m_volumeScalar) * 255;
	if (distance < 0) distance = 0;
	
	// if sound is too far away to hear, halt playing and return
	if (distance > 255) 
	{
		Mix_HaltChannel(m_playingChannel);
		return false;
	}


	//calculate where the sound is in relation to the player
	glm::vec3 forwardVector = glm::normalize(glm::vec3( listener->getForwardVector().x, 0, listener->getForwardVector().z));
	glm::vec3 vectorToSound = glm::normalize(glm::vec3(sourceX, 0,sourceZ));
	
	float degree = 180.f / 3.14 * acos(glm::dot(forwardVector, vectorToSound));

			//convert position of source relative to listener to SDL_Mixer orientation:
			/*
			0/360 - in front
	90 - to the right
			180 - behind
			270 - to the left
			*/
	if (glm::cross(forwardVector, vectorToSound).y > 0)
			{
		//std::cout << "Sound is to the Left\n";
		degree = 360 - degree;
			}
	else {
		//std::cout << "Sound is to the Right\n";	
			}

	Mix_SetPosition(m_playingChannel, Sint16(degree), Uint8(distance));
	return true;
}


void Audio::playMusic(Sound sound, int playCount)
{
	
	Mix_PlayMusic(m_musicLibrary[sound.getLibraryIndex()], playCount);

}