#pragma once
#include "Obstacle.h"
class PowerUP :
	public Obstacle
{
	using Obstacle::Obstacle;

public:
	PowerUP() { };
	void setScale();
};

