#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Enemy
{
public:
	Enemy() { this->posX = 0; this->posY = 0; this->acc = 0; };
	Enemy(string imgDirectory, int posX, int posY, int speed);
	void drawEnemy(RenderWindow& window);
	void updateEnemy();
	int getPosX();
	int getPosY();
	void setPosY(int);
	void setNewTexture(string);
	void setSpeed(int);

protected:
	Texture enemyTxt;
	Sprite enemySpr;
	int posX;
	int posY;
	int acc;
};