/*
** EPITECH PROJECT, 2018
** Game
** File description:
** game
*/

#include "GameCore.hpp"

GameCore::GameCore()
	:_id(1), _player1(-1, -1, -1), _player2(-1, -1, -1), _nbPlayer(0),
	_i(0), _bubgCounter(3000), _mapClosing(false)
{
	_loadScreenItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, INTRO3_ID, "", (SCREEN_WIDTH / 2) - 200, 300, 600, 600, "./media/three.png", true)));
	_loadScreenItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, INTRO2_ID, "", (SCREEN_WIDTH / 2) - 200, 300, 600, 600, "./media/two.png", true)));
	_loadScreenItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, INTRO1_ID, "", (SCREEN_WIDTH / 2) - 200, 300, 600, 600, "./media/one.png", true)));
}

void GameCore::createEntities(std::vector<std::vector<char>> &map,
		unsigned int &x, unsigned int &y, const parameters &params)
{
	y = 0;
	_iaList.clear();
	_nbPlayer = 0;
	for (auto &line : map) {
		x = 0;
		_vectorEntities.push_back(std::vector<std::unique_ptr<EntityPos>>());
		for (auto &c : line) {
			if (c == '0') {
				_vectorEntities[y].push_back(std::make_unique<EntityPos>(ItemStatic::WALL, static_cast<float>(x), static_cast<float>(y), _id));
				_id++;
			} else if (c == '1') {
				_vectorEntities[y].push_back(std::make_unique<EntityPos>(ItemStatic::CRATE, static_cast<float>(x), static_cast<float>(y), _id));
				_id++;
			} else if (c == '4') {
				_vectorEntities[y].push_back(std::make_unique<EntityPos>());
				if (_nbPlayer == 0) {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x), static_cast<float>(y), _id, 0));
					_player1 = Player(static_cast<float>(x), static_cast<float>(y), _id);
					_id++;
					_nbPlayer++;
				} else if (_nbPlayer == 1 && params.nbPlayers > 1) {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x), static_cast<float>(y), _id, 1));
					_player2 = Player(static_cast<float>(x), static_cast<float>(y), _id);
					_nbPlayer++;
					_id++;
				} else if (static_cast<int>(_iaList.size()) < params.nbBots) {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x), static_cast<float>(y), _id));
					_iaList.push_back(Player(static_cast<float>(x), static_cast<float>(y), _id));
					_id++;
//					_nbPlayer++;
				}
			} else
				_vectorEntities[y].push_back(std::make_unique<EntityPos>());
			x += 1;
		}
		y += 1;
	}
}

void GameCore::loadEntities(std::vector<std::vector<char>> &map,
unsigned int &x, unsigned int &y, const parameters &params)
{
	y = 0;
	_iaList.clear();
	for (auto &line : map) {
		x = 0;
		_vectorEntities.push_back(std::vector<std::unique_ptr<EntityPos>>());
		for (auto &c : line) {
			if (c == '0') {
				_vectorEntities[y].push_back(std::make_unique<EntityPos>(ItemStatic::WALL, static_cast<float>(x), static_cast<float>(y), _id));
				_id++;
			} else if (c == '1') {
				_vectorEntities[y].push_back(std::make_unique<EntityPos>(ItemStatic::CRATE, static_cast<float>(x), static_cast<float>(y), _id));
				_id++;
			} else
				_vectorEntities[y].push_back(std::make_unique<EntityPos>());
			x += 1;
		}
		y += 1;
	}
}

void GameCore::loadMovingEntities(std::vector<std::vector<char>> &map,
unsigned int &x, unsigned int &y, const parameters &params)
{
	std::string filename(_params.gameName.begin(), _params.gameName.end());
	std::ifstream fd(filename);
	std::string line;

	y = 0;
	while (std::getline(fd, line))
		if (line == "separateur")
			break ;
	std::getline(fd, line);
	std::istringstream iss(line);
	std::string tmp;
	iss >> _params.nbPlayers >> _params.nbBots >> _params.split;
	std::getline(fd, line);
	std::istringstream tss(line);
	while (tss >> tmp)
		_params.bonuses.push_back(static_cast<eItem>((std::stoi(tmp))));
	while (std::getline(fd, line)) {
		std::istringstream ss(line);
		std::string tmpstr;
		ss >> tmpstr;
		if (tmpstr == "Player1" || tmpstr == "Player2" || tmpstr == "IA") {
			std::array<std::string, 4> player; // xplayer, yplayer, power, super in this order
			ss >> player[0] >> player[1] >> player[2] >> player[3];
			if (tmpstr == "Player1") {
				std::array<std::string, 3> stats; // bombscount, speed, kick in this order
				ss >> stats[0] >> stats[1] >> stats[2];
				_vectorEntities[std::stoi(player[1])].push_back(std::make_unique<EntityPos>());
				_mobileEntities.push_back(std::make_unique<Player>(std::stoi(player[0]), std::stoi(player[1]), _id, 0));
				_player1 = Player(std::stoi(player[0]), std::stoi(player[1]), _id);
				_player1.setPower(std::stoi(player[2]));
				_player1.setSuper(std::stoi(player[3]));
				_player1.setBombs(std::stoi(stats[0]));
				_player1.setSpeed(std::stoi(stats[1]));
				_player1.setKick(std::stoi(stats[2]));
				_nbPlayer++;
			} else if (tmpstr == "Player2") {
				std::array<std::string, 3> stats; // bombscount, speed, kick in this order
				ss >> stats[0] >> stats[1] >> stats[2];
				_vectorEntities[std::stoi(player[1])].push_back(std::make_unique<EntityPos>());
				_mobileEntities.push_back(std::make_unique<Player>(std::stoi(player[0]), std::stoi(player[1]), _id, 1));
				_player2 = Player(std::stoi(player[0]), std::stoi(player[1]), _id);
				_player2.setPower(std::stoi(player[2]));
				_player2.setSuper(std::stoi(player[3]));
				_player2.setBombs(std::stoi(stats[0]));
				_player2.setSpeed(std::stoi(stats[1]));
				_player2.setKick(std::stoi(stats[2]));
			} else if (tmpstr == "IA") {
				_vectorEntities[std::round(std::stoi(player[1]))].push_back(std::make_unique<EntityPos>());
				_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(std::stof(player[0])), static_cast<float>(std::stof(player[1])), _id));
				_iaList.push_back(Player(static_cast<float>(std::stof(player[0])), static_cast<float>(std::stof(player[1])), _id));
			}
		} else if (tmpstr == "Bomb") {
			std::array<std::string, 5> bombs;
			ss >> bombs[0] >> bombs[1] >> bombs[2] >> bombs[3] >> bombs[4];
			Bomb tmp(std::ceil(std::stoi(bombs[0]) - 0.5), std::ceil(std::stoi(bombs[1]) - 0.5), _id, std::stoi(bombs[4]));
			tmp.setPower(std::stoi(bombs[2]));
			tmp.setSuper(std::stoi(bombs[3]));
			tmp.setAlive(true);
			_bombs.push_back(tmp);
			_updateEntities.push_back(std::make_unique<Bomb>(std::ceil(std::stoi(bombs[0]) - 0.5), std::ceil(std::stoi(bombs[1]) - 0.5), _id, std::stoi(bombs[4])));
		}
		_id++;
	}
}

std::vector<std::vector<char>> GameCore::loadGame(std::wstring filename)
{
	std::vector<std::vector<char>> map;
	std::string file;
	file.assign(filename.begin(), filename.end());
	std::ifstream fd(/*file);*/"save.txt");
	std::string line;

	while (std::getline(fd, line))
	{
		if (line == "separateur")
			break ;
		std::vector<char> tmp;
		for (char c : line)
			tmp.push_back(c);
		map.push_back(tmp);
		tmp.clear();
	}
	return (map);
}

void GameCore::getMapFromFile(Map map, parameters params)
{
		std::ifstream file(map.fileName);
	unsigned int x = 0;
	unsigned int y = 0;
	std::string line;

	_nbPlayer = 0;
	_iaList.clear();
	if (!file.is_open()) {
		std::cout << "Open has failed\n";
	} else {
		std::cout << "Open success\n";
		while (getline(file, line)) {
			x = 0;
			_vectorEntities.push_back(std::vector<std::unique_ptr<EntityPos>>());
		 	for (unsigned int j = 0; line[j] != 0; ++j) {
				if (line[j] == '0') {
					_vectorEntities[y].push_back(std::make_unique<EntityPos>(ItemStatic::WALL, static_cast<float>(x), static_cast<float>(y), _id));
					_id++;
				} else if (line[j] == '1') {
					_vectorEntities[y].push_back(std::make_unique<EntityPos>(ItemStatic::CRATE, static_cast<float>(x), static_cast<float>(y), _id));
					_id++;
				} else if (line[j] == '4') {
					_vectorEntities[y].push_back(std::make_unique<EntityPos>());
					if (_nbPlayer == 0) {
						_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x), static_cast<float>(y), _id, 0));
						_player1 = Player(static_cast<float>(x), static_cast<float>(y), _id);
						_id++;
						_nbPlayer++;
					} else if (_nbPlayer == 1 && params.nbPlayers > 1) {
						_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x), static_cast<float>(y), _id, 1));
						_player2 = Player(static_cast<float>(x), static_cast<float>(y), _id);
						_nbPlayer++;
						_id++;
					} else if (static_cast<int>(_iaList.size()) < params.nbBots) {
						_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x), static_cast<float>(y), _id));
						_iaList.push_back(Player(static_cast<float>(x), static_cast<float>(y), _id));
						_id++;
			//			_nbPlayer++;
					}
				} else
					_vectorEntities[y].push_back(std::make_unique<EntityPos>());
				x += 1;
			}
			y += 1;
		}
	}
	_size.x = x;
	_size.y = y;
}

void    GameCore::init(parameters &params)
{
	unsigned int x = 0;
	unsigned int y = 0;
	_i = 0;
	_bubgCounter = 1000;
	MapGenerator generator(params.mapSize.first, params.mapSize.second);
	_nbPlayer = 0;
	std::vector<std::vector<char>> map;
	_params = params;
	if (params.state == GameState::NEWGAME) {
		std::cout << "Initializing new game" << std::endl;
		if (params.map.mapName == "Random") {
			generator.generateMap();
			generator.generatePlayers(params.nbPlayers, params.nbBots);
			generator.dispMap();
			map = generator.getMap();
			createEntities(map, x, y, params);
		} else
			getMapFromFile(params.map, params);
	}
	if (params.state == GameState::LOADGAME) {
		std::cout << "Loading game from save" << std::endl;
		map = loadGame(params.gameName);
		loadEntities(map, x, y, params);
		loadMovingEntities(map, x, y, params);
		params.split = _params.split;
		params.gameName = _params.gameName;
	}
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID, "Resume", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 1, "Save and Quit", (SCREEN_WIDTH / 2) - 200, 350, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 2, "Main Menu", (SCREEN_WIDTH / 2) - 200, 500, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 3, "Quit", (SCREEN_WIDTH / 2) - 200, 650, 400, 100)));
	_size.x = x;
	_size.y = y;
	_bubgDir = {1, 0};
	_bubgPos = {1, 1};
	_mapClosing = false;
}

GameCore::~GameCore()
{
	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
}

pairUC GameCore::getSize() const
{
	return (std::make_pair(_size.x, _size.y));
}

std::vector<std::vector<std::unique_ptr<EntityPos>>> &GameCore::getEntities()
{
	return _vectorEntities;
}

std::vector<std::unique_ptr<IEntity>> &GameCore::getMobileEntities()
{
	return _mobileEntities;
}

std::vector<std::unique_ptr<IEntity>> &GameCore::getUpdateEntities()
{
	return _updateEntities;
}

void GameCore::releaseUpdateEntities()
{
	for (auto &i : _updateEntities)
		i.release();
	_updateEntities.clear();
}

std::vector<std::pair<int, Entity>> &GameCore::getEntitiesToRemove()
{
	return _entitiesToRemove;
}

void GameCore::playerDropBomb(Player &player)
{
	auto pos = player.getPos();
	for (auto &a : _bombs) {
			if (a.getPos().first == std::ceil(pos.first - 0.5) &&
			    std::ceil(pos.second - 0.5) == a.getPos().second) {
				pos.first = -1;
				pos.second = -1;
				return;
			}
	}
	if (pos.first != -1 && pos.second != -1) {
		Bomb tmp(std::ceil(pos.first - 0.5), std::ceil(pos.second - 0.5), _id, player.getId());
		player.dropBomb();
		tmp.setPower(player.getPower());
		tmp.setSuper(player.getSuper());
		tmp.setAlive(true);
		_bombs.push_back(tmp);
		_updateEntities.push_back(std::make_unique<Bomb>(std::ceil(pos.first - 0.5), std::ceil(pos.second - 0.5), _id, player.getId()));
		_id++;
	}
}

void GameCore::bombManager(Actions &act)
{
	for (auto &a : _bombs) {
		if (a.isOutFire()) {
			for (auto &b : a.getFlames())
				_entitiesToRemove.push_back(std::make_pair<int, Entity>(b.getId(),
							b.getType()));
		}	
	}
	_bombs.erase(std::remove_if(_bombs.begin(), _bombs.end(), [](const Bomb &x) {
			     return x.isOver();
		     }),
		     _bombs.end());
	if (act.space == true && _player1.getBombCount() > 0 && _player1.isAlive())
		playerDropBomb(_player1);
	if (act.W == true && _player2.getBombCount() > 0 && _player2.isAlive())
		playerDropBomb(_player2);
	for (auto &a : _bombs) {
		if (a.getOwner() == static_cast<unsigned int>(_player1.getId()) && _params.nbPlayers == 1)
			a.tick(_id, _vectorEntities, _entitiesToRemove, _params.bonuses, _player1.getPos());
		else
			a.tick(_id, _vectorEntities, _entitiesToRemove, _params.bonuses);
		if (a.isExplode()) {
			std::vector<Fire> &vec = a.getFlames();
			for (auto &b : vec) {
				_updateEntities.push_back(std::unique_ptr<IEntity>(&b));
				if (std::round(_player1.getPos().first) == b.getPos().first &&
				std::round(_player1.getPos().second) == b.getPos().second) {
					if (_player1.hasShield()) {
						int tmp = _player1.rmShield();
						_entitiesToRemove.push_back(std::pair<int, Entity>(tmp, Entity::SPHERE));
					} else
						_player1.setAlive(false);
					_updateEntities.push_back(std::unique_ptr<IEntity>(&_player1));
				}
				if (std::round(_player2.getPos().first) == b.getPos().first &&
				std::round(_player2.getPos().second) == b.getPos().second) {
					if (_player2.hasShield()) {
						int tmp = _player2.rmShield();
						_entitiesToRemove.push_back(std::pair<int, Entity>(tmp, Entity::SPHERE));
					} else
						_player2.setAlive(false);
					_updateEntities.push_back(std::unique_ptr<IEntity>(&_player2));
				}
				for (auto &it : _iaList) {
					if (std::round(it.getPos().first) == b.getPos().first &&
					std::round(it.getPos().second) == b.getPos().second) {
						if (it.hasShield()) {
							int tmp = it.rmShield();
							_entitiesToRemove.push_back(std::pair<int, Entity>(tmp, Entity::SPHERE));
						} else
							it.setAlive(false);
						_updateEntities.push_back(std::unique_ptr<IEntity>(&it));
					}
				}
				for (auto &c : _bombs) {
					if (c.isAlive() && c.getPos().first == b.getPos().first
					&& c.getPos().second == b.getPos().second)
						c.detonate();
				}
			}
			_entitiesToRemove.push_back(std::pair<int, Entity>(a.getId(), Entity::SPHERE));
			if (a.getOwner() == static_cast<unsigned int>(_player1.getId()))
				_player1.addBomb();
			if (a.getOwner() == static_cast<unsigned int>(_player2.getId()))
				_player2.addBomb();
			break;
		} else if (a.isAlive() && a.isPushed()) {
			if (_vectorEntities[a.getNextPos().second][a.getNextPos().first]->isEmpty() == true || 
				_vectorEntities[a.getNextPos().second][a.getNextPos().first]->getEntity()->getType() == Entity::ITEM) {
				if (thereIsBomb(a.getNextPos().first, a.getNextPos().second)) {
					for (auto &it : _bombs) {
						if (it.getPos().first == a.getNextPos().first && it.getPos().second == a.getNextPos().second)
							a.collide(it);
					}
				}
				a.move();
				_updateEntities.push_back(std::unique_ptr<IEntity>(&a));
			} else
				a.takeDir({0, 0}, 0);
		}
	}
}

bool GameCore::thereIsBomb(int x, int y)
{
	for (auto &it : _bombs)
	{
		if (it.getPos().first == x && it.getPos().second == y) {
			return (true);
		}
	}
	return (false);
}

void	GameCore::movePlayer(std::pair<float, float> from, std::pair<int, int> dir, Player &player, float rotation)
{
	if (_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->isEmpty() == true) {
		if ((thereIsBomb(std::round(from.first + 0.5 * dir.first), std::round(from.second + 0.5 * dir.second)) == false ||
		thereIsBomb(std::round(from.first), std::round(from.second)) == true)) {
			player.setPos(from.first + (0.07 + player.getSpeed()) * dir.first, from.second + (0.07 + player.getSpeed()) * dir.second);
			for (auto &it : player.getShields()) {
				it.setPos(from.first + (0.07 + player.getSpeed()) * dir.first, from.second + (0.07 + player.getSpeed()) * dir.second);
				_updateEntities.push_back(std::unique_ptr<IEntity>(new Shield(it)));
			}
		}
		else if (thereIsBomb(std::round(from.first + 0.5 * dir.first), std::round(from.second + 0.5 * dir.second)) && player.hasKick()) {
			for (auto &it : _bombs) {
				if (it.getPos().first == std::round(from.first + 0.5 * dir.first) && it.getPos().second == std::round(from.second + 0.5 * dir.second)) {
					it.takeDir(dir, player.getSpeed());
					break ;
				}
			}
		}
	} else if (_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->getType() == Entity::ITEM) {
		player.pickupItem(_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->getEntity(), _id, _updateEntities);
		_entitiesToRemove.push_back(std::make_pair<int, Entity>(_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->getId(),
		_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->getType()));
		_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->removeFirstEntity();
		player.setPos(from.first + (0.07 + player.getSpeed()) * dir.first, from.second + (0.07 + player.getSpeed()) * dir.second);
	}
	player.setRotation(rotation);
}

bool 	GameCore::playerMovement(Actions act)
{
	bool changed = false;
	std::pair<float, float>	playerPos;

	movement	movement_table[8] = {
		{act.right, std::make_pair(1, 0), 0.0f, 1},
		{act.left, std::make_pair(-1, 0), 180.0f, 1},
		{act.up, std::make_pair(0, 1), -90.0f, 1},
		{act.down, std::make_pair(0, -1), 90.0f, 1},
		{act.D, std::make_pair(1, 0), 0.0f, 2},
		{act.Q, std::make_pair(-1, 0), 180.0f, 2},
		{act.Z, std::make_pair(0, 1), -90.0f, 2},
		{act.S, std::make_pair(0, -1), 90.0f, 2}
	};
	for (int i = 0; i < (_params.nbPlayers > 1 ? 8 : 4); i++) {
		if (movement_table[i].action == true) {
			playerPos = (movement_table[i].player == 1) ? _player1.getPos() : _player2.getPos();
			movePlayer(playerPos, movement_table[i].dir, (movement_table[i].player == 1) ? _player1 : _player2, movement_table[i].rotation);
			changed = true;
		}
	}
	return (changed);
}

void GameCore::initEndScreen(STATE &state, char whoAlive)
{
	switch (whoAlive) {
		case 1:
			_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, LOSE_ID,
			"Player 1 won", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
			break;
		case 2:
			_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, WIN_P2_ID,
			"Player 2 won !", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
			break;
		case 3:
			_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, WIN_P1_ID,
			"IA Won !", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
			break;
		case 4:
			_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, WIN_P1_ID,
			"Draw !", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
			break;
		case 5:
			_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, WIN_P1_ID,
			"You won !", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
			break;
	}
	_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PLAY_AGAIN_ID, "Play again", (SCREEN_WIDTH / 2) - 200, 400, 400, 100)));
	_endItem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, QUIT_END_ID, "Quit", (SCREEN_WIDTH / 2) - 200, 600, 400, 100)));
	state = STATE::END;
}

bool GameCore::checkEnd(STATE &state)
{
	int nbIaAlive = std::count_if(_iaList.begin(), _iaList.end(), [](Player i){return i.isAlive() == true;});

//	std::cout << "nbPlayer :" << _nbPlayer << ", nb IA alive : " << nbIaAlive << std::endl;
//	std::cout << "Player 1 is " << (_player1.isAlive() ? "true" : "false") << ", player 2 is " << (_player2.isAlive() ? "true" : "false") << std::endl;
	if (_nbPlayer == 2 && _player1.isAlive() == true &&
	_player2.isAlive() == false && nbIaAlive == 0) {
		initEndScreen(state, 1); // p1 win
	} else if (_nbPlayer == 2 && _player1.isAlive() == false &&
	_player2.isAlive() == true && nbIaAlive == 0) {
		initEndScreen(state, 2); // P2 win
	} else if (_player1.isAlive() == true && _nbPlayer == 1 && nbIaAlive <= 0) {
		initEndScreen(state, 5); // P1 win alone
	} else if (_nbPlayer == 2 && _player1.isAlive() == false
	&& _player2.isAlive() == false) {
		initEndScreen(state, 3); // IA Win
	} else if (_player1.isAlive() == false && _nbPlayer == 1)
		initEndScreen(state, 3); // IA Win
	if (state == STATE::END) {
		if (_nbPlayer == 2)
			_params.split = true;
		return true;
	}
	return false;
}

int	GameCore::dodgeBomb(std::pair<float, float> bombPos, std::pair<float, float> myPos, Player &player)
{
	if (bombPos.second == std::round(myPos.second)) {
		if (_vectorEntities[std::round(myPos.second + 1)][std::round(myPos.first)]->isEmpty()) {
			movePlayer(myPos, {0, 1}, player, -90.0f);
		}
		else if (_vectorEntities[std::round(myPos.second - 1)][std::round(myPos.first)]->isEmpty())
			movePlayer(myPos, {0, -1}, player, 90.0f);
		else {
			if (bombPos.first > myPos.first)
				movePlayer(myPos, {-1, 0}, player, 0.0f);
			else
				movePlayer(myPos, {1, 0}, player, 180.0f);
		}
	}
	else if (bombPos.first == std::round(myPos.first)) {
		if (_vectorEntities[std::round(myPos.second)][std::round(myPos.first + 1)]->isEmpty())
			movePlayer(myPos, {1, 0}, player, 0.0f);
		else if (_vectorEntities[std::round(myPos.second)][std::round(myPos.first - 1)]->isEmpty())
			movePlayer(myPos, {-1, 0}, player, 180.0f);
		else {
			if (bombPos.second > myPos.second)
				movePlayer(myPos, {0, -1}, player, 90.0f);
			else
				movePlayer(myPos, {0, 1}, player, -90.0f);
		}
	}
	return 1;
}

bool	GameCore::haveBombed(Player player)
{
	int	id = player.getId();
	int	posed = 0;

	for (auto &it : _bombs) {
		if (it.getOwner() == static_cast<size_t>(id))
			posed = 1;
	}
	return (posed == 1) ? true : false;
}

bool	GameCore::isThereFreeTile()
{
	pairUC	dir = turnLeft(_bubgDir);
	pairUC	pos = _bubgPos;
	pairUC	size = {_vectorEntities[0].size(), _vectorEntities.size()};

	while (pos.first >= 0 && pos.second >= 0 && pos.first < size.first && pos.second < size.second) {
		if (_vectorEntities[pos.second][pos.first]->isEmpty() || _vectorEntities[pos.second][pos.first]->getEntity()->getType() != Entity::CUBE ||
			!static_cast<ACube*>(_vectorEntities[pos.second][pos.first]->getEntity().get())->isDestructible()) {
			return (true);
		}
		pos.first += dir.first;
		pos.second += dir.second;
	}
	return (false);
}

pairUC	GameCore::turnLeft(pairUC tmp)
{
	pairUC	dir;

	if (tmp.first == 1)
		dir = {0, 1};
	else if (tmp.second == -1)
		dir = {1, 0};
	else if (tmp.first == -1)
		dir = {0, -1};
	else if (tmp.second == 1)
		dir = {-1, 0};
	return (dir);
}

void	GameCore::bubgKillPlayer()
{
	if (_player1.isAlive() && std::round(_player1.getPos().first) == _bubgPos.first && std::round(_player1.getPos().second) == _bubgPos.second)
			_player1.setAlive(false);
	if (_player2.isAlive() && std::round(_player2.getPos().first) == _bubgPos.first && std::round(_player2.getPos().second) == _bubgPos.second)
		_player2.setAlive(false);
	for (auto &it : _iaList) {
		if (it.isAlive() && std::round(it.getPos().first) == _bubgPos.first && std::round(it.getPos().second) == _bubgPos.second)
			it.setAlive(false);
	}
}

void	GameCore::bubgFindNextPos()
{
	if (_mapClosing && !isThereFreeTile()) {
		_bubgPos.first -= _bubgDir.first;
		_bubgPos.second -= _bubgDir.second;
		_bubgDir = turnLeft(_bubgDir);
		_bubgPos.first += _bubgDir.first;
		_bubgPos.second += _bubgDir.second;
		return ;
	}
	_vectorEntities[_bubgPos.second][_bubgPos.first]->stomp();
	bubgKillPlayer();
	if (_vectorEntities[_bubgPos.second][_bubgPos.first]->isEmpty())
		_vectorEntities[_bubgPos.second][_bubgPos.first]->addWall(_bubgPos.first, _bubgPos.second, _id);
	if (!_mapClosing)
		_mapClosing = true;
	_bubgPos.first += _bubgDir.first;
	_bubgPos.second += _bubgDir.second;
}

void	GameCore::iaAction(std::unique_ptr<EntityPos> &entity, Player &player, std::pair<int, int> dir, float orientation)
{
	std::pair<int, int>	pos = player.getIa();
	
	if (entity->isEmpty() || entity->getType() == Entity::ITEM)
		movePlayer(player.getPos(), dir, player, orientation);
	else if (entity->getSubType() == ItemStatic::CRATE && !haveBombed(player)) {
	        playerDropBomb(player);
		player.setIa(std::make_pair((pos.first == 0) ? 0 : pos.first * -1, (pos.second == 0) ? 0 : pos.second * -1));
		player.incForceIa();
	}
	else
		player.setIa(std::make_pair(0, 0));
}

bool	GameCore::existBomb(float second, float first)
{
	std::pair<float, float>	bomb;
	
	for (auto &it : _bombs) {
		bomb = it.getPos();
		if (bomb.first == std::round(first) || bomb.second == std::round(second))
			return true;
	}
	return false;
}

void	GameCore::iaMoving(Player &player)
{
	std::pair<int, int>	dir = player.getIa();
	std::pair<float, float>	myPos = player.getPos();
	int			rand;

	if (dir == std::make_pair(0, 1)) {
		if (existBomb(myPos.second + 1, myPos.first))
			player.setIa(std::make_pair(0, 0));
		else
			iaAction(_vectorEntities[std::round(myPos.second + 1)][std::round(myPos.first)], player, {0, 1}, -90.0f);
	}
	else if (dir == std::make_pair(0, -1)) {  
		if (existBomb(myPos.second - 1, myPos.first))
			player.setIa(std::make_pair(0, 0));
		else
			iaAction(_vectorEntities[std::round(myPos.second - 1)][std::round(myPos.first)], player, {0, -1}, 90.0f);
	}
	else if (dir == std::make_pair(1, 0)) {
		if (existBomb(myPos.second, myPos.first + 1))
			player.setIa(std::make_pair(0, 0));
		else
			iaAction(_vectorEntities[std::round(myPos.second)][std::round(myPos.first + 1)], player, {1, 0}, 0.0f);
	}
	else if (dir == std::make_pair(-1, 0)) {
		if (existBomb(myPos.second, myPos.first - 1))
			player.setIa(std::make_pair(0, 0));
		else
			iaAction(_vectorEntities[std::round(myPos.second)][std::round(myPos.first - 1)], player, {-1, 0}, 180.0f);
	}
	else if (dir == std::make_pair(0, 0)) {
		std::random_device re;
		std::uniform_int_distribution<int>	distrib{1, 4};
		rand = distrib(re);
		if (rand == 1 && !existBomb(myPos.second + 1, myPos.first))
			player.setIa(std::make_pair(0, 1));
		else if (rand == 2 && !existBomb(myPos.second - 1, myPos.first))
			player.setIa(std::make_pair(0, -1));
		else if (rand == 3 && !existBomb(myPos.second, myPos.first + 1))
			player.setIa(std::make_pair(1, 0));
		else if (rand == 4 && !existBomb(myPos.second, myPos.first - 1))
		        player.setIa(std::make_pair(-1, 0));
	}
}

void	GameCore::handleIA()
{
	int			dodging = 0;
	std::pair<float, float>	myPos;
	std::pair<float, float>	bombPos;

	for (auto &it : _iaList) {
		if (it.isAlive() == false)
			continue ;
		myPos = it.getPos();
		if (it.getForceIa() > 0) {
			movePlayer(myPos, it.getIa(), it, 0.0f);
			it.incForceIa();
			dodging = 1;
		}
		else {
			for (auto &i : _bombs) {
				bombPos = i.getPos();
				if (bombPos.second == std::round(myPos.second) || bombPos.first == std::round(myPos.first))
					dodging = dodgeBomb(bombPos, myPos, it);
			}
		}
		if (dodging == 0)
			iaMoving(it);
		_updateEntities.push_back(std::unique_ptr<IEntity>(&it));
	}
}

void GameCore::displayAroundPlayer(void)
{
	// set updateEnties around the player
	for (int y = _player1.getPos().second - 8; y < _player1.getPos().second + 8; ++y) {
		if (y >= 0 && y < static_cast<int>(_vectorEntities.size()))
			for (int x = _player1.getPos().first - 13; x < _player1.getPos().first + 13; ++x) {
				if (x >= 0 && x < static_cast<int>(_vectorEntities[y].size()) && _vectorEntities[y][x]->isEmpty() == false) {
					_updateEntities.push_back(std::unique_ptr<IEntity>(_vectorEntities[y][x]->getEntity().get()));
					_entitiesToRemove.push_back(std::make_pair<int, Entity>(_vectorEntities[y][x]->getId(),
							_vectorEntities[y][x]->getType()));
				}
			}
	}
	if (_params.nbPlayers > 1)
		for (int y = _player2.getPos().second - 8; y < _player2.getPos().second + 8; ++y) {
			if (y >= 0 && y < static_cast<int>(_vectorEntities.size()))
				for (int x = _player2.getPos().first - 13; x < _player2.getPos().first + 13; ++x) {
					if (x >= 0 && x < static_cast<int>(_vectorEntities[y].size()) && _vectorEntities[y][x]->isEmpty() == false &&
						_updateEntities.end() == find(_updateEntities.begin(), _updateEntities.end(),
								_vectorEntities[y][x]->getEntity())) {
						_updateEntities.push_back(std::unique_ptr<IEntity>(_vectorEntities[y][x]->getEntity().get()));
						_entitiesToRemove.push_back(std::make_pair<int, Entity>(_vectorEntities[y][x]->getId(),
							_vectorEntities[y][x]->getType()));
					}
				}
		}
	// end
}

void GameCore::displayScore()
{
	_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 0, "Speed: " + std::to_string(static_cast<int>(100 * _player1.getSpeed())), 0, 0, 300, 100));
	_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 1, "Bombs: " + std::to_string(_player1.getBombCount()), 0, 100, 300, 100));
	_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 2, "Power: " + std::to_string(_player1.getPower()), 0, 200, 300, 100));
	_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 3, "Super: " + std::string(_player1.getSuper() ? "On" : "Off"), 0, 300, 300, 100));
	_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 4, "Kick: " + std::string(_player1.hasKick() ? "On" : "Off"), 0, 400, 300, 100));
	_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 5, "Shields: " + std::to_string(_player1.getShields().size()) + "/2", 0, 500, 300, 100));
	if (_iaList.size()) {
		int tmp = std::count_if(_iaList.begin(), _iaList.end(), [](const Player &i){ return i.isAlive(); });
		_updateEntities.push_back(std::make_unique<MenuItem>(Entity::LABEL, 6, "IAs : " + std::to_string(tmp) + "/" + std::to_string(_iaList.size()), 0, 600, 300, 100));
	}

}

std::vector<std::unique_ptr<IEntity>> &GameCore::calc(Actions act, STATE &state, parameters &param)
{
	bool changed;

	_entitiesToRemove.clear();
	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
	if (_bubgCounter > 0)
		_bubgCounter -= 1;
	else if (_bubgCounter == 0 && _params.bubg) {
		bubgFindNextPos();
		_bubgCounter = 50;
	}
	changed = playerMovement(act);
	handleIA();
	bombManager(act);
	if (changed) {
		_updateEntities.push_back(std::unique_ptr<IEntity>(&_player1));
		if (_params.nbPlayers > 1)
			_updateEntities.push_back(std::unique_ptr<IEntity>(&_player2));
		else
			displayScore();
	}
	displayAroundPlayer();
	if (checkEnd(state) == true)
		return _updateEntities;
	return (_updateEntities);
}


void GameCore::removeAll()
{
	for (auto &it : _vectorEntities)
		it.clear();
	_vectorEntities.clear();
	_mobileEntities.clear();
	_bombs.clear();
	_endItem.clear();
	_pauseitem.clear();
	_entitiesToRemove.clear();
	for (auto &it : _updateEntities)
		it.release();
	_updateEntities.clear();
	_entities.clear();
	_iaList.clear();
	_id = 0;
}

void	GameCore::saveMap(std::ofstream &file)
{
	for (unsigned int idx = 0; idx != _vectorEntities.size(); idx++) {
		for (auto &i2 : _vectorEntities[idx]) {
			if (i2->isEmpty() == false && i2->getType() == Entity::CUBE) {
				if (i2->getSubType() == ItemStatic::WALL)
					file << "0";
				else if (i2->getSubType() == ItemStatic::CRATE)
					file << "1";
			}
			else
				file << " ";
		}
		file << "\n";
	}
}

std::map<eItem, std::string> myItem =
{
	{BOMB_UP, "BOMB_UP"},
	{POWER_UP, "POWER_UP"},
	{SPEED, "SPEED"},
	{SUPER_BOMB, "SUPER_BOMB"},
//	{WALL_PASS, "WALL_PASS"},
	{KICK, "KICK"},
	{SHIELD, "SHIELD"}
};

void 	GameCore::saveParameters(std::ofstream &file)
{
	file << _params.nbPlayers << " " << _params.nbBots << " " << _params.split << "\n";
	for (auto &i : _params.bonuses)
		file << i << " ";
	file << "\n";
}

void 	GameCore::saveMobileEntities(std::ofstream &file)
{
	file << "Player1 " << std::round(_player1.getX()) << " " << std::round(_player1.getY()) << " " <<  _player1.getPower()
	<< " " << _player1.getSuper() << " " << _player1.getMaxBombs() << " " << _player1.getSpeed() << " " << _player1.hasKick() << "\n";
	if (_player2.getX() != -1 && _player2.getY() != -1)
		file << "Player2 " << std::round(_player2.getX()) << " " << std::round(_player2.getY()) << " " <<  _player2.getPower()
		<< " " << _player2.getSuper() << " " << _player2.getMaxBombs() << " " << _player2.getSpeed() << " " << _player1.hasKick() << "\n";
	for (auto &i : _bombs)
		file << "Bomb " << i.getX() << " " << i.getY() << " " << i.getPower() << " " << i.getSuper() << " " << i.getOwner() << "\n";
	for (auto &i :_iaList)
		file << "IA " << i.getX() << " " << i.getY() << " " << i.getPower() << " " << i.getSuper() << "\n";
}

void GameCore::handlePause(Actions actions, STATE &state)
{
	if (actions.buttonPressed == PAUSE_ID)
		state = STATE::GAME;
	if (actions.buttonPressed == PAUSE_ID + 1) {
		std::string filename(_params.gameName.begin(), _params.gameName.end());
		if (_params.state == GameState::NEWGAME)
			filename = SAVE_DIR + filename + ".txt";
		std::ofstream file(filename);
		saveMap(file);
		file << "separateur\n";
		saveParameters(file);
		saveMobileEntities(file);
		file.close();
	}
	if (actions.buttonPressed == PAUSE_ID + 2) {
		removeAll();
		state = STATE::MENU;
	}
	if (actions.buttonPressed == PAUSE_ID + 3)
		state = STATE::EXIT;
}

int GameCore::getEndId() const
{
	if (!_player1.isAlive() && !_player2.isAlive())
		return LOSE_ID;
	else if (!_player1.isAlive())
		return WIN_P2_ID;
	else if (!_player2.isAlive())
		return WIN_P1_ID;
	else
		return LOSE_ID;
}

void GameCore::handleEnd(Actions actions, STATE &state)
{
	if (actions.buttonPressed == PLAY_AGAIN_ID) {
		removeAll();
		state = STATE::GAME;
	} if (actions.buttonPressed == QUIT_END_ID) {
		removeAll();
		state = STATE::EXIT;
	}
}

std::vector<std::unique_ptr<IEntity>> &GameCore::createPause()
{
	return _pauseitem;
}

std::vector<std::unique_ptr<IEntity>> &GameCore::createEndScreen()
{
	return _endItem;
}

std::vector<std::unique_ptr<IEntity>> &GameCore::createLoadScreen()
{
	return _loadScreenItem;
}

std::vector<std::unique_ptr<IEntity>>	&GameCore::getAllMap()
{
	for (auto &line : _vectorEntities) {
		for (auto &ref : line) {
			if (!ref->isEmpty() && ref->getType() == Entity::CUBE) {
				ACube	*tmp = static_cast<ACube*>(ref->getEntity().get());
				_updateEntities.push_back(std::make_unique<ACube>(tmp->getPos().first, tmp->getPos().second, tmp->getTexture(), tmp->getId(), true));
			}
		}
	}
	return (_updateEntities);
}
