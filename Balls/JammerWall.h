#pragma once
#include "Wall.h"
class JammerWall :
	public Wall
{
public:
	JammerWall();
	~JammerWall();
	void OnCollision();
};

