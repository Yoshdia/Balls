#pragma once
#include "Game.h"
#include "Actor.h"
#include "DxLib.h"
#include "BoxColliderComponent.h"

class MoveComponent;
class Wall :
	public Actor
{
public:
	Wall(VECTOR initPos,BoxColliderComponent::ColliderTag tag);
	~Wall();

	void UpdateActor(float deltaTime);

	//���W���󂯎�����n�_�ɂ��A�t���O��|��
	void ResetWall(VECTOR pos);
	void ClearWall();
	void OnCollision() { state = Actor::ActiveState::Paused; };
protected:
	MoveComponent * moveComponent;
	BoxColliderComponent* boxCollider;
};

