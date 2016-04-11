#include <stdlib.h>
#include <time.h>
#include "random.h"

Random::Random()
{
	srand(time(NULL));
}

Random::Random(unsigned int seed)
{
	srand(seed);
}

int Random::getInt(int min, int max)
{
	return rand() % max + min;
}

int Random::rollDie(int amount, int sides) // 3d6 is 3 times 1 to 6
{
	int total = 0;
	while(amount > 0) {
		total += this->getInt(1, sides);
		amount--;
	}
	return total;
}
