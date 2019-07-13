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
	Wall(BoxColliderComponent::ColliderTag tag,const std::string& modelFileName);
	~Wall();

	void UpdateActor(float deltaTime);

	//座標をセット、stateをActiveにして走らせる
	void ResetWall(VECTOR pos);
	//座標を画面外にセットし、stateをPauseにして待機状態にさせる
	void ClearWall();

	void StopMove() ;
	void OnCollision();
	const VECTOR InitPos = VGet(-10, -10, -10);
protected:
	MoveComponent * moveComponent;
	BoxColliderComponent* boxCollider;
	const VECTOR moveSpeed = VGet(0, 0, -60.0f);
};

