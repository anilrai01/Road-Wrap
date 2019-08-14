#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Animation.h"
class Bullet : public Animation
{
	using Animation::Animation;

private:
	int life = 1;
	float acc = 2.5f;

public:
	void updateBullet();
	int getPosY();
	int getPosX();
};