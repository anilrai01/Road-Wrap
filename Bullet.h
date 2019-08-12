#pragma once
#include "Explosion.h"
class Bullet : public Explosion
{
	using Explosion::Explosion;

private:
	int life = 1;
	float acc = 2.5f;

public:
	void updateBullet();
	int getPosY();
	int getPosX();
};

