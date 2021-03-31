#include <iostream>

#include "DrawWorld.h"

using namespace std;

#define SCENARIO		"Scenario.png"

#define JUMP_F1_IMG		"wjump-f1.png"
#define JUMP_F2_IMG		"wjump-f2.png"
#define JUMP_F3_IMG		"wjump-f3.png"
#define JUMP_F4_IMG		"wjump-f4.png"
#define JUMP_F5_IMG		"wjump-f5.png"
#define JUMP_F6_IMG		"wjump-f6.png"
#define JUMP_F7_IMG		"wjump-f7.png"
#define JUMP_F8_IMG		"wjump-f8.png"
#define JUMP_F9_IMG		"wjump-f9.png"
#define JUMP_F10_IMG	"wjump-f10.png"


#define WALK_F1_IMG		"wwalk-f1.png"
#define WALK_F2_IMG		"wwalk-f2.png"
#define WALK_F3_IMG		"wwalk-f3.png"
#define WALK_F4_IMG		"wwalk-f4.png"
#define WALK_F5_IMG		"wwalk-f5.png"
#define WALK_F6_IMG		"wwalk-f6.png"
#define WALK_F7_IMG		"wwalk-f7.png"
#define WALK_F8_IMG		"wwalk-f8.png"
#define WALK_F9_IMG		"wwalk-f9.png"
#define WALK_F10_IMG	"wwalk-f10.png"
#define WALK_F11_IMG	"wwalk-f11.png"
#define WALK_F12_IMG	"wwalk-f12.png"
#define WALK_F13_IMG	"wwalk-f13.png"
#define WALK_F14_IMG	"wwalk-f14.png"
#define WALK_F15_IMG	"wwalk-f15.png"


bool AllegroRes::initWorld()
{

	const char* jumpImgs[] = { JUMP_F1_IMG,
								JUMP_F2_IMG,
								JUMP_F3_IMG,
								JUMP_F4_IMG,
								JUMP_F5_IMG,
								JUMP_F6_IMG,
								JUMP_F7_IMG,
								JUMP_F8_IMG,
								JUMP_F9_IMG,
								JUMP_F10_IMG
	};

	const char* walkImgs[] = { WALK_F1_IMG,
								WALK_F2_IMG,
								WALK_F3_IMG,
								WALK_F4_IMG,
								WALK_F5_IMG,
								WALK_F6_IMG,
								WALK_F7_IMG,
								WALK_F8_IMG,
								WALK_F9_IMG,
								WALK_F10_IMG,
								WALK_F11_IMG,
								WALK_F12_IMG,
								WALK_F13_IMG,
								WALK_F14_IMG,
								WALK_F15_IMG
	};

	if (!al_init()) {
		return false;
	}
	al_init_image_addon();
	al_install_keyboard();

	int error = 0;

	display = al_create_display(1920, 696);
	if (display == NULL)
	{
		error = 5;
		destroyWorld(error);
		return false;
	}

	for (int i = 0; i < 10; i++)
	{
		wormJump[i] = al_load_bitmap(jumpImgs[i]);
		if (wormJump[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				al_destroy_bitmap(wormJump[j]);
			}
			error = 1;
			destroyWorld(error);
			return false;
		}
	}
	for (int i = 0; i < 15; i++)
	{
		wormWalk[i] = al_load_bitmap(walkImgs[i]);
		if (wormWalk[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				al_destroy_bitmap(wormWalk[j]);
			}
			error = 2;
			destroyWorld(error);
			return false;
		}
	}

	eventQueue = al_create_event_queue();
	if (eventQueue == NULL)
	{
		error = 4;
		destroyWorld(error);
		return false;
	}

		backSplash = al_load_bitmap(SCENARIO);
	if (backSplash == NULL)
	{
		error = 3;
		destroyWorld(error);
		return false;
	}

	timer = al_create_timer(1.0 / FPS); 
	if (timer == NULL)
	{
		error = 6;
		destroyWorld(error);
		return false;
	}

	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	return true;
}

void AllegroRes::destroyWorld(int error)
{
	switch (error)
	{
		case 0 :
			al_destroy_timer(timer);
		case 6:
			al_destroy_display(display);
		case 5 :
			al_destroy_event_queue(eventQueue);
		case 4:
			al_destroy_bitmap(backSplash);
		case 3:
			for (int i = 0; i < 15; i++)
			{
				al_destroy_bitmap(wormWalk[i]);
			}
		case 2:
			for (int i = 0; i < 10; i++)
			{
				al_destroy_bitmap(wormJump[i]);
			}
		case 1:
			break;
	}
}


void AllegroRes::drawWorld(World * world)
{
	al_clear_to_color(al_color_name("blue"));
	drawBackground();
	drawWorms(world);
	al_flip_display();
}




void AllegroRes::drawBackground() {
	al_draw_bitmap(backSplash, 0, 0, 0);
}

void AllegroRes::drawWorms(World * world) {
	for (int i = 0; i < 2; i++)
	{
		if (world->worms[i].state != IDLE)
		{
			if (world->worms[i].state != JUMPING && world->worms[i].state != START_JUMPING)
			{
				if (world->worms[i].state == START_MOVING_LEFT || world->worms[i].state == START_MOVING_RIGHT)
				{
					al_draw_bitmap(wormWalk[0], world->worms[i].pos.x, world->worms[i].pos.y, world->worms[i].direction == RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0);

				}
				else if (world->worms[i].frameCounter > 5 )
				{
					al_draw_bitmap(wormWalk[world->worms[i].bitmapIndex - 1 ], world->worms[i].pos.x, world->worms[i].pos.y, world->worms[i].direction == RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0);

				}
			}
			else
			{
				al_draw_bitmap(wormJump[world->worms[i].bitmapIndex - 1], world->worms[i].pos.x, world->worms[i].pos.y, world->worms[i].direction == RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0);

			}
		}
		else if (world->worms[i].state == IDLE)
		{
			al_draw_bitmap(wormWalk[world->worms[i].bitmapIndex], world->worms[i].pos.x, world->worms[i].pos.y, world->worms[i].direction == RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0);

		}
	}
}

