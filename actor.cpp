#include <string.h>
#include <stdlib.h>
#include "engine.h"
#include "actor.h"



Actor::Actor()
{
	position.x = 0;
	position.y = 0;
	sprite = '?';
	name = NULL;
}

Actor::Actor(const char *name, char sprite, int x, int y)
{
	setName(name);
	this->sprite = sprite;
	position.x = x;
	position.y = y;
}

void Actor::freeName()
{
	if(name != NULL) {
		free(name);
	}
}

bool Actor::setName(const char *name)
{
	this->name = (char*)malloc(strlen(name));
	if(this->name == NULL) {
		// Malloc failed
		return false;
	}

	strncpy(this->name, name, strlen(name));
	return true;
}

char *Actor::getName()
{
	if(name != NULL) {
		return name;
	}
	return (char*)"Unkown Entity";
}

void Actor::draw()
{
	engine.putChar(position.x, position.y, sprite);
}
