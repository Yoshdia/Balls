#pragma once
#include "Wall.h"
class AddPointWall :
	public Wall
{
public:
	AddPointWall(VECTOR initPos);
	~AddPointWall();
	void OnCollision();

};

