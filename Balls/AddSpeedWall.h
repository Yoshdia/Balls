#pragma once
#include "Wall.h"
//プレイヤーと接触するとMoveComponent内にある静的メンバのgameSpeedを加算する壁
class AddSpeedWall :
	public Wall
{
public:
	AddSpeedWall(VECTOR initPos);
	~AddSpeedWall();
	void OnCollision();
};

