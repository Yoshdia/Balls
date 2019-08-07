#pragma once

class GrainBackGroundHaver;
class WallCreateAndHaver;
class Wall;

//ステージの奥からwallやgrainを産み出すクラス
class DeepestSpawner
{
public:
	DeepestSpawner();
	~DeepestSpawner();

	void SpawnerUpdate(float deltaTime);

	//すべてのObjectの移動を停止させ生成もやめさせる
	void StopDeepestObject();
	//すべてのObjectを初期状態に戻す
	void ClearDeepestObject();
	//停止した後移動を再開させる
	void ReStartDeepestObject();
private:
	//このクラスの中心座標
	VECTOR myPos;
	//GameSpeesクラスから受け取ったgameSpeedから計算した加速秒数
	float plusSpeed;

	//背景のgrainクラス
	GrainBackGroundHaver* grainCreateAndHaver;
	//背景のgrainを産み出す
	void GrainSpawn(float deltaTime);
	//設置
	void SetGrain();
	//grainを産み出すインターバル
	float grainCount;

	//grainを産み出すy座標 少し高くする
	static const float GrainHeight;
	//grainを円状に産み出す際の半径
	static const float Radius;
	static const float SpawnGrainTime;

	//wallを確保しているクラス
	WallCreateAndHaver* wallCreateAndHaver;
	//SpawnTimeごとにwallを生成する関数
	void WallSpawn(float deltaTime);
	//設置する
	void SetWall();
	//wallを産み出すインターバル
	float wallCount;

	//どのwallを設置させるかを選択する関数
	Wall* GetRandomWall();
	//それぞれのWallが設置される確率
	static const int WallRandMax;
	static const float AddPointRand;
	static const float AddSpeedRand;
	//設置インターバルの初期数
	static const float SpawnTime;
	//設置インターバルの増減後の値が入る
	float spawnTime;
	static const VECTOR StartRunPos;
	//二つのレーンのどちらに設置するかをランダムで取得する
	VECTOR CreateWallPositionCreateSuperWall(int rand);
	void CreateSuperWall(int rand, int rightOrLeft);
};

