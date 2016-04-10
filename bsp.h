#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include "random.h"

class Bsp;

class BspCallback {
public :
	virtual ~BspCallback() {}
	virtual bool visitNode(Bsp *node, void *userData) = 0;
};

class Tree {
public :
	Tree *next;
	Tree *father;
	Tree *sons;

	Tree() : next(NULL),father(NULL),sons(NULL){}
	void addSon(Tree *data) {
		data->father=this;
		Tree *lastson = sons;
		while ( lastson && lastson->next ) lastson=lastson->next;
		if ( lastson ) {
			lastson->next=data;
		} else {
			sons=data;
		}
	}

};

class Bsp : public Tree
{
public:
	int x,y,w,h; //
	int position; // position of splitting
	bool horizontal; // horizontal splitting ?
	uint8_t level; // level in the tree

	Bsp() : level(0) {}
	Bsp(Bsp *father, bool left);
	~Bsp();
	bool traversePreOrder(BspCallback *listener, void *userData);
	bool traverseInOrder(BspCallback *listener, void *userData);
	bool traversePostOrder(BspCallback *listener,void *userData);
	bool traverseLevelOrder(BspCallback *listener, void *userData);
	bool traverseInvertedLevelOrder(BspCallback *listener, void *userData);
	void removeSons();
	void splitOnce(bool horizontal, int position);
	void splitRecursive(Random *randomizer, int nb, int minHSize, int minVSize, float maxHRatio, float maxVRatio);

	void resize(int x,int y, int w, int h);

	Bsp *getLeft() const {
		return (Bsp *)sons;
	}
	Bsp *getRight() const {
		return sons ? (Bsp *)(sons->next) : NULL;
	}
	Bsp *getFather() const {
		return (Bsp *)father;
	}

	bool isLeaf() const { return sons == NULL ; }
	bool contains(int px, int py) const;
	Bsp *findNode(int px, int py);
};

#endif // BSP_H
