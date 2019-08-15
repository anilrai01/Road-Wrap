#include "Obstacle.h"

Obstacle::Obstacle(Texture& imgTexture, int posX, int posY)
{
	obsSpr.setTexture(imgTexture);
	//obsSpr.setScale(Vector2f(0.3f, 0.5f));

	this->posX = posX;
	this->posY = posY;
}

void Obstacle::moveObs()
{
	this->posY += this->acc;
	this->obsSpr.setPosition(Vector2f(this->posX, this->posY));
}

void Obstacle::setPosY(float y)
{
	this->posY = y;
}

void Obstacle::drawObs(RenderWindow& window)
{
	window.draw(this->obsSpr);
	moveObs();
}

float Obstacle::getPosX()
{
	return this->posX;
}

float Obstacle::getPosY()
{
	return this->posY;
}
