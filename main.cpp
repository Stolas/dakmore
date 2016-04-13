#include <SDL2/SDL.h>
#include "engine.h"

// F-it, a global to make the pain go away.
Engine engine;

int main(int argc, char **argv)
{
	bool running;
	uint32_t previous_milliseconds, current_milliseconds, elapsed_milliseconds;
	previous_milliseconds = 0;

	// TODO: Load config
	engine.state = StartUp;

	for(running=true;running;) {
		current_milliseconds = SDL_GetTicks();
		elapsed_milliseconds = current_milliseconds - previous_milliseconds;

		switch(engine.state) {
			case StartUp:
				printf("State -> Startup\n");
				engine.map->computeFov();
				engine.state = Idle;
				break;
			case Idle:
				engine.pollEvent();
				if(engine.state == Closing) {
					running = false;
				}
				break;
			case NewTurn:
				printf("State -> NewTurn\n");
				engine.update();
				engine.state = Idle;
				break;
			default:
				printf("State -> Closing\n");
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
