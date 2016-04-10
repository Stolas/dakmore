#include <SDL2/SDL_image.h>
#include "engine.h"

static void panic(char *message, ...) {
	va_list args;
	char buffer[128];

	va_start(args, message);
	vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	buffer[sizeof(buffer) - 1] = '\0';

	fputs(buffer, stderr);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Dungeons of Dakmor", buffer, NULL);

	SDL_Quit();

	exit(EXIT_FAILURE);
}

Engine::Engine() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		panic("Unable to initialize SDL: %s.", SDL_GetError());
	}

	window = SDL_CreateWindow("Dungeons of Dakmor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		panic("Unable to create a window: %s.", SDL_GetError());
	}

	fovRadius = 10;
	computeFov = true;

	rnd = new Random();

	player = new Player();
	actors.push_back(player);

	map = new Map(50, 30);
	ui = new Gui();

	loadSpritesheetSurfaces();
}

Engine::~Engine() {
	// TODO: actors.clearAndDelete();
	delete map;
	delete ui;
	delete rnd;
	SDL_FreeSurface(spritesheet);
}

void Engine::pollEvent()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
	// TCODSystem::checkForEvent(TCOD_KEY_PRESSED, &key, NULL);
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						if(!map->checkTileType(player->position.x, player->position.y-1, Wall)) {
							player->setAction(MoveUp);
						}
						break;
					case SDLK_DOWN:
						if(!map->checkTileType(player->position.x, player->position.y+1, Wall)) {
							player->setAction(MoveDown);
						}
						break;
					case SDLK_LEFT:
						if(!map->checkTileType(player->position.x-1, player->position.y, Wall)) {
							player->setAction(MoveLeft);
						}
						break;
					case SDLK_RIGHT:
						if(!map->checkTileType(player->position.x+1, player->position.y, Wall)) {
							player->setAction(MoveRight);
						}
						break;
					default: break;
				}
				break;
			case SDL_QUIT:
				state = Closing;
				break;
			default: break;
		}

	}
}

void Engine::update()
{
	std::list<Actor*>::iterator iterator = actors.begin();
	while(iterator != actors.end()) {

		Actor *actor = (*iterator);
		// if(!actor) {
		// 	Player* actor = dynamic_cast<Player*>(*iterator);
		// 	if(!actor) {
		// 		Actor *actor = (*iterator);
		// 	}
		// }

		// TODO: add speed modifiers
		actor->update();


		iterator++;
	}

	if(computeFov) {
		map->computeFov();
	}
}

void Engine::draw()
{
	// TCODConsole::root->clear();
	map->draw();

	std::list<Actor*>::iterator iterator = actors.begin();
	while(iterator != actors.end()) {
		Actor *actor = (*iterator);

		if(map->isInFov(actor->position.x, actor->position.y)) {
			actor->draw();
		}

		iterator++;
	}
	ui->draw();

	SDL_UpdateWindowSurface(window);
}

void Engine::putChar(int x, int y, uint16_t sprite)
{
	// TODO: Fix this first.
	SDL_Rect draw_offset, fetch_offset;

	draw_offset.x = (x*TILE_SIZE);
	draw_offset.y = (y*TILE_SIZE);


	// This overflips
	fetch_offset.x = sprite * TILE_SIZE;
	fetch_offset.y = 0;

	while(fetch_offset.x >= spritesheet->w) {
		fetch_offset.y += TILE_SIZE;
		fetch_offset.x -= spritesheet->w;
	}
	// end this

	fetch_offset.w = fetch_offset.h = TILE_SIZE;

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_BlitSurface(spritesheet, &fetch_offset, surface, &draw_offset);

	return;
}

Random *Engine::getRandomInstance()
{
	return rnd;
}

void Engine::loadSpritesheetSurfaces()
{
	spritesheet = IMG_Load("tiles1.png");
}

void Engine::switchSpritesheet()
{ //TODO: Switch for animation.
}
