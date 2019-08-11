#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
public:
	Player(){};
	Player(string imgDirectory, int posX, int posY);

	void drawPlayer(RenderWindow& window);
	void movePlayer(char direction);
	float getPosX();
	float getPosY();
	void collided(char);
	void setDeg();
	int getLife();
	void setLife(int);

private:
	Texture playerTexture;
	Sprite	playerSprite;
	float posX = 0;
	float posY = 0;
	float acc = 2.5f;
	float currentDeg = 0;
	int life = 3;
};

