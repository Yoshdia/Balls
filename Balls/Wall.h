#pragma once
#include "Game.h"

class Wall 
{
public:
	Wall();
	~Wall();

	void Update();
	void Render();
	//座標を受け取った地点にし、フラグを倒す
	void ResetWall(float x);

	bool GetComeOutCameraFlag() { return comeOutCamera; };
private:
	float movingSpeed;
	//カメラの外に出たら建つフラグ。trueで待機状態に戻る
	bool comeOutCamera;

	VECTOR pos;
	int *model;
	int *duplicateModel;
	int *modelTexture;
};

