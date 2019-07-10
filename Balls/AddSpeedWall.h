#pragma once

#include"Wall.h"

class AddSpeedWall :
	public Wall
{
public:
	AddSpeedWall();
	~AddSpeedWall();
	void OnCollision();
};