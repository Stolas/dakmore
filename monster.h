#ifndef MONSTER_H
#define MONSTER_H

#include "actor.h"

class Monster : public Actor
{
public:
	Monster(const char *name, char skin, int x, int y);
	~Monster();

	void update();
};

#endif // MONSTER_H
