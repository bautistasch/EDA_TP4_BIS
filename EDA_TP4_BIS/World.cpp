#include <iostream>

#include "World.h"
#include <allegro5/allegro.h>


void World::startMoving(int key)
{
	switch (key)
	{
	case ALLEGRO_KEY_LEFT:
		worms[0].startMovingLeft();
		break;

	case ALLEGRO_KEY_RIGHT:
		worms[0].startMovingRight();
		break;

	case ALLEGRO_KEY_D:
		worms[1].startMovingRight();
		break;

	case ALLEGRO_KEY_A:
		worms[1].startMovingLeft();
		break;
	case ALLEGRO_KEY_UP:
		worms[0].startJumping();
		break;
	case ALLEGRO_KEY_W:
		worms[1].startJumping();
		break;
	}
}
void World::stopMoving(int key)
{
	switch (key)
	{
	case ALLEGRO_KEY_LEFT:
		worms[0].stopMovingLeft();
		break;

	case ALLEGRO_KEY_RIGHT:
		worms[0].stopMovingRight();
		break;

	case ALLEGRO_KEY_D:
		worms[1].stopMovingRight();
		break;

	case ALLEGRO_KEY_A:
		worms[1].stopMovingLeft();
		break;
	case ALLEGRO_KEY_UP:
		worms[0].stopJumping();
		break;
	case ALLEGRO_KEY_W:
		worms[1].stopJumping();
		break;
	}
}
void World::refresh(void)
{
	worms[0].upDate();
	worms[1].upDate();
}

World::World()
{
	isRunning = true;
}