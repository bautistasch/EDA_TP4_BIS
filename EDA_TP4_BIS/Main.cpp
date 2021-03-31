#include <iostream>

#include "World.h"
#include "DrawWorld.h"


void dispatch(World* world, AllegroRes allegroRes);

int main()
{
	World myWorld;   // NO Sabemos como hacer en la lista de inicializacion. INICIALIZAR los objetos worm
					// podriamos asignar estos valores en el contructores de world pero no es la idea...

	myWorld.worms[0].pos.x = 1000;
	myWorld.worms[0].pos.y = 616;          
	myWorld.worms[0].direction = LEFT;        
	myWorld.worms[0].state = IDLE;

	myWorld.worms[1] = myWorld.worms[0];
	myWorld.worms[1].pos.x = 800;

	AllegroRes allegroResources;

	if (!allegroResources.initWorld())
		return 1;

	while (myWorld.isRunning)
	{
		dispatch(&myWorld, allegroResources);            
	}
	allegroResources.destroyWorld();

}

void dispatch(World* world, AllegroRes allegroRes)
{
	ALLEGRO_EVENT event;

	bool redraw = false;

	if (al_get_next_event(allegroRes.eventQueue, &event))
	{
		switch (event.type)      //Se evalua el evento ocurrido y se actua acordemente
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			world->isRunning = false;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			world->startMoving(event.keyboard.keycode);
			break;

		case ALLEGRO_EVENT_KEY_UP:
			world->stopMoving(event.keyboard.keycode);
			break;

		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		}
	}
	if (redraw && al_is_event_queue_empty(allegroRes.eventQueue))
	{
		redraw = false;
		world->refresh();
		allegroRes.drawWorld(world);
	}
}