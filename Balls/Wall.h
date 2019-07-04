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
	bool GetComeOutCameraFlag() { return comeOutCamera; };
private:
	BoxColliderComponent* boxCollider;
	//カメラの外に出たら建つフラグ。trueで待機状態に戻る
	bool comeOutCamera;
};

