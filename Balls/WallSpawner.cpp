#include "DxLib.h"
#include "WallSpawner.h"
#include "GameSpeedManager.h"
#include "WallCreateAndHaver.h"
#include "Wall.h"

const int WallSpawner::WallRandMax = 100;
const float WallSpawner::AddPointRand = (float)(5*0.01);
const float WallSpawner::AddSpeedRand = (float)((WallSpawner::AddPointRand + 5)*0.01);
const float WallSpawner::SpawnTime = 60;

WallSpawner::WallSpawner()
{
	spawnTime = SpawnTime;
	count = 0;

	wallCreateAndHaver = new WallCreateAndHaver();
	wallCreateAndHaver->CreatePauseWalls();
}

WallSpawner::~WallSpawner()
{
	delete wallCreateAndHaver;
}

void WallSpawner::WallSpawn(float deltaTime)
{
	float gameSpeed = GameSpeedManager::GetInstance()->GetGameSpeed();
	//設置速度から減算する値
	float plusSpeed = (gameSpeed - 1) * 50;
	//壁の設置速度の上限
	if (plusSpeed > 10)
	{
		plusSpeed = 10;
	}
	count += deltaTime * 80;
	if (count >= spawnTime - plusSpeed)
	{
		WallsSpawn();
		count = 0;
	}
}

void WallSpawner::WallsSpawn()
{
	VECTOR wallPos;
	int rand = GetRand(1);
	wallPos = CreateWallPositionCreateSuperWall(rand);
	CreateSuperWall(rand, 1);

	Wall* posingWall = nullptr;
	posingWall = GetRandomWall();
	posingWall->ResetWall(wallPos);

	rand = GetRand(1);
	wallPos = CreateWallPositionCreateSuperWall(rand);
	CreateSuperWall(rand, -1);
	//反転させる
	wallPos.x *= -1;
	posingWall = GetRandomWall();
	posingWall->ResetWall(wallPos);
}

Wall * WallSpawner::GetRandomWall()
{
	//100までの乱数を取得
	int rand = GetRand(WallRandMax);
	//一定の確立でAddPointWall、AddSpeedWall生成しそれ以外はJammerWallを生成する
	if (rand < WallRandMax*AddPointRand)
	{
		return wallCreateAndHaver->GetPausingWall(BoxColliderComponent::ColliderTag::AddPointWall);
	}
	else if (rand < WallRandMax*AddSpeedRand)
	{
		return wallCreateAndHaver->GetPausingWall(BoxColliderComponent::ColliderTag::AddSpeedWall);
	}
	return wallCreateAndHaver->GetPausingWall(BoxColliderComponent::ColliderTag::JammerWall);
}

void WallSpawner::WallStop()
{
	wallCreateAndHaver->AllWallsStop();
}

void WallSpawner::WallClear()
{
	wallCreateAndHaver->AllWallsClear();
}

VECTOR WallSpawner::CreateWallPositionCreateSuperWall(int rand)
{
	VECTOR wallPos = StartRunPos;
	wallPos.x += (rand * 2);

	return wallPos;
}

void WallSpawner::CreateSuperWall(int rand, int rightOrLeft)
{
	int random = GetRand(50);
	if (random > 10)
	{
		return;
	}
	VECTOR wallPos = StartRunPos;
	wallPos.x *= rightOrLeft;
	if (rand == 0)
	{
		wallPos.x += 2 * rightOrLeft;
	}

	Wall* superWall = wallCreateAndHaver->GetPausingWall(BoxColliderComponent::ColliderTag::SuperWall);
	superWall->ResetWall(wallPos);
}
