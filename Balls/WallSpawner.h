#pragma once

#include "DxLib.h"

class Wall;
class AddSpeedWall;
class AddPointWall;
class SuperWall;

class WallSpawner
{
public:
	WallSpawner();
	~WallSpawner();
	//SpawnTimeごとにWallを生成する関数
	void WallSpawn(float deltaTime);
	//すべてのwallの移動を停止させ生成もやめさせる
	void WallStop();

	//すべてのwallを初期状態に戻す
	void WallClear();
private:
	float count=0;
	const float SpawnTime = 60;
	float spawnTime;
	int RandamSpawnWallMax = 200;
	const VECTOR StartRunPos = VGet(1, 0, 100);

	//Wallのアドレスを保存しておく
	Wall* walls[50];
	//特殊なWallへのアドレス
	AddSpeedWall* addSpeedWalls[5];
	AddPointWall* addPointWalls[5];
	SuperWall* superWalls[5];
	//現在StateがPausingのWallを取得
	Wall* GetPausingWall();
	//二つのレーンのどちらに設置するかをランダムで取得する
	VECTOR CreateWallPositionCreateSuperWall(int rand);
	void CreateSuperWall(int rand, int rightOrLeft);

};

