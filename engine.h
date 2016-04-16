#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <list>
#include "actor.h"
#include "player.h"
#include "map.h"
#include "gui.h"
#include "random.h"
#include "sprites.h"

#define TILE_SIZE (16)

typedef enum GameState {
	StartUp,
	Idle,
	NewTurn,
	Closing
} GameState;

class Engine
{
public:
	std::list<Actor *> actors;
	Player *player;
	Map *map;
	Gui *ui;
	GameState state;
	int fovRadius;

	// TODO:
	// struct controls {
	// 	SDL_Keysym MoveDown;
	// } controls;

	Engine();
	~Engine();
	void pollEvent();
	void update();
	void draw();

	void putChar(int x, int y, Sprite sprite);
	Random *getRandomInstance();
	void switchSpritesheet();

private:
	bool computeFov;
	Random *rnd;
	SDL_Window *window;
	SDL_Surface *spritesheet;

	void loadSpritesheetSurfaces();
};


extern Engine engine;

#endif // ENGINE_H
