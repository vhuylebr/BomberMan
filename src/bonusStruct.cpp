typedef struct s_bonus {
	int id;
	eItem bonus;	
} t_bonus;

static const t_bonus bonusButton[NB_ITEMS] {
	{9, eItem::BOMB_UP},
	{11, eItem::POWER_UP},
	{13, eItem::SUPER_BOMB},
	{15, eItem::SPEED},
	{17, eItem::WALL_PASS},
	{19, eItem::KICK},
};

static void changeBonus(const eItem bonus, std::map<eItem, bool> &map_bonus)
{
	eItem key = static_cast<eItem>(bonus);
	map_bonus[key]= (map_bonus[key] ? false : true);
}

void Menu::checkBonus(Actions &actions)
{
	for (int i = 0; i < NB_ITEMS; i++) {
		if (bonusButton[i].id == actions.buttonPressed) {
			changeBonus(bonusButton[i].bonus, _map_bonus);
		}
	}
}