#ifndef RANDOM_H
#define RANDOM_H


class Random
{
public:
	Random();
	Random(unsigned int seed);
	int getInt(int min, int max);
	int rollDie(int amount, int sides);
};

#endif // RANDOM_H
