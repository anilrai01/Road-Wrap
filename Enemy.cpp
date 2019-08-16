#include "Enemy.h"

Enemy::Enemy(string imgDirectory, int posX, int posY, int speed)
{

	try
	{
		if (!enemyTxt.loadFromFile(imgDirectory)) {
			throw "Error loading Enemy";
		}
	}
	catch (const char* msg)
	{
		cout << msg;
	}

	enemySpr.setTexture(enemyTxt);
	//enemySpr.setRotation(180);
	enemySpr.setScale(Vector2f(0.8f, 0.8f));

	this->posX = posX;
	this->posY = posY;
	this->acc = 2;
}

void Enemy::drawEnemy(RenderWindow& window)
{
	window.draw(enemySpr);
	enemySpr.setPosition((float)this->posX, (float)this->posY);
	updateEnemy();
}

void Enemy::updateEnemy()
{
	this->posY += this->acc;
	enemySpr.setPosition(Vector2f((float)this->posX, (float)this->posY));
}

int Enemy::getPosX()
{
	return this->posX;
}

int Enemy::getPosY()
{
	return this->posY;
}

void Enemy::setPosY(int posY)
{
	this->posY = posY;
}

void Enemy::setNewTexture(string imgDir)
{
	try
	{
		if (!enemyTxt.loadFromFile(imgDir)) {
			throw "Error repeating enemy Files";
		}
	}
	catch (const char* msg)
	{
		cout << msg;
	}

	enemySpr.setTexture(enemyTxt);
	//enemySpr.setRotation(180);
	//enemySpr.setScale(Vector2f(0.6f, 0.6f));
}

void Enemy::setSpeed(int speed)
{
	this->acc = speed;
}