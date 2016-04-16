#ifndef ACTOR_H
#define ACTOR_H

#include <SDL.h>
#include "sprites.h"

class Actor
{
public:
	Actor();
	Actor(const char *name, Sprite sprite, int x, int y);

	char* getName();
	void draw();
	virtual void update() = 0;

	struct {
		int x;
		int y;
	} position;

protected:
	bool setName(const char *name);
	void freeName();

	char *name;
	Sprite sprite;
};

#endif // ACTOR_H
