#include <SDL2/SDL.h>
#include "engine.h"

// F-it, a global to make the pain go away.
Engine engine;

int main(int argc, char **argv)
{
	uint32_t previous_milliseconds, current_milliseconds, elapsed_milliseconds;

	// TODO: Load config
	engine.state = StartUp;

	while(engine.state != Closing) {
		current_milliseconds = SDL_GetTicks();
		elapsed_milliseconds = current_milliseconds - previous_milliseconds;

		switch(engine.state) {
			case StartUp:
				engine.map->computeFov();
				engine.state = Idle;
				break;
			case Idle:
				engine.pollEvent();
				break;
			case NewTurn:
				engine.update();
				engine.state = Idle;
				break;
		}

		if(elapsed_milliseconds > 1000) {
			previous_milliseconds = current_milliseconds;
			engine.switchSpritesheet();
		}

		engine.draw();
	}
	return 0;
}

