#pragma once
#include "Explosion.h"
class Bullet : public Explosion
{
	using Explosion::Explosion;

public:
	void updateBullet();
	int getPosY();
private:
	int life = 1;
	float acc = 2.5f;
};

