#include "DxLib.h"
#include "WallSpawner.h"
#include "AddSpeedWall.h"
#include "AddPointWall.h"
#include "SuperWall.h"

const VECTOR WallSpawner::InitPos = WallSpawner::InitPos;

WallSpawner::WallSpawner()
{
	spawnTime = SpawnTime;
	count = 0;

	for (int num = 0; num < 50; num++)
	{
		walls[num] = new Wall(InitPos, BoxColliderComponent::ColliderTag::JammerWall);
		walls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		addSpeedWalls[num] = new AddSpeedWall(InitPos);
		addSpeedWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		addPointWalls[num] = new AddPointWall(InitPos);
		addPointWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		superWalls[num] = new SuperWall(InitPos);
		superWalls[num]->SetState(Actor::ActiveState::Paused);
	}
}


WallSpawner::~WallSpawner()
{
	//Wall’B‚Ì‰ð•ú‚ÍGame“à‚Ås‚¤
}

void WallSpawner::WallSpawn(float deltaTime)
{
	float gameSpeed = Game::GetInstance()->GetGameSpeed();
	float plusSpeed = (gameSpeed - 1) * 50;
	if (plusSpeed > 10)
	{
		plusSpeed = 10;
	}
	count+=deltaTime*80;
	if (count >= spawnTime - plusSpeed)
	{
		VECTOR wallPos;
		wallPos = CreateWallPositionCreateSuperWall();

		Wall* posingWall = nullptr;
		//posingWall = GetPausingWall();
		//posingWall->ResetWall(wallPos);

		wallPos = CreateWallPositionCreateSuperWall();
		//”½“]‚³‚¹‚é
		wallPos.x *= -1;
		//posingWall = GetPausingWall();
		//posingWall->ResetWall(wallPos);

		count = 0;
	}
}

void WallSpawner::WallStop()
{
	for (auto wall : walls)
	{
		wall->SetState(Actor::ActiveState::Paused);
		wall->SetPosition(InitPos);
	}
}

void WallSpawner::WallClear()
{
	for (auto wall : walls)
	{
		wall->ClearWall();
	}
}

Wall * WallSpawner::GetPausingWall()
{
	int range = GetRand(RandamSpawnWallMax);
	if (range>RandamSpawnWallMax - 3)
	{
		for (int num = 0; num < 5; num++)
		{
			Actor::ActiveState state = addSpeedWalls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return addSpeedWalls[num];
			}
		}
	}
	else if (range > RandamSpawnWallMax - 10)
	{
		for (int num = 0; num < 5; num++)
		{
			Actor::ActiveState state = addPointWalls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return addPointWalls[num];
			}
		}
	}
	else
	{
		for (int num = 0; num < 50; num++)
		{
			Actor::ActiveState state = walls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return walls[num];
			}
		}
	}
	return new Wall(VGet(0, -10, 0), BoxColliderComponent::ColliderTag::JammerWall);
}

VECTOR WallSpawner::CreateWallPositionCreateSuperWall()
{
	int rand = GetRand(1);

	VECTOR wallPos = StartRunPos;
	wallPos.x += (rand * 2);
	CreateSuperWall(rand);

	return wallPos;
}

void WallSpawner::CreateSuperWall(int rand)
{
	int random = GetRand(50);
	if (random > 10)
	{
		return;
	}
	VECTOR wallPos = StartRunPos;
	if (rand == 0)
	{
		wallPos.x += 2;
	}

	for (int num = 0; num < 5; num++)
	{
		Actor::ActiveState state = superWalls[num]->GetState();
		if (state == Actor::ActiveState::Paused)
		{
			superWalls[num]->ResetWall(wallPos);
			return;
		}
	}
	SuperWall* super=new SuperWall(InitPos);
	super->ResetWall(wallPos);
}
