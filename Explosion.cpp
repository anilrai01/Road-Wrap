#include "Explosion.h"

Explosion::Explosion(float posX, float posY)
{
	if (explodeTxt.loadFromFile("images/type_B.png")) {
		cout << "Player Loaded on the screen";
	}
	else {
		cout << "Error Loading Player";
	}

	explodeSpr.setTexture(explodeTxt);

	this->posX = posX;
	this->posY = posY;
}

void Explosion::drawExplosion(RenderWindow& window)
{
	Frame += animSpeed;
	//Repeated Frame set
	//if (Frame > frameCount) Frame -= frameCount;
	explodeSpr.setTextureRect(IntRect(int(Frame) * 192, 0, 192, 192));
	explodeSpr.setPosition(Vector2f(posX, posY));

	window.draw(explodeSpr);
}
