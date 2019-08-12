#include "Explosion.h"

void Explosion::update()
{
	Frame += speed;
	int n = frames.size();
	if (Frame >= n) Frame -= n;
	if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
}

Explosion::Explosion(Texture& t, int x, int y, int w, int h, int count, float Speed)
{
	Frame = 0;
	speed = Speed;

	for (int i = 0; i < count; i++) {
		frames.push_back(IntRect(i * w, 0, w, h));
	}

	sprite.setTexture(t);
	//sprite.setOrigin(w / 2, h / 2);
	sprite.setScale(Vector2f(1.5f, 1.5f));
	sprite.setPosition(x, y);
	sprite.setTextureRect(frames[0]);
}

bool Explosion::isEnd()
{
	return Frame + speed >= frames.size();
}
