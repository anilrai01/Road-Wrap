#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include<vector>
#include "Animation.h"

class Explosion : public Animation
{
	using Animation::Animation;
public:
	/*
	float Frame, speed;
	Sprite sprite;
	vector <IntRect> frames;

	Explosion(Texture &, int, int, int, int, int, float);
	*/

	bool isEnd();
};

