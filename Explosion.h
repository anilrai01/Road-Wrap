#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Explosion
{
public:
	Explosion() { this->posX = 0; this->posY = 0; };
	Explosion(float posX, float posY);

	void drawExplosion(RenderWindow& window);

private:
	Texture explodeTxt;
	Sprite explodeSpr;
	float posX;
	float posY;
	float Frame = 0;
	float animSpeed = 0.5;
	int frameCount = 192;
};

