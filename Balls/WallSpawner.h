#pragma once

#include "DxLib.h"

class Wall;
class AddSpeedWall;
class AddPointWall;

class WallSpawner
{
public:
	WallSpawner();
	~WallSpawner();
	//SpawnTimeごとにWallを生成する関数
	void WallSpawn();
	//すべてのwallの移動を停止させ生成もやめさせる
	void WallStop();
	//すべてのwallを初期状態に戻す
	void WallClear();
private:
	int count;
	const int SpawnTime = 60;
	int spawnTime;
	int RandamSpawnWallMax = 200;
	//Wallのアドレスを保存しておく
	Wall* walls[50];
	//AddSpeedWallへのアドレス
	AddSpeedWall* addSpeedWalls[5];
	//AddPointWall
	AddPointWall* addPointWalls[5];
	//現在StateがPausingのWallを取得
	Wall* GetPausingWall();
	//二つのレーンのどちらに設置するかをランダムで取得する
	VECTOR CreateWallPosition();

	static const VECTOR InitPos;
};

