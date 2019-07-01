#pragma once

#include "DxLib.h"

class Wall;
class Actor;

class WallSpawner
{
public:
	WallSpawner();
	~WallSpawner();
	void WallSpawn();
	bool ballWallCollision(Actor* ball);
private:
	int count;
	const int SpawnTime = 50;
	//Wallのアドレスを保存しておく
	Wall* walls[50];
	//現在StateがPausingのWallを取得
	Wall* GetPausingWall();
	//二つのレーンのどちらに設置するかをランダムで取得する
	VECTOR CreateWallPosition();
};

