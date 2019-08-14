#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

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

