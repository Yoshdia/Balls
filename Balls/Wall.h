#pragma once
#include "Game.h"
#include "Actor.h"
#include "DxLib.h"

class BoxColliderComponent;

class Wall :
	public Actor
{
public:
	Wall(VECTOR initPos);
	~Wall();

	void UpdateActor(float deltaTime);

	//座標を受け取った地点にし、フラグを倒す
	void ResetWall(VECTOR pos);
	void ClearWall();
private:
	BoxColliderComponent* boxCollider;
};

