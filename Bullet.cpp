#include "Bullet.h"

void Bullet::updateBullet()
{
	this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - acc);
}

int Bullet::getPosY()
{
	return this->sprite.getPosition().y;
}
