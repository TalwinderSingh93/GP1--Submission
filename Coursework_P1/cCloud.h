/*
=================
cCloud.h
- Header file for class definition - SPECIFICATION
- Header file for the Cloud class which is a child of cSprite class
=================
*/
#ifndef _CCLOUD_H
#define _CCLOUD_H
#include "cSprite.h"


class cCloud : public cSprite
{
private:
	SDL_Point cloudVelocity;

public:
	cCloud();
	void update(double deltaTime);		// Cloud update method
	void setCloudVelocity(SDL_Point cloudVel);   // Sets the velocity for the Cloud
	SDL_Point getCloudVelocity();				 // Gets the Cloud velocity
};
#endif