#include "Coin.h"

void Coin::updateCoin()
{
	this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y + acc);
}

int Coin::getPosY()
{
	return this->sprite.getPosition().y;
}

int Coin::getPosX()
{
	return this->sprite.getPosition().x;
}

void Coin::setNewPos(int posX, int posY)
{
	this->sprite.setPosition(Vector2f(posX, posY));
}
