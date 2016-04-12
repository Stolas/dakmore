#include "map.h"
#include "bsplistener.h"
#include "engine.h"
#include "monster.h"
#include "sprites.h"


// TODO: Reintroduce TCODMap;

Map::Map(int width, int height)
{
	this->width = width;
	this->height = height;

	// map = new TCODMap(width, height);
	tiles = new Tile[width*height];
	for(int tile_x = 0; tile_x < width; ++tile_x) {
		for(int tile_y = 0; tile_y < height; ++tile_y) {
			setTileExplored(tile_x, tile_y, false);
			setTileType(tile_x, tile_y, Wall);
		}
	}

	// Bsp bsp;
	// bsp.x = bsp.y = 0;
	// bsp.w = this->width;
	// bsp.h = this->height;

	// bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
	// BspListener listener(this);
	// bsp.traverseInvertedLevelOrder(&listener, NULL);
	createRoom(true, 10, 10, 20, 20);
	
	
	spawnMonster(12, 15);
}

Map::~Map()
{
	delete [] tiles;
	// delete map;
}

bool Map::isInFov(int x, int y)
{
	// if(map->isInFov(x, y)) {
		setTileExplored(x, y, true);
		return true;
	// }
	// return false;
}

void Map::computeFov()
{
	// map->computeFov(engine.player->position.x, engine.player->position.y, engine.fovRadius);
}

void Map::draw()
{
	Sprite sprite;
	for(int x = 0; x < width ; ++x) {
		for(int y = 0; y < height; ++y) {
			if(isInFov(x, y)) {
				switch(getTileType(x, y)) {
					case Wall:
						sprite = SpriteWall;
						break;
					default:
						sprite = SpriteFloor;
						break;
				}
			} else {
				if(getTileExplored(x, y)) {
					switch(getTileType(x, y)) {
						case Wall: // TODO : Add Shade
							sprite = SpriteWall;
							break;
						default:
							sprite = SpriteFloor;
							break;
					}
				}
			}

			engine.putChar(x, y, sprite);
		}
	}
}

void Map::dig(int x1, int y1, int x2, int y2)
{
	// Reminder, do _not_ use the xor-swap here.
	if(x2 < x1) {
		int temp = x2;
		x2 = x1;
		x1 = temp;
	}

	if(y2 < y1) {
		int temp = y2;
		y2 = y1;
		y1 = temp;
	}

	for(int tile_x = x1; tile_x <= x2; ++tile_x) {
		for(int tile_y = y1; tile_y <= y2; ++tile_y) {
			setTileType(tile_x, tile_y, Empty);
		}
	}
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
	this->dig(x1, y1, x2, y2);
	if(first) {
		// put the player in the first room
		engine.player->position.x = (x1+x2)/2;
		engine.player->position.y = (y1+y2)/2;
	} else {
		// TODO: Drop Monster and items etc
		Random *rng = engine.getRandomInstance();
		int monsters = rng->getInt(0, 7);
		while(monsters > 0) {
			int x = rng->getInt(x1, x2);
			int y = rng->getInt(y1, y2);
			if(checkTileWalk(x, y)) {
				spawnMonster(x, y);
			}

			monsters--;
		}
	}
}


bool Map::checkTileType(int x, int y, TileType type)
{
	return tiles[x+y*width].type == type;
}

bool Map::checkActorTile(int x, int y)
{
	std::list<Actor*>::iterator iterator = engine.actors.begin();
	while(iterator != engine.actors.end()) {
		Actor *actor = (*iterator);

		if(actor->position.x == x) {
			if(actor->position.y == y) {
				return true;
			}
		}
		iterator++;
	}
	return false;
}

Actor* Map::getActorTile(int x, int y)
{
	std::list<Actor*>::iterator iterator = engine.actors.begin();
	while(iterator != engine.actors.end()) {
		Actor *actor = (*iterator);

		if(actor->position.x == x) {
			if(actor->position.y == y) {
				return actor;
			}
		}
		iterator++;
	}
	return NULL;
}

bool Map::checkTileWalk(int x, int y)
{
	if(checkTileType(x, y, Wall)) {
		return false;
	}

	if(checkActorTile(x, y)) {
		return false;
	}

	return true;
}


TileType Map::getTileType(int x, int y)
{
	return tiles[x+y*width].type;
}

void Map::setTileType(int x, int y, TileType type)
{
	switch(type) {
		case Wall:
			// map->setProperties(x, y, false, false);
			break;
		case Empty:
			// map->setProperties(x, y, true, true);
			break;
	}

	tiles[x+y*width].type = type;
}

void Map::setTileExplored(int x, int y, bool explored)
{
	tiles[x+y*width].explored = explored;
}

bool Map::getTileExplored(int x, int y)
{
	return tiles[x+y*width].explored;
}

void Map::spawnMonster(int x, int y)
{
	Random *rng = engine.getRandomInstance();
	if(rng->getInt(0, 100) < 80) {
		engine.actors.push_back(new Monster("Demon", SpriteDemon, x, y));
	} else {
		engine.actors.push_back(new Monster("Goblin", SpriteDemon, x, y));
	}
}
