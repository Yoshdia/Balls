#pragma once

#include"Wall.h"

class AddSpeedWall :
	public Wall
{
public:
	AddSpeedWall(VECTOR initPos);
	~AddSpeedWall();
	void OnCollision();
};