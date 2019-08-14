#pragma once
#include <iostream>
#include <string>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
public:
	Player() {};
	Player(string imgDirectory, float posX, float posY);

	void drawPlayer(RenderWindow& window);
	void movePlayer(char direction);
	float getPosX();
	float getPosY();
	int getLife();
	void setLife(int);

private:
	Texture playerTexture;
	Sprite	playerSprite;
	float posX = 0;
	float posY = 0;
	float acc = 2.5f;
	int life = 3;
};