/*
=================
cBuilding.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBuilding.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cBuilding::cBuilding() : cSprite()
{
	this->buildingVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cBuilding::update(double deltaTime)
{

	FPoint direction = { 0.0, 0.0};
	direction.X = (sin((-90)*PI/180));
	direction.Y = -(cos((-90)*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->buildingVelocity.x = this->buildingVelocity.x + direction.X;
	this->buildingVelocity.y = this->buildingVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->buildingVelocity.x * deltaTime;
	currentSpritePos.y += this->buildingVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });

	//cout << "building position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;

	this->setBoundingRect(this->getSpritePos());

}
/*
=================================================================
  Sets the velocity for the building
=================================================================
*/
void cBuilding::setBuildingVelocity(SDL_Point BuildingVel)
{
	this->buildingVelocity = BuildingVel;
}
/*
=================================================================
  Gets the building velocity
=================================================================
*/
SDL_Point cBuilding::getBuildingVelocity()
{
	return this->buildingVelocity;
}
