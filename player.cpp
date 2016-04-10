#include "player.h"
#include "engine.h"
#include "monster.h"

Player::Player() : Actor()
{
	sprite = '@';
	setName("player");
}

Player::Player(int x, int y) : Actor("player", 0, x, y)
{
}

Player::~Player()
{
	freeName();
}

void Player::update()
{
	switch(action) {
		case MoveUp:
			if(engine.map->checkActorTile(position.x, position.y-1)) {
				fightWithActor(position.x, position.y-1);
			} else {
				position.y--;
			}
			break;

		case MoveDown:
			if(engine.map->checkActorTile(position.x, position.y+1)) {
				fightWithActor(position.x, position.y+1);
			} else {
				position.y++;
			}
			break;

		case MoveLeft:
			if(engine.map->checkActorTile(position.x-1, position.y)) {
				fightWithActor(position.x-1, position.y);
			} else {
				position.x--;
			}
			break;

		case MoveRight:
			if(engine.map->checkActorTile(position.x+1, position.y)) {
				fightWithActor(position.x+1, position.y);
			} else {
				position.x++;
			}
			break;
		default: break;
	}
}

void Player::setAction(Action action)
{
	this->action = action;
	engine.state = NewTurn;
}

void Player::fightWithActor(int x, int y)
{
	Actor *actor;

	actor = engine.map->getActorTile(x, y);
	if(actor == NULL) { return; }

	Monster* monster = dynamic_cast<Monster*>(actor);
	if(monster) {
		printf("Fighting with: %s\n", monster->getName());
	} else {
		printf("Hitting a: %s\n", actor->getName());
	}
}
