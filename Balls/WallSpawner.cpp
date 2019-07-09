#include "DxLib.h"
#include "WallSpawner.h"
#include "AddSpeedWall.h"
#include "AddPointWall.h"

WallSpawner::WallSpawner()
{
	spawnTime = SpawnTime;
	count = 0;

	VECTOR initPos = VGet(0, -10, 0);
	for (int num = 0; num < 50; num++)
	{
		walls[num] = new Wall(initPos, BoxColliderComponent::ColliderTag::JammerWall);
		walls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		addSpeedWalls[num] = new AddSpeedWall(initPos);
		addSpeedWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < 5; num++)
	{
		addPointWalls[num] = new AddPointWall(initPos);
		addPointWalls[num]->SetState(Actor::ActiveState::Paused);
	}
}


WallSpawner::~WallSpawner()
{
	//Wall達の解放はGame内で行う
}

void WallSpawner::WallSpawn()
{
	float gameSpeed = Game::GetInstance()->GetGameSpeed();
	float plusSpeed = (gameSpeed - 1) * 50;
	if (plusSpeed > 10)
	{
		plusSpeed = 10;
	}
	count++;
	if (count >= spawnTime - plusSpeed)
	{
		VECTOR wallPos;
		wallPos = CreateWallPosition();

		Wall* posingWall = nullptr;
		posingWall = GetPausingWall();
		posingWall->ResetWall(wallPos);

		wallPos = CreateWallPosition();
		//反転させる
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
		wall->SetState(Actor::ActiveState::Paused);
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
	int range = GetRand(AddWallRandam);
	if (range>AddWallRandam - 3)
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
	else if (range > AddWallRandam - 10)
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

VECTOR WallSpawner::CreateWallPosition()
{
	int rand = GetRand(1);

	VECTOR wallPos = VGet(1, 0, 100);
	wallPos.x += (rand * 2);

	return wallPos;
}
