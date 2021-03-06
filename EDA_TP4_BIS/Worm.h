#ifndef _WORM_H
#define _WORM_H

#include "Point.h"

typedef enum { MOVE_RIGHT, MOVE_LEFT, START_MOVING_RIGHT, START_MOVING_LEFT, STOP_MOVING_RIGHT, STOP_MOVING_LEFT, IDLE, START_JUMPING, JUMPING } states_t;


typedef enum {RIGHT, LEFT} direction_t;

#define MAX_MOVEMENT_REPETITIONS 3

class Worm {
public:
	Worm() {
		bitmapIndex = 0;
		frameCounter = 0;
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
private:

	bool inRange(Point& point);
	bool onAir(Point* pos);
	int movementRepetitons;
};

#endif // _WORM_H