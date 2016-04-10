#ifndef ACTOR_H
#define ACTOR_H

#include <SDL2/SDL.h>

class Actor
{
public:
	Actor();
	Actor(const char *name, char sprite, int x, int y);

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
	char sprite;
};

#endif // ACTOR_H
