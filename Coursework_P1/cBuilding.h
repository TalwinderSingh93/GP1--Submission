/*
=================
cBuilding.h
- Header file for class definition - SPECIFICATION
- Header file for the building class which is a child of cSprite class
=================
*/
#ifndef _cBUILDING_H
#define _cBUILDING_H
#include "cSprite.h"


class cBuilding : public cSprite
{
private:
	SDL_Point buildingVelocity;

public:
	cBuilding();
	void update(double deltaTime);		// building update method
	void setBuildingVelocity(SDL_Point buildingVel);   // Sets the velocity for the building
	SDL_Point getBuildingVelocity();				 // Gets the building velocity
};
#endif