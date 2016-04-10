#ifndef MAP_H
#define MAP_H

#include "actor.h"

#define ROOM_MAX_SIZE (12)
#define ROOM_MIN_SIZE (6)

typedef enum {
	Empty,
	Wall
} TileType;

struct Tile
{
	TileType type;
	bool explored;
};

class Map
{
public:
	int width;
	int height;

	Map(int width, int height);
	~Map();

	bool isInFov(int x, int y);
	void computeFov();
	void draw();

	bool checkTileType(int x, int y, TileType type);
	bool checkActorTile(int x, int y);
	Actor* getActorTile(int x, int y);
	TileType getTileType(int x, int y);
	bool checkTileWalk(int x, int y);
	void setTileType(int x, int y, TileType type);
	void setTileExplored(int x, int y, bool explored);
	bool getTileExplored(int x, int y);

	void spawnMonster(int x, int y);

protected:
	friend class BspListener;
	Tile *tiles;
	// TODO: TCODMap *map;
	void createRoom(bool first, int x1, int y1, int x2, int y2);

private:
	void dig(int x1, int y1, int x2, int y);
};

#endif // MAP_H
