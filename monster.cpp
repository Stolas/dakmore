#include "monster.h"


Monster::Monster(const char *name, Sprite skin, int x, int y) : Actor(name, skin, x, y)
{
	// TODO: Set strneght
}

Monster::~Monster()
{
	freeName();
}

void Monster::update()
{
	// Does stuff
}
