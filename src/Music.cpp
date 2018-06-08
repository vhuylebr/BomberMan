/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** music class
*/

#include "Music.hpp"

Music::Music()
{
}

Music::~Music()
{
}

void 	playsMusic(std::pair<irrklang::ISoundEngine *, std::pair<std::string, bool>> sound)
{
	sound.first->play2D(sound.second.first.c_str(), sound.second.second);
}

void 	Music::play(SOUND id)
{
	std::thread tmp2(playsMusic, _sound[id]);
	tmp2.detach();
}

bool 	Music::load(SOUND id, std::string pathname)
{
	irrklang::ISoundEngine* tmp2 = irrklang::createIrrKlangDevice();

	_sound.insert(std::make_pair(id, std::make_pair(tmp2, std::make_pair(pathname, false))));
	return true;
}

void 	Music::setLoop(SOUND id, bool state)
{
	_sound[id].second.second = state;
}

void 	Music::stop(SOUND id)
{
	_sound[id].first->stopAllSounds();
}

void	Music::setVol(SOUND id, float volume)
{
	_sound[id].first->setSoundVolume(volume);
}