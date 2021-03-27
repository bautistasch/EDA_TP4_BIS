#include <iostream>

#include "World.h"
#include "DrawWorld.h"


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_color.h>    // <------- PARA PROBAR EL RADIO DE BUSQUEDA



int main()
{
	World myWorld;

	myWorld.worms[0].bitmapIndex = 0;
	myWorld.worms[0].frameCounter = 0;
	myWorld.worms[0].pos.x = 1000;
	myWorld.worms[0].pos.y = 616;
	myWorld.worms[0].direction = LEFT;

	//myWorld.worms[0].pos.x = 500;
	//myWorld.worms[0].pos.y = 500;



	myWorld.worms[0].state = IDLE;
	myWorld.worms[0].direction = LEFT;

	myWorld.worms[1] = myWorld.worms[0];

	myWorld.worms[1].pos.x = 800;

	if (!initWorld())
	{
		return 1;
	}

	while (myWorld.running())
	{
	//	if ( isEvent())
	//	{
			dispatch(&myWorld);
	//	}
	}
}




