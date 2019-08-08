#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include<vector>

class Explosion
{
public:
	float Frame, speed;
	Sprite sprite;
	vector <IntRect> frames;

	Explosion() { Frame = 0; speed = 0; };
	Explosion(Texture &, int, int, int, int, int, float);

	void update();
};

