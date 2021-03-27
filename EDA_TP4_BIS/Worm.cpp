#include "Worm.h"
#include <iostream>

#include "DrawWorld.h"   //  <------ por inRange()
#include <cmath>

#define PI 3.14159265
bool onAir(Point* pos);
void Worm::startMovingLeft(void) // tecla d presionada
{
	if (this->state == IDLE ) //arranco a apretar la flecha
	{
		this->frameCounter = 0;
		bitmapIndex = 0;
		this->state = START_MOVING_LEFT;
		this->direction = LEFT;
	}
	else if (this->state == STOP_MOVING_LEFT) //termino el movimiento pero siguen apretando la flecha
	{
		this->state == MOVE_LEFT;
	}
}

void Worm::stopMovingLeft(void) // solte la tecla d
{
	if (this->state == MOVE_LEFT)
	{
		this->state = STOP_MOVING_LEFT;
	}
	else if (this->state == START_MOVING_LEFT)
	{
		this->state = IDLE;
	}
}

void Worm::startMovingRight(void) // tecla a presionada
{
	if (this->state == IDLE ) //arranco a apretar la flecha
	{
		this->frameCounter = 0;
		bitmapIndex = 0;
		this->state = START_MOVING_RIGHT;
		this->direction = RIGHT;
	}
	else if (this->state == STOP_MOVING_RIGHT) //termino el movimiento pero siguen apretando la flecha
	{
		this->state == MOVE_RIGHT;
	}
}

void Worm::stopMovingRight() // solte la tecla a
{
	if (this->state == MOVE_RIGHT)
	{
		this->state = STOP_MOVING_RIGHT;
	}
	else if (this->state == START_MOVING_RIGHT)
	{
		this->state = IDLE;
	}
}

void Worm::startJumping()
{
	if (this->state == IDLE)
	{
		frameCounter = 0;
		bitmapIndex = 0;
		this->state = START_JUMPING;
	}
}

void Worm::stopJumping()
{
	if (this->state == START_JUMPING)
	{
		this->state = IDLE;
	}
}


void Worm::upDate()
{
	switch (this->state)
	{
		case START_MOVING_LEFT: case START_MOVING_RIGHT:
			if (frameCounter < 5)
				frameCounter++;
			else
			{
				this->state = this->state == START_MOVING_LEFT ? MOVE_LEFT : MOVE_RIGHT;
				frameCounter++;
				bitmapIndex = frameCounter - 5;
			}
		break;

		case MOVE_LEFT: case STOP_MOVING_LEFT: case MOVE_RIGHT: case STOP_MOVING_RIGHT:
			if (frameCounter < 8) 
			{
				frameCounter++;
				bitmapIndex = frameCounter - 5;
			}
			else if (frameCounter >= 8 && frameCounter < 16 )
			{
				frameCounter++;
				bitmapIndex = frameCounter - 5 ;
			}
			else if (frameCounter >= 16  && frameCounter < 21 )
			{
				frameCounter++;
				bitmapIndex = frameCounter - 6;
			}
			else              //llegue al F14 de la repeticion
			{    
				bitmapIndex = 4;
				frameCounter++;
				if (this->state == MOVE_LEFT || this->state == STOP_MOVING_LEFT)
				{
					pos.x -= 9;
					if(!inRange(pos))//Si esta fuera de ranfo lo dejo como estaba 
					{
						pos.x += 9;
					}
				}
				else if (this->state == MOVE_RIGHT || this->state == STOP_MOVING_RIGHT)
				{
					pos.x += 9;
					if (!inRange(pos))//Si esta fuera de ranfo lo dejo como estaba 
					{
						pos.x -= 9;
					}
				}

				movementRepetitons++;

				if (movementRepetitons == MAX_MOVEMENT_REPETITIONS)
				{	//termine todo el movimiento (hasta la rep 3) esto lo tiene que terminar si o si
					movementRepetitons = 0;
					frameCounter = 0;
					if (this->state == STOP_MOVING_LEFT || this->state == STOP_MOVING_RIGHT)
					{
						this->state = IDLE;
					}
					else if (this->state == MOVE_LEFT || this->state == MOVE_RIGHT)
					{
						this->state = this->state == MOVE_LEFT ? START_MOVING_LEFT : START_MOVING_RIGHT;
						frameCounter = 0;
					}
				}
				else
				{
					frameCounter = 8;   // 8 o 9?
				}
			}				
		break;

		case START_JUMPING:
			if (frameCounter < 4)
			{
				frameCounter++;
				bitmapIndex++;
			}
			else
			{
				this->state = JUMPING;
				frameCounter++;
				bitmapIndex++;
			}
		break;

		case JUMPING:
			if(frameCounter == 5 || onAir(&this->pos) ) 
			{
				int jumpTime = frameCounter - 4;
				if (direction == RIGHT)
				{
					this->pos.x += 4.5 * cos(60 * PI / 180.0);//Ecuacion de salto
					this->pos.y -= (4.5 * sin(60 * PI / 180.0)*jumpTime - 0.24 * jumpTime * jumpTime  );
					if (this->pos.y > 616)
					{
						this->pos.y = 616;
					}
					if (!inRange(pos))
					{
						this->pos.x -= 4.5 * cos(60 * PI / 180.0);
					}
				}        
				else if(direction == LEFT)
				{
					this->pos.x -= 4.5 * cos(60 * PI / 180.0);//Ecuacion de salto
					this->pos.y -= (4.5 * sin(60 * PI / 180.0)*jumpTime - 0.24 * jumpTime * jumpTime );
					if (this->pos.y > 616)
					{
						this->pos.y = 616;
					}
					if (!inRange(pos))
					{
						this->pos.x += 4.5 * cos(60 * PI / 180.0);
					}
				}
				frameCounter++;
			}
			else //Si ya dejo de saltar
			{
				bitmapIndex++; //Llega en 5 lo paso a 6, 7...
				if(bitmapIndex > 10 || (bitmapIndex == 2) )//Si ya pase por los dibujos 6 - 7 - 8 - 9 - 10 - 1
				{
					if (bitmapIndex == 2)
					{
						this->state = IDLE;
						frameCounter = 0; //Lo dejamos en 10 
					}
					bitmapIndex = 1;
				}
			}
		break;
	}
}


bool onAir(Point* pos)
{
	if (pos->y < 616)
	{
		return true;
	}
	return false;
}
//
//void Worm::uptdate(void) {
//	static int rep = 0;
//	switch (state)
//	{
//		case START_MOVING_LEFT:
//			if (frameCounter < 5)
//				frameCounter++;
//			else
//				this->state = MOVE_LEFT;
//			break;
//
//		//case START_MOVING_RIGHT:
//		//	if (frameCounter < 5)
//		//		frameCounter++;
//		//	else
//		//		this->state = MOVE_RIGHT;
//		//	break;
//
//		case MOVE_LEFT:
//		//case MOVE_RIGHT:
//			if (frameCounter < 8) {
//				bitmapIndex = frameCounter - 4;
//				frameCounter++;
//			}
//			else if (frameCounter < (16 + FRAMES_PER_REP * rep)) {
//				bitmapIndex = frameCounter - 4 - FRAMES_PER_REP * rep;
//				frameCounter++;
//			}
//			else if (frameCounter == (16 + FRAMES_PER_REP * rep)) {
//				bitmapIndex = 11;
//				frameCounter++;
//			}
//			else if (frameCounter < (21 + FRAMES_PER_REP * rep)) {
//				bitmapIndex = frameCounter - 6 - FRAMES_PER_REP * rep;
//				frameCounter++;
//			}
//			else {							//llegue al F14 de la repeticion
//				if (rep < 2){
//					(state == MOVE_LEFT) ? pos.x-=9 : pos.x+=9;
//					//mover 9 pixeles pos.x+=9 ; --> FIJARME SI ES MOVE RIGHT O LEFT
//					bitmapIndex = 4;
//					frameCounter++;
//					rep++;
//				}
//				else{						//termine todo el movimiento (hasta la rep 3) esto lo tiene que terminar si o si
//					rep = 0;
//					frameCounter = 0;
//					(state == MOVE_LEFT) ? (this->state = STOP_MOVING_LEFT) : (this->state = STOP_MOVING_RIGHT);
//				}
//			}
//			break;
//	}
//
//}

//acordarme inicializar frame counter constructor
// si estaba en start_moving_left y dejo de tocar incializar frame counter denuevo


/*																		frameCounter
5 frames no hago nada													0 1 2 3 4
3 frames --> 1 2 3														5 6 7

14 frames --> 4 5 6 7 8 9 10 11 11 12 13 14 15 (desplazada 9 pixeles)4  8 9 10 11 12 13 14 15 16 17 18 19 20 21
(15=4)

4 5 6 7 8 9 10 11 11 12 13 14 15 (desplazada 9 pixeles)4				22 23 24 25 26 27 28 29 30 31 32 33 34 35

4 5 6 7 8 9 10 11 11 12 13 14 15 (desplazada 9 pixeles)4				36 37 38 39 40 41 42 43 44 45 46 47 48 49

en total desplazo 27 pixeles
*/