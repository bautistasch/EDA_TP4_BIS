#ifndef _DRAWWORLD_H
#define _DRAWWORLD_H
#include "World.h"


#define FPS 50.0			//Frames por segundo de muestra



bool initWorld();
void destroyWorld(int error = 0);
void drawWorld(World* world);

bool isEvent(void);
void dispatch(World* world);

bool inRange(Point& point);


#endif // !_DRAWWORLD_H