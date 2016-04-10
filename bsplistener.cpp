#include "bsplistener.h"
#include "engine.h"


BspListener::BspListener(Map *map)
{
	this->map = map;
	this->room_number = 0;
}

bool BspListener::visitNode(Bsp *node, void *user_data)
{
	if(node->isLeaf()) {
		int x, y, width, height;

		Random *rng = engine.getRandomInstance();
		width = rng->getInt(ROOM_MIN_SIZE, node->w-2);
		height = rng->getInt(ROOM_MIN_SIZE, node->h-2);
		x = rng->getInt(node->x+1, node->x+node->w-width-1);
		y = rng->getInt(node->y+1, node->y+node->h-height-1);
		map->createRoom(room_number == 0, x, y, x+width-1, y+height-1);

		if(room_number != 0) {
			// dig a corridor from last room
			map->dig(last_x, last_y, x+width/2, last_y);
			map->dig(x+width/2, last_y,x+width/2, y+height/2);
		}

		last_x = x+width/2;
		last_y = y+height/2;
		room_number++;
	}
	return true;
}

