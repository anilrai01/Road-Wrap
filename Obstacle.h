#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Obstacle 
{
private:
	Sprite obsSpr;
	float acc = 2.0f;
	float posX;
	float posY;

public:
	Obstacle() { this->posX = 0; this->posY = 0; this->acc = 0; };
	Obstacle(Texture& imgTexture, int posX, int posY);
	void moveObs();
	void setPosY(float);
	void drawObs(RenderWindow &window);
	float getPosX();
	float getPosY();
};