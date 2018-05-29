/*
** EPITECH PROJECT, 2018
** game
** File description:
** game
*/

#include "GameCore.hpp"

GameCore::GameCore()
	:_id(1), _player1(-1, -1, -1), _player2(-1, -1, -1)
{
}

void    GameCore::init(pairUC size)
{
	std::string filename = "./media/map1.txt";
	std::ifstream file(filename);
	std::string line;

	std::cout << "Initializing new game" << std::endl;
	unsigned int x1 = 0;
	unsigned int y1 = 0;
	if (!file.is_open()) {
		std::cout << "Open has failed\n";
	} else {
		std::cout << "Open success\n";
		while (getline(file, line)) {
			x1 = 0;
			_vectorEntities.push_back(std::vector<std::unique_ptr<EntityPos> >());
			for (unsigned int j = 0; line[j] != 0; ++j) {
				if (line[j] == '0') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::WALL, static_cast<float>(x1), static_cast<float>(y1), _id));
					_id++;
				} else if (line[j] == '1') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::CRATE, static_cast<float>(x1), static_cast<float>(y1), _id));
					_id++;
				} else if (line[j] == '2') {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x1), static_cast<float>(y1), _id));
					_player1 = Player(static_cast<float>(x1), static_cast<float>(y1), _id);
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
					_id++;
				} else if (line[j] == '3') {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x1), static_cast<float>(y1), _id));
					_player2 = Player(static_cast<float>(x1), static_cast<float>(y1), _id);
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
					_id++;
				} else {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
				}
				x1 += 1;
			}
			y1 += 1;
		}
	}
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID, "Resume", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 1, "Save and Quit", (SCREEN_WIDTH / 2) - 200, 350, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 2, "Main Menu", (SCREEN_WIDTH / 2) - 200, 500, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 3, "Quit", (SCREEN_WIDTH / 2) - 200, 650, 400, 100)));
	_size.x = x1;
	_size.y = y1;
}

void    GameCore::init(parameters params)
{
	std::ifstream file(params.mapname);
	std::string line;

	std::cout << "Initializing new game" << std::endl;
	_size.x = params.mapSize.first;
	_size.y = params.mapSize.second;
	unsigned int x1 = 0;
	unsigned int y1 = 0;
	if (!file.is_open()) {
		std::cout << "Open has failed\n";
	} else {
		std::cout << "Open success\n";
		while (getline(file, line)) {
			x1 = 0;
			_vectorEntities.push_back(std::vector<std::unique_ptr<EntityPos> >());
			for (unsigned int j = 0; line[j] != 0; ++j) {
				if (line[j] == '0') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::WALL, static_cast<float>(x1), static_cast<float>(y1), _id));
					_id++;
				} else if (line[j] == '1') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::CRATE, static_cast<float>(x1), static_cast<float>(y1), _id));
					_id++;
				} else if (line[j] == '2') {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x1), static_cast<float>(y1), _id));
					_player1 = Player(static_cast<float>(x1), static_cast<float>(y1), _id);
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
					_id++;
				} else if (line[j] == '3') {
					_mobileEntities.push_back(std::make_unique<Player>(static_cast<float>(x1), static_cast<float>(y1), _id));
					_player2 = Player(static_cast<float>(x1), static_cast<float>(y1), _id);
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
					_id++;
				} else {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
				}
				x1 += 1;
			}
			y1 += 1;
		}
	}
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID, "Resume", (SCREEN_WIDTH / 2) - 200, 200, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 1, "Save and Quit", (SCREEN_WIDTH / 2) - 200, 350, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 2, "Main Menu", (SCREEN_WIDTH / 2) - 200, 500, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, PAUSE_ID + 3, "Quit", (SCREEN_WIDTH / 2) - 200, 650, 400, 100)));
	_size.x = x1;
	_size.y = y1;
}

GameCore::~GameCore()
{
	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
}

pairUC	GameCore::getSize() const
{
	return (std::make_pair(_size.x, _size.y));
}

void	GameCore::init(const std::string &file)
{
	init(std::make_pair(100, 100));
	std::cout << "Loading " << file << std::endl;
}

std::vector<std::vector<std::unique_ptr<EntityPos> > >	&GameCore::getEntities()
{
	return _vectorEntities;
}

std::vector<std::unique_ptr<IEntity> >	&GameCore::getMobileEntities()
{
	return _mobileEntities;
}

void GameCore::releaseUpdateEntities()
{
	for (auto &i : _updateEntities)
		i.release();
	_updateEntities.clear();
}

std::vector<std::pair<int, Entity> >	&GameCore::getEntitiesToRemove()
{
	return _entitiesToRemove;
}

void	GameCore::bombManager(Actions &act)
{
	for (auto &a : _bombs) {
		if (a.isOutFire()) {
			for (auto &b : a.getFlames()) {
				_updateEntities.push_back(std::unique_ptr<IEntity>(&b));
			}
		}
	} // Plus tard les deux boucles seront assemblables
	_bombs.erase(std::remove_if(_bombs.begin(), _bombs.end(),[](const Bomb& x) {
		return x.isOver();
	}), _bombs.end());
	if (act.space == true && _player1.getBombCount() > 0 && _player1.isAlive()) {
			auto pos = _player1.getPos();
			for (auto &a : _bombs) {
				if (a.getPos().first == std::ceil(pos.first - 0.5) && 
					std::ceil(pos.second - 0.5) == a.getPos().second) {
					pos.first = -1;
					pos.second = -1;
					break ;
				}
			}
			if (pos.first != -1 && pos.second != -1) {
				Bomb	tmp(std::ceil(pos.first - 0.5), std::ceil(pos.second - 0.5), _id++, _player1.getId());
				_player1.dropBomb();
				tmp.setPower(_player1.getPower());
				_bombs.push_back(tmp);
				_updateEntities.push_back(std::unique_ptr<IEntity>(&_bombs.back()));
			}
	} else if (act.W == true && _player2.getBombCount() > 0 && _player2.isAlive()) {
			auto pos = _player2.getPos();
			for (auto &a : _bombs) {
				if (a.getPos().first == std::ceil(pos.first - 0.5) && 
					std::ceil(pos.second - 0.5) == a.getPos().second) {
					pos.first = -1;
					pos.second = -1;
					break ;
				}
			}
			if (pos.first != -1 && pos.second != -1) {
				Bomb	tmp(std::ceil(pos.first - 0.5), std::ceil(pos.second - 0.5), _id++, _player2.getId());
				_player2.dropBomb();
				tmp.setPower(_player2.getPower());
				_bombs.push_back(tmp);
				_updateEntities.push_back(std::unique_ptr<IEntity>(&_bombs.back()));
			}
	}
	for (auto &a : _bombs) {
		a.tick(_id, _vectorEntities, _entitiesToRemove, _updateEntities);
		if (a.isExplode()) {
			std::vector<Fire> &vec = a.getFlames();
			for (auto &b : vec) {
					_updateEntities.push_back(std::unique_ptr<IEntity>(&b));
					if (std::round(_player1.getPos().first) == b.getPos().first &&
						std::round(_player1.getPos().second) == b.getPos().second) {
							_player1.setAlive(false);
							_updateEntities.push_back(std::unique_ptr<IEntity>(&_player1));
					}
					if (std::round(_player2.getPos().first) == b.getPos().first &&
						std::round(_player2.getPos().second) == b.getPos().second) {
							_player2.setAlive(false);
							_updateEntities.push_back(std::unique_ptr<IEntity>(&_player2));
					}
			}
			_updateEntities.push_back(std::unique_ptr<IEntity>(&a));
			if (a.getOwner() == static_cast<unsigned int>(_player1.getId()))
				_player1.addBomb();
			if (a.getOwner() == static_cast<unsigned int>(_player2.getId()))
				_player2.addBomb();
			break;
		}
	}
}

bool	GameCore::thereIsBomb(int x, int y)
{
	for (auto &it : _bombs) {
		if (it.getPos().first == x && it.getPos().second == y) {
			return (true);
		}
	}
	return (false);
}

void	GameCore::movePlayer(std::pair<float, float> from, std::pair<int, int> dir, Player &player, float rotation)
{
	if (_vectorEntities[std::round(from.second + 0.5 * dir.second)][std::round(from.first + 0.5 * dir.first)]->isEmpty() == true &&
		(thereIsBomb(std::round(from.first + 0.5 * dir.first), std::round(from.second + 0.5 * dir.second)) == false ||
		thereIsBomb(std::round(from.first), std::round(from.second)) == true))
		player.setPos(from.first + 0.07 * dir.first, from.second + 0.07 * dir.second);
	player.setRotation(rotation);
}

bool 	GameCore::playerMovement(Actions act)
{
	bool changed = false;

	if (act.right == true) {
		movePlayer(_player1.getPos(), {1, 0}, _player1, 0.0f);
		changed = true;
	}
	if (act.left == true) {
		movePlayer(_player1.getPos(), {-1, 0}, _player1, 180.0f);
		changed = true;
	}
	if (act.up == true) {
		movePlayer(_player1.getPos(), {0, 1}, _player1, -90.0f);
		changed = true;
	}
	if (act.down == true) {
		movePlayer(_player1.getPos(), {0, -1}, _player1, 90.0f);
		changed = true;
	}
	if (act.D == true) {
		movePlayer(_player2.getPos(), {1, 0}, _player2, 0.0f);
		changed = true;
	}
	if (act.Q == true) {
		movePlayer(_player2.getPos(), {-1, 0}, _player2, 180.0f);
		changed = true;
	}
	if (act.Z == true) {
		movePlayer(_player2.getPos(), {0, 1}, _player2, -90.0f);
		changed = true;
	}
	if (act.S == true) {
		movePlayer(_player2.getPos(), {0, -1}, _player2, 90.0f);
		changed = true;
	}
	return (changed);
}

std::vector<std::unique_ptr<IEntity>>	&GameCore::calc(Actions act)
{
	bool changed;

	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
	changed = playerMovement(act);
	if (changed) {
		_updateEntities.push_back(std::unique_ptr<IEntity>(&_player1));
		_updateEntities.push_back(std::unique_ptr<IEntity>(&_player2));
	}
	bombManager(act);
	return (_updateEntities);
}

void	GameCore::removeAll()
{
	for (auto &it : _vectorEntities)
		it.clear();
	_vectorEntities.clear();
	_updateEntities.clear();
	_mobileEntities.clear();
	_bombs.clear();
	_pauseitem.clear();
	_entitiesToRemove.clear();
	_entities.clear();
	_id = 0;
}

void 	GameCore::handlePause(Actions actions, STATE &state)
{
	if (actions.buttonPressed == PAUSE_ID)
		state = STATE::GAME;
	if (actions.buttonPressed == PAUSE_ID + 2) {
		removeAll();
		state = STATE::MENU;
	}
	if (actions.buttonPressed == PAUSE_ID + 3)
		state = STATE::EXIT;
}

std::vector<std::unique_ptr<IEntity>> 	&GameCore::createPause()
{
	return _pauseitem;
}