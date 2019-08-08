#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "BoxColliderComponent.h"

class HeadForTargetComponent;
class Wall :
	public Actor
{
public:
	Wall(BoxColliderComponent::ColliderTag tag,const std::string& modelFileName);
	~Wall();

	void UpdateActor(float deltaTime);

	//座標をセット、stateをActiveにして走らせる
	void ResetWall(VECTOR pos,VECTOR target);
	//座標を画面外にセットし、stateをPauseにして待機状態にさせる
	void ClearWall();

	void StopMove() ;
	void OnCollision();
	const VECTOR InitPos = VGet(-10, -10, -10);
protected:
	HeadForTargetComponent * headForTarget;
	BoxColliderComponent* boxCollider;
	const VECTOR moveSpeed = VGet(0, 0, -60.0f);
};

