#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"


typedef enum {
	Wait,
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown
} Action;

class Player : public Actor
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void update();
	void setAction(Action action);
	void fightWithActor(int x, int y);

	Action action;
};

#endif // PLAYER_H
