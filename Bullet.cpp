#include "Bullet.h"

void Bullet::updateBullet()
{
	this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - acc);
}

int Bullet::getPosY()
{
	return (int)this->sprite.getPosition().y;
}

int Bullet::getPosX()
{
	return (int)this->sprite.getPosition().x;
}
