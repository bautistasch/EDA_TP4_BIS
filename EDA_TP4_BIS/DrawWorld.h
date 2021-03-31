#ifndef _DRAWWORLD_H
#define _DRAWWORLD_H
#include "World.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_color.h>   


#define FPS 50.0			//Frames por segundo de muestra


class AllegroRes {
public:
	bool initWorld();
	void destroyWorld(int error = 0);
	void drawWorld(World* world);
	ALLEGRO_EVENT_QUEUE* eventQueue;

private:
	ALLEGRO_BITMAP* wormJump[10];
	ALLEGRO_BITMAP* wormWalk[15];
	ALLEGRO_BITMAP* backSplash;
	ALLEGRO_TIMER* timer;
	ALLEGRO_DISPLAY* display;
	void drawBackground();
	void drawWorms(World* world);

};

#endif // !_DRAWWORLD_H