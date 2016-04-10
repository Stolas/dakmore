#ifndef BSPLISTENER_H
#define BSPLISTENER_H

#include "map.h"
#include "bsp.h"

class BspListener : public BspCallback {
private:
	Map *map;
	int room_number;
	int last_x, last_y;

public:
	BspListener(Map *map);
	bool visitNode(Bsp *node, void *user_data);
};

#endif // BSPLISTENER_H
