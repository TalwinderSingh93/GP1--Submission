/*
=================
cHelicopter.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cHelicopter.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cHelicopter::cHelicopter() : cSprite()
{
	this->helicopterVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cHelicopter::update(double deltaTime)
{
	

	FPoint direction = { 0.0f, 0.0f };
	direction.X = (sin(this->getSpriteRotAngle()*PI / 180));
	direction.Y = -(cos(this->getSpriteRotAngle()*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->helicopterVelocity.x = this->helicopterVelocity.x + direction.X;
	this->helicopterVelocity.y = this->helicopterVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->helicopterVelocity.x * deltaTime;
	currentSpritePos.y += this->helicopterVelocity.y * deltaTime;

	this->helicopterVelocity.x *= 0.95;
	this->helicopterVelocity.y *= 0.95;

	this->setSpritePos({ currentSpritePos.x , currentSpritePos.y });
	this->setBoundingRect(this->getSpritePos());
	
}
/*
=================================================================
Sets the velocity for the helicopter
=================================================================
*/
void cHelicopter::setHelicopterVelocity(SDL_Point helicopterVel)
{
	helicopterVelocity = helicopterVel;
}
/*
=================================================================
Gets the helicopter velocity
=================================================================
*/
SDL_Point cHelicopter::getHelicopterVelocity()
{
	return helicopterVelocity;
}


