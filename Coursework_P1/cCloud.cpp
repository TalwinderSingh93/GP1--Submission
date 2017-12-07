/*
=================
cCloud.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cCloud.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cCloud::cCloud() : cSprite()
{
	this->cloudVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cCloud::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0};
	direction.X = (sin((-90)*PI/180));
	direction.Y = -(cos((-90)*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->cloudVelocity.x = this->cloudVelocity.x + direction.X;
	this->cloudVelocity.y = this->cloudVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->cloudVelocity.x * deltaTime;
	currentSpritePos.y += this->cloudVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	//cout << "Cloud position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
  Sets the velocity for the Cloud
=================================================================
*/
void cCloud::setCloudVelocity(SDL_Point CloudVel)
{
	this->cloudVelocity = CloudVel;
}
/*
=================================================================
  Gets the Cloud velocity
=================================================================
*/
SDL_Point cCloud::getCloudVelocity()
{
	return this->cloudVelocity;
}
