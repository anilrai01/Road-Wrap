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
	playerSprite.setScale(Vector2f(0.7f, 0.7f));

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
