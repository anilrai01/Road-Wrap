#include "Explosion.h"

bool Explosion::isEnd()
{
	return Frame + speed >= frames.size();
}
