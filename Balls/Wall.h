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

	//座標を受け取った地点にし、フラグを倒す
	void ResetWall(VECTOR pos);
	void ClearWall();
	void OnCollision() { state = Actor::ActiveState::Paused; };
protected:
	MoveComponent * moveComponent;
	BoxColliderComponent* boxCollider;
};

