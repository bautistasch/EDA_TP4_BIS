#ifndef _WORM_H
#define _WORM_H

#include "Point.h"

typedef enum { MOVE_RIGHT, MOVE_LEFT, START_MOVING_RIGHT, START_MOVING_LEFT, STOP_MOVING_RIGHT, STOP_MOVING_LEFT, IDLE, START_JUMPING, JUMPING } states_t;


typedef enum {RIGHT, LEFT} direction_t;

#define MAX_MOVEMENT_REPETITIONS 3

class Worm {
public:

	Worm()
	{
		movementRepetitons = 0;
	}
	int bitmapIndex;
	states_t state;
	unsigned int frameCounter;
	direction_t direction;
	Point pos;

	void startMovingRight(void);
	void startMovingLeft(void);
	void stopMovingRight(void);
	void stopMovingLeft(void);
	void startJumping(void);
	void stopJumping(void);
	void upDate(void);
	void setInitPos(void);
	float get_X_InitPos(void);
	float get_Y_initPos(void);
private:
	int movementRepetitons;
	Point initialPos;
};

#endif // _WORM_H