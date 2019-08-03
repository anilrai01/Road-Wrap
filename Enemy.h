#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
public:
	Enemy() { this->posX = 0; this->posY = 0; };
	Enemy(string imgDirectory, float posX, float posY);
	void drawEnemy(RenderWindow& window);
	void updateEnemy();

private:
	Texture enemyTxt;
	Sprite enemySpr;
	float posX;
	float posY;
	float acc = 3.5f;
};

