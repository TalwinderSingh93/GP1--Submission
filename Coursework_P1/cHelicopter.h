/*
=================
cHelicopter.h
- Header file for class definition - SPECIFICATION
- Header file for the Helicopter class which is a child of cSprite class
=================
*/
#ifndef _CHELICOPTER_H
#define _CHELICOPTER_H
#include "cSprite.h"

class cHelicopter : public cSprite
{
private:
	SDL_Point helicopterVelocity;

public:
	cHelicopter();
	void update(double deltaTime);		// Helicopter update method
	void setHelicopterVelocity(SDL_Point helicopterVel);   // Sets the velocity for the Helicopter
	SDL_Point getHelicopterVelocity();				 // Gets the Helicopter velocity
};
#endif