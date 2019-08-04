#include "Enemy.h"

Enemy::Enemy(string imgDirectory, int posX, int posY, int speed)
{
	if (enemyTxt.loadFromFile(imgDirectory)) {
		cout << "Enemy Diployed" << endl;
	}
	else {
		cout << "Failed loading Enemy";
	}

	enemySpr.setTexture(enemyTxt);
	enemySpr.setScale(Vector2f(1.3f, 1.5f));
	
	this->posX = posX;
	this->posY = posY;
	this->acc = speed;
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
	if (enemyTxt.loadFromFile(imgDir)) {
		cout << "Enemy Diployed" << endl;
	}
	else {
		cout << "Failed loading Enemy";
	}
	
	enemySpr.setTexture(enemyTxt);
	enemySpr.setScale(Vector2f(1.3f, 1.5f));
}

void Enemy::setSpeed(int speed)
{
	this->acc = speed;
}
