#pragma once

#include "Animation.h"
class Coin :
	public Animation
{
	using Animation::Animation;

private:
	int life = 1;
	float acc = 2.5f;

public:
	void updateCoin();
	int getPosY();
	int getPosX();
	void setNewPos(int, int);
};

