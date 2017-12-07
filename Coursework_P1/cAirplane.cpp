/*
=================
cAirplane.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cAirplane.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cAirplane::cAirplane() : cSprite()
{
	this->airplaneVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cAirplane::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0};
	direction.X = (sin((-90)*PI/180));
	direction.Y = -(cos((-90)*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->airplaneVelocity.x = this->airplaneVelocity.x + direction.X;
	this->airplaneVelocity.y = this->airplaneVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->airplaneVelocity.x * deltaTime;
	currentSpritePos.y += this->airplaneVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	//cout << "airplane position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
  Sets the velocity for the airplane
=================================================================
*/
void cAirplane::setAirplaneVelocity(SDL_Point BuildingVel)
{
	this->airplaneVelocity = BuildingVel;
}
/*
=================================================================
  Gets the airplane velocity
=================================================================
*/
SDL_Point cAirplane::getAirplaneVelocity()
{
	return this->airplaneVelocity;
}
