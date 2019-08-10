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

const float DeepestSpawner::squareHeight = 10;

const int DeepestSpawner::WallRandMax = 100;
const float DeepestSpawner::AddPointRand = (float)(5 * 0.01);
const float DeepestSpawner::AddSpeedRand = (float)((DeepestSpawner::AddPointRand + 5)*0.01);
const float DeepestSpawner::SpawnTime = 60;
const VECTOR DeepestSpawner::StartRunPos = VGet(1, 0, 100);

const int DeepestSpawner::CreateMovePlanCntMax = 100;
const float DeepestSpawner::MoveStage = 3.0f;
const float DeepestSpawner::AdjacentTargetX = 7.0f/ MoveStage;
const float DeepestSpawner::movingSpeed = 0.01f;

DeepestSpawner::DeepestSpawner()
{
	grainCreateAndHaver = new GrainBackGroundHaver();
	myPos = VGet(0, 0, 30);
	grainCount = 0;
	moving = false;

	spawnTime = SpawnTime;
	wallCount = 0;
	wallCreateAndHaver = new WallCreateAndHaver();
	wallCreateAndHaver->CreatePauseWalls();
	grainShade = DeepestSpawner::GrainShade::sphere;
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
	if (moving)
	{
		Move();
	}
	else
	{
		CreateMovePlan();
	}

	DrawSphere3D(myPos, 5, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
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

void DeepestSpawner::Move()
{
	if ((int)myPos.x == (int)targetPositionX)
	{
		moving = false;
		return;
	}
	myPos.x += CulculationX() * movingSpeed;
}

void DeepestSpawner::CreateMovePlan()
{
	if (createMovePlanCnt < CreateMovePlanCntMax)
	{
		createMovePlanCnt++;
	}
	else
	{
		createMovePlanCnt = 0;
		int rand = GetRand(7) - 3;
		if (rand == 2)
		{
			grainCreateAndHaver->GrainColorChange(GrainBackGround::GrainColor::Red);
		}
		if (rand == 1)
		{
			grainShade = DeepestSpawner::GrainShade::sphere;
		}
		if (rand == -1)
		{
			grainShade = DeepestSpawner::GrainShade::square;
		}
		if (rand == -2)
		{
			grainCreateAndHaver->GrainColorChange(GrainBackGround::GrainColor::white);
		}
		targetPositionX = AdjacentTargetX * rand;
		moving = true;
	}
}

float DeepestSpawner::CulculationX()
{
	bool plus = myPos.x < targetPositionX ? true : false;
	float plusPos = 1;

	if (plus)
	{
		if (myPos.x < targetPositionX)
		{
			plusPos *= 1;
		}
		else
		{
			plusPos *= 0;
		}
	}
	else
	{
		if (myPos.x > targetPositionX)
		{
			plusPos *= -1;
		}
		else
		{
			plusPos *= 0;
		}
	}
	return plusPos;
}

void DeepestSpawner::GrainSpawn(float deltaTime)
{
	grainCount++;
	if (grainCount >= SpawnGrainTime - plusSpeed)
	{
		grainCount = 0;
		SetGrain();
	}
}

void DeepestSpawner::SetGrain()
{
	VECTOR grainMiddlePos = myPos;
	grainMiddlePos.y += GrainHeight;
	switch (grainShade)
	{
	case(GrainShade::sphere):
		SphereGrain(grainMiddlePos); 
		break;
	case(GrainShade::square):	
		SquareGrain(grainMiddlePos, 1);
		SquareGrain(grainMiddlePos, -1); 
		break;
	}
}

void DeepestSpawner::SphereGrain(VECTOR grainMiddlePos)
{
	for (int num = 1; num <= 12; num++)
	{
		GrainBackGround* grain = grainCreateAndHaver->GetPauseGrain();
		float x = (float)(cos(num * 60));
		float y = (float)(sin(num * 60));
		VECTOR circleOnPos = VGet(x, y, 0)*Radius;
		VECTOR grainPos = VAdd(grainMiddlePos, circleOnPos);
		VECTOR targetPos = VGet(x, y, -20)*Radius;
		grain->ResetBackGround(grainPos, targetPos);
	}
}

void DeepestSpawner::SquareGrain(VECTOR grainMiddlePos, char plusOrMinas)
{
	for (int num = 0; num < 7; num++)
	{
		GrainBackGround* grain = grainCreateAndHaver->GetPauseGrain();
		float x = squareHeight / 2*plusOrMinas;
		float y = (-squareHeight/8)+num;
		VECTOR squareOnPos = VGet(x, y, 0);
		VECTOR grainPos = VAdd(myPos, squareOnPos);
		VECTOR targetPos = VGet(x, y, -12);
		grain->ResetBackGround(grainPos, targetPos);
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
	VECTOR targetPos;
	int rand = GetRand(1);
	wallPos = CreateWallPositionCreateSuperWall(rand);
	targetPos = wallPos;
	wallPos = VAdd(wallPos, myPos);
	targetPos.z = -12;
	CreateSuperWall(rand, 1);

	Wall* posingWall = nullptr;
	posingWall = GetRandomWall();
	posingWall->ResetWall(wallPos, targetPos);

	rand = GetRand(1);
	wallPos = CreateWallPositionCreateSuperWall(rand);
	//反転させる
	wallPos.x *= -1;
	targetPos = wallPos;
	wallPos = VAdd(wallPos, myPos);
	targetPos.z = -12;
	CreateSuperWall(rand, -1);
	posingWall = GetRandomWall();
	posingWall->ResetWall(wallPos, targetPos);
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
	VECTOR targetPos = wallPos;
	wallPos = VAdd(wallPos, myPos);
	targetPos.z = -12;

	Wall* superWall = wallCreateAndHaver->GetPausingWall(BoxColliderComponent::ColliderTag::SuperWall);
	superWall->ResetWall(wallPos, targetPos);
}
