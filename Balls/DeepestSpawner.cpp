#include "DxLib.h"

#include "DeepestSpawner.h"
#include "GrainBackGroundHaver.h"

#include "GameSpeedManager.h"
#include "WallCreateAndHaver.h"
#include "Wall.h"

#include <math.h>
#include "InputKey.h"
#include "CountDownComponent.h"
#include "HeadForTargetComponent.h"

const float DeepestSpawner::Radius = 8;
const float DeepestSpawner::GrainHeight = 2;
const float DeepestSpawner::SpawnGroundTime = 24;
const float DeepestSpawner::SpawnBoxTime = 15;

const float DeepestSpawner::SpawnRandomMaxCount = 100;

const float DeepestSpawner::squareHeight = 10;

const int DeepestSpawner::WallRandMax = 100;
const float DeepestSpawner::AddPointRand = (float)(5 * 0.01);
const float DeepestSpawner::AddSpeedRand = (float)((DeepestSpawner::AddPointRand + 5)*0.01);
const float DeepestSpawner::SpawnTime = 60;
const VECTOR DeepestSpawner::StartRunPos = VGet(1, 0, 10);

const int DeepestSpawner::CreateMovePlanCntMax = 600;
const float DeepestSpawner::MoveStage = 3.0f;
const VECTOR DeepestSpawner::AdjacentTarget = VGet((12/* / MoveStage*/), 0, 0);
const VECTOR DeepestSpawner::MovingSpeed = VGet(1, 1, 0.0f);

const int DeepestSpawner::GroundGrainHeight = 4;

DeepestSpawner::DeepestSpawner()
{
	grainCreateAndHaver = new GrainBackGroundHaver();
	position = VGet(0, 0, 100);

	spawnTime = SpawnTime;
	wallCount = 0;
	wallCreateAndHaver = new WallCreateAndHaver();
	wallCreateAndHaver->CreatePauseWalls();
	grainShade = DeepestSpawner::GrainShade::square;

	countDownComponent = new CountDownComponent(CreateMovePlanCntMax);
	countDownComponent->ResetCount();
	groundSpawnCountDown = new CountDownComponent(SpawnGroundTime);
	groundSpawnCountDown->ResetCount();
	boxSpawnCountDown = new CountDownComponent(SpawnBoxTime);
	boxSpawnCountDown->ResetCount();
	randomSpawnCountDown = new CountDownComponent(GetRand((int)SpawnRandomMaxCount));
	randomSpawnCountDown->ResetCount();
	headForTargetComponent = new HeadForTargetComponent(this, 120, MovingSpeed, VGet(0, 0, 0));
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

	CreateMovePlan();
	headForTargetComponent->HeadForTarget(deltaTime);
}

void DeepestSpawner::UpdateActor(float deltaTime)
{
	DrawSphere3D(position, 5, 255, GetColor(255, 255, 255), GetColor(150, 150, 255), TRUE);

}

void DeepestSpawner::StopDeepestObject()
{
	headForTargetComponent->SetMoveSpeed(VGet(0, 0, 0));
	wallCreateAndHaver->AllWallsStop();
	grainCreateAndHaver->AllGrainsStop();
}

void DeepestSpawner::ClearDeepestObject()
{
	wallCreateAndHaver->AllWallsClear();
}

void DeepestSpawner::ReStartDeepestObject()
{
	headForTargetComponent->SetMoveSpeed(MovingSpeed);
	grainCreateAndHaver->AllGrainReStart();
}

void DeepestSpawner::CreateMovePlan()
{
	if (countDownComponent->CountEnd())
	{
		int randx = GetRand(7) - 3;
		if (randx == 2)
		{
			//grainCreateAndHaver->GrainColorChange(GrainBackGround::GrainColor::Red);
		}
		if (randx == 1)
		{
			grainShade = DeepestSpawner::GrainShade::sphere;
		}
		if (randx == -1)
		{
			grainShade = DeepestSpawner::GrainShade::square;
		}
		if (randx == -2)
		{
			//grainCreateAndHaver->GrainColorChange(GrainBackGround::GrainColor::white);
		}
		int randy = GetRand(2) - 1;
		VECTOR targetPos = VGet(0, 0, 0);
		targetPos.x = AdjacentTarget.x; //*randx;
		targetPos.y = AdjacentTarget.y;// *randy;
		headForTargetComponent->SetTargetPos(targetPos);
		countDownComponent->ResetCount();
	}
}

void DeepestSpawner::GrainSpawn(float deltaTime)
{
	VECTOR grainMiddlePos = position;
	grainMiddlePos.y += GrainHeight;
	if (boxSpawnCountDown->CountEnd())
	{
		boxSpawnCountDown->ResetCount(SpawnBoxTime - plusSpeed);
		switch (grainShade)
		{
		case(GrainShade::sphere):
			SphereGrain(grainMiddlePos);
			break;
		case(GrainShade::square):
			MonotoneGrain(grainMiddlePos, 1);
			MonotoneGrain(grainMiddlePos, -1);
			break;
		}
	}

	if (groundSpawnCountDown->CountEnd())
	{
		groundSpawnCountDown->ResetCount(SpawnGroundTime - plusSpeed);
		GroundGrain(grainMiddlePos);
	}

	//	if (randomSpawnCountDown->CountEnd())
	//	{
	//		RamdamGrain();
	//		randomSpawnCountDown->ResetCount(GetRand(SpawnRandomMaxCount));
	//	}
}

//switch (grainShade)
//{
//case(GrainShade::sphere):
//	SphereGrain(grainMiddlePos); 
//	break;
//case(GrainShade::square):	
//	SquareGrain(grainMiddlePos, 1);
//	SquareGrain(grainMiddlePos, -1); 
//	break;
//}
//
//
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
//
//void DeepestSpawner::SquareGrain(VECTOR grainMiddlePos, char plusOrMinas)
//{
//	for (int num = 0; num < 7; num++)
//	{
//		GrainBackGround* grain = grainCreateAndHaver->GetPauseGrain();
//		float x = squareHeight / 2 * plusOrMinas;
//		float y = (-squareHeight / 8) + num;
//		VECTOR squareOnPos = VGet(x, y, 0);
//		VECTOR grainPos = VAdd(position, squareOnPos);
//		VECTOR targetPos = VGet(x, y, -12);
//		//grain->ResetBackGround(grainPos, targetPos);
//	}
//}

void DeepestSpawner::MonotoneGrain(VECTOR grainMiddlePos, char plusOrMinas)
{
	float timeWidth = 10;

	for (int num = 0; num < 3; num++)
	{
		BoxShape* box = grainCreateAndHaver->GetPauseBox();
		float x = 13.0f* plusOrMinas;
		float y = ((timeWidth + 0.5f) *num) - 8;
		VECTOR boxPos = VGet(x, y, 0);
		VECTOR grainPos = VAdd(position, boxPos);
		VECTOR targetPos = VGet(x, y, -30);
		box->ResetBox(grainPos, targetPos, VGet(0, timeWidth, timeWidth), false);
	}
}

void DeepestSpawner::GroundGrain(VECTOR grainMiddlePos)
{
	for (int num = 0; num < GroundGrainHeight; num++)
	{
		GrainBackGround* grain = grainCreateAndHaver->GetPauseGround();
		float x = float((num - (GroundGrainHeight / 2)) * 2) + (GroundGrainHeight / 4);
		float y = -1.2f;
		VECTOR groundOnPos = VGet(x, y, 0);
		VECTOR grainPos = (VAdd(position, groundOnPos));
		VECTOR targetPos = VGet(x, y-1, -30);
		grain->ResetBackGround(grainPos, targetPos);
	}
}

//void DeepestSpawner::RamdamGrain()
//{
//	SphereShape* sphere = grainCreateAndHaver->GetPauseSphare();
//	//float x = GetRand(10)+10;
//	//float y = GetRand(3);
//	float x = 6;
//	float y = 2;
//	VECTOR randomPos = VGet(x, y, 0);
//	VECTOR targetPos = VGet(x, y, -30);
//	sphere->ResetSphere(randomPos, targetPos, GetRand(20)*0.1f, GetRand(2));
//	printfDx("AAAAAAAAAAAAAAAAAAAAAAAAAA\n");
//}

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
	wallPos = VAdd(wallPos, position);
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
	wallPos = VAdd(wallPos, position);
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
	wallPos = VAdd(wallPos, position);
	targetPos.z = -12;

	Wall* superWall = wallCreateAndHaver->GetPausingWall(BoxColliderComponent::ColliderTag::SuperWall);
	superWall->ResetWall(wallPos, targetPos);
}
