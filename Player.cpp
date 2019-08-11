#include "Player.h"

Player::Player(string imgDirectory, int posX, int posY)
{
	try
	{
		if (!playerTexture.loadFromFile(imgDirectory)) {
			throw "Error loading Plyer";
		}
	}
	catch (const char * msg)
	{
		cout << msg;
	}

	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(Vector2f(0.6f, 0.6f));
	//playerSprite.setRotation(45);

	this->posX = posX;
	this->posY = posY;
}

void Player::drawPlayer(RenderWindow& window)
{
	window.draw(playerSprite);
	playerSprite.setPosition(posX, posY);
}

void Player::movePlayer(char direction)
{
	if (direction == 'u') {
		if (playerSprite.getPosition().y >= 0 + acc) {
			posY -= acc;
		}
	}
	if (direction == 'd') {
		if (playerSprite.getPosition().y <= 900 - acc) {
			posY += acc;
		}
	}
	if (direction == 'l') {
		if (playerSprite.getPosition().x >= 705 + acc) {
			posX -= acc;
		}
	}
	if (direction == 'r') {
		if (playerSprite.getPosition().x < 1280 - acc) {
			posX += acc;
		}
	}
	playerSprite.setPosition(Vector2f(posX, posY));
}

float Player::getPosX()
{
	return this->posX;
}

float Player::getPosY()
{
	return this->posY;
}

void Player::collided(char dir)
{
	/*
	if (this->currentDeg < 35) {
		this->currentDeg += 2;
	}*/
	if (dir == 'left') {
		this->playerSprite.rotate(35);
	}
	else {
		this->playerSprite.rotate(-35);
	}
	
}

void Player::setDeg()
{
	this->currentDeg = 0;
}

int Player::getLife()
{
	return this->life;
}

void Player::setLife(int life)
{
	this->life = life;
}
