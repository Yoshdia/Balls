#pragma once

class Wall;
#include"BoxColliderComponent.h"

class WallCreateAndHaver
{
public:
	WallCreateAndHaver();
	~WallCreateAndHaver();
	//全WallのStateをPauseにして生成する
	void CreatePauseWalls();
	//現在StateがPausingのWallを取得
	Wall* GetPausingWall(const BoxColliderComponent::ColliderTag& tag);
	//すべてのWallを停止させる
	void AllWallsStop();
	//すべてのWallを初期のPause状態に戻す
	void AllWallsClear();
private:
	//Wallそれぞれのアドレスを保存しておく配列
	Wall* jammerWalls[50];
	//Wallそれぞれの要素数
	static const int JammerNum;
	Wall* addSpeedWalls[5];
	static const int AddSpeedNum;
	Wall* addPointWalls[5];
	static const int AddPointNum;
	Wall* superWalls[5];
	static const int SuperNum;
};

