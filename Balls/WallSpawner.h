#pragma once

#include "DxLib.h"
class WallCreateAndHaver;
class Wall;

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
	//Wallを確保しているクラス
	WallCreateAndHaver* wallCreateAndHaver;
	//壁を設置する
	void WallsSpawn();
	//どの壁を設置させるかを選択する関数
	Wall* GetRandomWall();
	//それぞれのWallが設置される確率
	static const int WallRandMax;
	static const float AddPointRand;
	static const float AddSpeedRand;
	//設置のタイミングを生成するカウント
	float count;
	//設置インターバルの初期数
	static const float SpawnTime;
	//設置インターバルの増減後の値が入る
	float spawnTime;
	//
	//int RandamSpawnWallMax = 200;
	const VECTOR StartRunPos = VGet(1, 0, 100);

	//二つのレーンのどちらに設置するかをランダムで取得する
	VECTOR CreateWallPositionCreateSuperWall(int rand);
	void CreateSuperWall(int rand, int rightOrLeft);
};

