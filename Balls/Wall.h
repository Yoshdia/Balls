#pragma once
#include "Game.h"
#include "Actor.h"

class Wall :
	public Actor
{
public:
	Wall();
	~Wall();

	void UpdateActor(float deltaTime);

	//座標を受け取った地点にし、フラグを倒す
	void ResetWall(float x);
	bool GetComeOutCameraFlag() { return comeOutCamera; };
private:
	//カメラの外に出たら建つフラグ。trueで待機状態に戻る
	bool comeOutCamera;
};

