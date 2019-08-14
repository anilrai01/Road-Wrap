#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include<vector>

class Animation
{
public:
	float Frame, speed;
	Sprite sprite;
	vector <IntRect> frames;

	Animation() { Frame = 0; speed = 0; };
	Animation(Texture&, int, int, int, int, int, float);

	void update();
};

