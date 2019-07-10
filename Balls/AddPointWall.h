#pragma once
#include "Wall.h"
class AddPointWall :
	public Wall
{
public:
	AddPointWall();
	~AddPointWall();
	void OnCollision();

};

