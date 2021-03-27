#ifndef _WORLD_H
#define _WORLD_H

#include "Worm.h"

class World {
public:
	World();
	Worm worms[2];
	void startMoving(int key);
	void stopMoving(int key);
	bool running(void);
	void refresh(void);
	bool isRunning;
};

#endif