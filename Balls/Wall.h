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

	//���W���󂯎�����n�_�ɂ��A�t���O��|��
	void ResetWall(VECTOR pos);
	void ClearWall();
private:
	BoxColliderComponent* boxCollider;
};

