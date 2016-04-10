#include <list>
#include "engine.h"
#include "bsp.h"

// This code is "borrowed" from libtcod.


Bsp::Bsp(Bsp *father, bool left) {
	if ( father->horizontal ) {
		x=father->x;
		w=father->w;
		y = left ? father->y : father->position;
		h = left ? father->position - y: father->y + father->h - father->position;
	} else {
		y=father->y;
		h=father->h;
		x = left ? father->x : father->position;
		w = left ? father->position - x: father->x + father->w - father->position;
	}
	level=father->level+1;
}

Bsp::~Bsp() {
	removeSons();
}

bool Bsp::traversePreOrder(BspCallback *listener, void *userData) {
	if (!listener->visitNode(this,userData)) return false;
	if ( getLeft() && !getLeft()->traversePreOrder(listener,userData) ) return false;
	if ( getRight() && !getRight()->traversePreOrder(listener,userData)) return false;
	return true;
}

bool Bsp::traverseInOrder(BspCallback *listener, void *userData) {
	if ( getLeft() && !getLeft()->traverseInOrder(listener,userData) ) return false;
	if (!listener->visitNode(this,userData)) return false;
	if ( getRight() && !getRight()->traverseInOrder(listener,userData)) return false;
	return true;
}

bool Bsp::traversePostOrder(BspCallback *listener,void *userData) {
	if ( getLeft() && !getLeft()->traversePostOrder(listener,userData)) return false;
	if ( getRight() && !getRight()->traversePostOrder(listener,userData)) return false;
	if (!listener->visitNode(this,userData)) return false;
	return true;
}

bool Bsp::traverseLevelOrder(BspCallback *listener, void *userData) {
	std::list<Bsp *> stack;
	stack.push_back(this);
	while ( ! stack.empty() ) {
		Bsp *node=stack.front();
		stack.remove(node);
		if ( node->getLeft() ) stack.push_back(node->getLeft());
		if ( node->getRight() ) stack.push_back(node->getRight());
		if (!listener->visitNode(node,userData)) return false;
	}
	return true;
}

bool Bsp::traverseInvertedLevelOrder(BspCallback *listener, void *userData) {
	std::list<Bsp *> stack1;
	std::list<Bsp *> stack2;
	stack1.push_back(this);
	while ( ! stack1.empty() ) {
		Bsp *node=stack1.front();
		stack2.push_back(node);
		stack1.remove(node);
		if ( node->getLeft() ) stack1.push_back(node->getLeft());
		if ( node->getRight() ) stack1.push_back(node->getRight());
	}
	while ( ! stack2.empty() ) {
		Bsp *node=stack2.front();
		stack2.pop_front();
		if (!listener->visitNode(node,userData)) return false;
	}
	return true;
}

void Bsp::removeSons() {
	Bsp *node=(Bsp *)sons;
	while ( node ) {
		Bsp *nextNode=(Bsp *)node->next;
		node->removeSons();
		delete node;
		node=nextNode;
	}
	sons=NULL;
}

void Bsp::splitOnce(bool horizontal, int position) {
	this->horizontal = horizontal;
	this->position=position;
	addSon(new Bsp(this,true));
	addSon(new Bsp(this,false));
}

void Bsp::splitRecursive(Random *randomizer, int nb, int minHSize, int minVSize, float maxHRatio, float maxVRatio) {
	if ( nb == 0 || (w < 2*minHSize && h < 2*minVSize ) ) return;
	bool horiz;
	if (! randomizer ) randomizer=engine.getRandomInstance();
	// promote square rooms
	if ( h < 2*minVSize || w > h * maxHRatio ) horiz = false;
	else if ( w < 2*minHSize || h > w * maxVRatio) horiz = true;
	else horiz = randomizer->getInt(0,1) == 0;
	int position;
	if ( horiz ) {
		position = randomizer->getInt(y+minVSize,y+h-minVSize);
	} else {
		position = randomizer->getInt(x+minHSize,x+w-minHSize);
	}
	splitOnce(horiz,position);
	getLeft()->splitRecursive(randomizer,nb-1,minHSize,minVSize,maxHRatio,maxVRatio);
	getRight()->splitRecursive(randomizer,nb-1,minHSize,minVSize,maxHRatio,maxVRatio);
}

void Bsp::resize(int x,int y, int w, int h) {
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
	if ( getLeft() ) {
		if ( horizontal ) {
			getLeft()->resize(x,y,w,position-y);
			getRight()->resize(x,position,w,y+h-position);
		} else {
			getLeft()->resize(x,y,position-x,h);
			getRight()->resize(position,y,x+w-position,h);
		}
	}
}

bool Bsp::contains(int px, int py) const {
	return (px >= x && py >= y && px < x+w && py < y+h);
}

Bsp *Bsp::findNode(int px, int py) {
	if ( ! contains(px,py) ) return NULL;
	if ( ! isLeaf() ) {
		Bsp *left,*right;
		left=getLeft();
		if ( left->contains(px,py) ) return left->findNode(px,py);
		right=getRight();
		if ( right->contains(px,py) ) return right->findNode(px,py);
	}
	return this;
}
