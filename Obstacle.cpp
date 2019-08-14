#include "Obstacle.h"

Obstacle::Obstacle(Texture imgTexture, int posX, int posY, int speed)
{
	obsSpr.setTexture(imgTexture);
	obsSpr.setScale(Vector2f(0.3f, 0.5f));

	this->posX = posX;
	this->posY = posY;
	this->acc = speed;
}

void Obstacle::moveObs()
{
	this->posY += acc;
	this->obsSpr.setPosition(Vector2f(this->posX, this->posY));
}

void Obstacle::updateObs(float x, float y)
{
	this->obsSpr.setPosition(Vector2f(x, y));
}

void Obstacle::drawObs(RenderWindow& window)
{
	window.draw(this->obsSpr);
	moveObs();
}
