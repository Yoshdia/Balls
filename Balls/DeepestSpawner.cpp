#include "DxLib.h"

#include "DeepestSpawner.h"
#include "GrainBackGroundHaver.h"
#include "GrainBackGround.h"

#include "GameSpeedManager.h"
#include "WallCreateAndHaver.h"
#include "Wall.h"

#include <math.h>
#include "InputKey.h"

const float DeepestSpawner::Radius = 6;
const float DeepestSpawner::GrainHeight = 2;
const float DeepestSpawner::SpawnGrainTime = 12;

const int DeepestSpawner::WallRandMax = 100;
const float DeepestSpawner::AddPointRand = (float)(5 * 0.01);
const float DeepestSpawner::AddSpeedRand = (float)((DeepestSpawner::AddPointRand + 5)*0.01);
const float DeepestSpawner::SpawnTime = 60;
const VECTOR DeepestSpawner::StartRunPos = VGet(1, 0, 100);

DeepestSpawner::DeepestSpawner()
{
	grainCreateAndHaver = new GrainBackGroundHaver();
	myPos = VGet(0, 0, 30);
	grainCount = 0;

	spawnTime = SpawnTime;
	wallCount = 0;
	wallCreateAndHaver = new WallCreateAndHaver();
	wallCreateAndHaver->CreatePauseWalls();
}


DeepestSpawner::~DeepestSpawner()
{
	delete grainCreateAndHaver;
	delete wallCreateAndHaver;
}

void DeepestSpawner::SpawnerUpdate(float deltaTime)
{
	float gameSpeed = GameSpeedManager::GetInstance()->GetGameSpeed();
	//設置速度から減算する値
	plusSpeed = (gameSpeed - 1) * 50;
	//壁の設置速度の上限
	if (plusSpeed > 10)
	{
		plusSpeed = 10;
	}

	GrainSpawn(deltaTime);
	WallSpawn(deltaTime);
}

void DeepestSpawner::StopDeepestObject()
{
	wallCreateAndHaver->AllWallsStop();
	grainCreateAndHaver->AllGrainsStop();
}

void DeepestSpawner::ClearDeepestObject()
{
	wallCreateAndHaver->AllWallsClear();
}

void DeepestSpawner::ReStartDeepestObject()
{
	grainCreateAndHaver->AllGrainReStart();
}

void DeepestSpawner::GrainSpawn(float deltaTime)
{
	grainCount++;
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_1])
		myPos.x -= 0.01f;
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_2])
		myPos.x += 0.01f;
	if (grainCount >= SpawnGrainTime-plusSpeed)
	{
		grainCount = 0;
		SetGrain();
	}
}

void DeepestSpawner::SetGrain()
{
	VECTOR grainMiddlePos = myPos;
	grainMiddlePos.y += GrainHeight;
	for (int num = 1; num <= 12; num++)
	{
		GrainBackGround* grain = grainCreateAndHaver->GetPauseGrain();
		float x = (float)(cos(num * 60));
		float y = (float)(sin(num * 60));
		VECTOR circleOnPos = VGet(x, y, 0)*Radius;
		VECTOR grainPos = VAdd(grainMiddlePos, circleOnPos);
		grain->ResetBackGround(grainPos, circleOnPos);
	}
}

void DeepestSpawner::WallSpawn(float deltaTime)
{
	wallCount += deltaTime * 80;
	if (wallCount >= SpawnTime - plusSpeed)
	{
		SetWall();
		wallCount = 0;
	}
}

void DeepestSpawner::SetWall()
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

Wall * DeepestSpawner::GetRandomWall()
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

VECTOR DeepestSpawner::CreateWallPositionCreateSuperWall(int rand)
{
	VECTOR wallPos = StartRunPos;
	wallPos.x += (rand * 2);

	return wallPos;
}

void DeepestSpawner::CreateSuperWall(int rand, int rightOrLeft)
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
