#include "DxLib.h"
#include "WallSpawner.h"
#include "AddSpeedWall.h"
#include "AddPointWall.h"
#include "JammerWall.h"
#include "SuperWall.h"

WallSpawner::WallSpawner()
{
	spawnTime = SpawnTime;
	count = 0;

	for (int num = 0; num < 50; num++)
	{
		walls[num] = new JammerWall();
		walls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		addSpeedWalls[num] = new AddSpeedWall();
		addSpeedWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		addPointWalls[num] = new AddPointWall();
		addPointWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		superWalls[num] = new SuperWall();
		superWalls[num]->SetState(Actor::ActiveState::Paused);
	}
}


WallSpawner::~WallSpawner()
{
	//Wall�B�̉����Game���ōs��
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
		int rand = GetRand(1);
		wallPos = CreateWallPositionCreateSuperWall(rand);
		CreateSuperWall(rand,1);

		Wall* posingWall = nullptr;
		posingWall = GetPausingWall();
		posingWall->ResetWall(wallPos);

		rand = GetRand(1);
		wallPos = CreateWallPositionCreateSuperWall(rand);
		CreateSuperWall(rand,-1);
		//���]������
		wallPos.x *= -1;
		posingWall = GetPausingWall();
		posingWall->ResetWall(wallPos);

		count = 0;
	}
}

void WallSpawner::WallStop()
{
	for (auto wall : walls)
	{
		wall->StopMove();
	}
	for (auto wall : addPointWalls)
	{
		wall->StopMove();
	}
	for (auto wall : addPointWalls)
	{
		wall->StopMove();
	}
	for (auto wall : superWalls)
	{
		wall->StopMove();
	}
}

void WallSpawner::WallClear()
{
	for (auto wall : walls)
	{
		wall->ClearWall();
	}
	for (auto wall : addPointWalls)
	{
		wall->ClearWall();
	}
	for (auto wall : addPointWalls)
	{
		wall->ClearWall();
	}
	for (auto wall : superWalls)
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
	return new JammerWall();
}

VECTOR WallSpawner::CreateWallPositionCreateSuperWall(int rand)
{
	VECTOR wallPos = StartRunPos;
	wallPos.x += (rand * 2);

	return wallPos;
}

void WallSpawner::CreateSuperWall(int rand,int rightOrLeft)
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
		wallPos.x += 2*rightOrLeft;
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
	SuperWall* super=new SuperWall();
	super->ResetWall(wallPos);
}
