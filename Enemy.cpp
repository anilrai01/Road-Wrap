#include "Enemy.h"

Enemy::Enemy(string imgDirectory, int posX, int posY)
{
	if (enemyTxt.loadFromFile(imgDirectory)) {
		cout << "Enemy Diployed" << endl;
	}
	else {
		cout << "Failed loading Enemy";
	}

	enemySpr.setTexture(enemyTxt);
	enemySpr.setScale(Vector2f(1.3, 1.5));
	
	this->posX = posX;
	this->posY = posY;
}

void Enemy::drawEnemy(RenderWindow& window)
{
	window.draw(enemySpr);
	enemySpr.setPosition(this->posX, this->posY);
	updateEnemy();
}

void Enemy::updateEnemy()
{
	this->posY += this->acc;
	enemySpr.setPosition(Vector2f(this->posX, this->posY));
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
	enemySpr.setScale(Vector2f(1.3, 1.5));
}
