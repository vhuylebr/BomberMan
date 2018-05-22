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

void 	playMusic(sf::Music *music)
{
	music->play();
}

void 	Music::play(SOUND id)
{
	std::thread tmp(playMusic, _sounds[id]);
	tmp.detach();
}

bool 	Music::load(SOUND id, std::string pathname)
{
	sf::Music *tmp = new sf::Music();
	int ret = tmp->openFromFile(pathname);

	if (!ret)
		return false;
	_sounds.insert(std::make_pair(id, tmp));
	return true;
}

void 	Music::setLoop(SOUND id, bool state)
{
	_sounds[id]->setLoop(state);
}

void 	Music::stop(SOUND id)
{
	_sounds[id]->stop();
}

void 	Music::pause(SOUND id)
{
	_sounds[id]->pause();
}