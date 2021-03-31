#include "Worm.h"
#include <iostream>

#include "DrawWorld.h"   //  <------ por inRange()
#include <cmath>

#define PI 3.14159265
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
					this->pos.y -= (4.5 * sin(60 * PI / 180.0) - 0.12 * jumpTime * jumpTime  );
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
					this->pos.y -= (4.5 * sin(60 * PI / 180.0) - 0.12 * jumpTime * jumpTime );
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

bool Worm::onAir(Point* pos)
{
	if (pos->y < 616)
	{
		return true;
	}
	return false;
}

bool Worm::inRange(Point& point)   
{
	if ((point.x > 680) && (point.x < 1175))   
		return true;
	else
		return false;

}
