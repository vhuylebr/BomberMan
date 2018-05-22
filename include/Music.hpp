/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** music cpp
*/

#ifndef MUSIC_HPP_
	#define MUSIC_HPP_

#include <SFML/Audio.hpp>
#include <map>

enum class SOUND {
	MENU,
	GAME,
	POWERUP,
	TICTAC,
	BOOM,
	LOSE,
	WIN
};

class Music {
	public:
		Music();
		~Music();
		void play(SOUND id);
		bool load(SOUND id, std::string pathname);
		void setLoop(SOUND id, bool state);
		void stop(SOUND id);
		void pause(SOUND id);

	private:
		std::map<SOUND, sf::Music *> _sounds;
};

#endif /* !MUSIC_HPP_ */
