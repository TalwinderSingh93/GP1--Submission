/*
=================
cAirplane.h
- Header file for class definition - SPECIFICATION
- Header file for the airplane class which is a child of cSprite class
=================
*/
#ifndef _cAIRPLANE_H
#define _cAIRPLANE_H
#include "cSprite.h"


class cAirplane : public cSprite
{
private:
	SDL_Point airplaneVelocity;

public:
	cAirplane();
	void update(double deltaTime);		// airplane update method
	void setAirplaneVelocity(SDL_Point airplaneVel);   // Sets the velocity for the airplane
	SDL_Point getAirplaneVelocity();				 // Gets the airplane velocity
};
#endif