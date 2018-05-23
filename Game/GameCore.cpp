/*
** EPITECH PROJECT, 2018
** game
** File description:
** game
*/

#include "GameCore.hpp"

GameCore::GameCore()
	:_id(1), _player1(-1, -1, _id)
{
}

void    GameCore::init(pairUC size)
{
	std::string filename = "./media/map1.txt";
	std::ifstream file(filename);
	std::string line;

	std::cout << "Initializing new game" << std::endl;
	_size.x = size.first;
	_size.y = size.second;
	unsigned int x1 = 0;
	unsigned int y1 = 0;
	if (!file.is_open()) {
		std::cout << "Open has failed\n";
	} else {
		std::cout << "Open success\n";
		while (getline(file, line)) {
			x1 = 0;
			_vectorEntities.push_back(std::vector<std::unique_ptr<EntityPos> >());
			for (unsigned int j = 0; line[j] != 0; j++) {
				if (line[j] == '0') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::WALL, static_cast<float>(x1), static_cast<float>(y1), _id));
					_id++;
				} else if (line[j] == '1') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::CRATE, static_cast<float>(x1), static_cast<float>(y1), _id));
					_id++;
				} else if (line[j] == '2') {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>(ItemStatic::PLAYER, static_cast<float>(x1), static_cast<float>(y1), _id));
					_player1 = Player(static_cast<float>(x1), static_cast<float>(y1), _id);
					_id++;
				} else  {
					_vectorEntities[y1].push_back(std::make_unique<EntityPos>());
				}
				x1 += 1;
			}
			y1 += 1;
		}
	}
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1001, "Resume", 600, 200, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1002, "Save and Quit", 600, 400, 400, 100)));
	_pauseitem.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1003	, "Quit", 600, 600, 400, 100)));
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

void    GameCore::init(const std::string &file)
{
	init(std::make_pair(100, 100));
	std::cout << "Loading " << file << std::endl;
}

std::vector<std::vector<std::unique_ptr<EntityPos> > >	&GameCore::getEntities()
{
	return _vectorEntities;
}

void GameCore::releaseUpdateEntities()
{
	for (auto &i : _updateEntities)
		i.release();
	_updateEntities.clear();
}

void	GameCore::bombManager(Actions &act)
{
	for (auto &a : _bombs) {
		if (a.isOutFire()) {
			for (auto &b : a.getFlames()) {
				std::cout << "Fire Out" << std::endl;
				_updateEntities.push_back(std::unique_ptr<IEntity>(&b));
			}
		}
	} // Plus tard les deux boucles seront assemblables
	_bombs.erase(std::remove_if(_bombs.begin(), _bombs.end(),[](const Bomb& x) {
		return x.isOver();
	}), _bombs.end());
	if (act.space == true && _player1.getBombCount() > 0) {
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
				std::cout << "create Bomb" << std::endl;
			}
	}
	for (auto &a : _bombs) {
		a.tick(_id, _vectorEntities);
		if (a.isExplode()) {
			std::vector<Fire> &vec = a.getFlames();
			for (auto &b : vec) {
				//std::cout << "here" << std::endl;
				//b.getPos().second;
				//b.getPos().first;
				//_vectorEntities.size();
				//std::cout << "here2" << std::endl;
					_updateEntities.push_back(std::unique_ptr<IEntity>(&b));
			}
			_updateEntities.push_back(std::unique_ptr<IEntity>(&a));
			_player1.addBomb();
		}
	}
}

std::vector<std::unique_ptr<IEntity>>    &GameCore::calc(Actions act)
{
	bool changed = false;

	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
	if (act.up == true) {
		_player1.setPos(_player1.getPos().first + 0.07, _player1.getPos().second);
		_player1.setRotation(0.0f);
		changed = true;
	}
	if (act.down == true) {
		_player1.setPos(_player1.getPos().first - 0.07, _player1.getPos().second);
		_player1.setRotation(180.0f);
		changed = true;
	}
	if (act.left == true) {
		_player1.setPos(_player1.getPos().first, _player1.getPos().second + 0.07);
		_player1.setRotation(-90.0f);
		changed = true;
	}
	if (act.right == true) {
		_player1.setPos(_player1.getPos().first, _player1.getPos().second - 0.07);
		_player1.setRotation(90.0f);
		changed = true;
	}
	if (changed)
		_updateEntities.push_back(std::unique_ptr<IEntity>(&_player1));
	
	bombManager(act);
	return (_updateEntities);
}

void 	GameCore::handlePause(Actions actions, STATE &state)
{
	if (actions.buttonPressed == 1001)
		state = STATE::GAME;
	if (actions.buttonPressed == 1003)
		state = STATE::EXIT;
}

std::vector<std::unique_ptr<IEntity>> 	&GameCore::createPause()
{
	return _pauseitem;
}