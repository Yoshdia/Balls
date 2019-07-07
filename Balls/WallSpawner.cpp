#include "WallSpawner.h"
#include "Wall.h"
#include "AddSpeedWall.h"
#include "DxLib.h"
#include "Wall.h"
#include "Actor.h"

WallSpawner::WallSpawner()
{
	spawnTime = SpawnTime;
	count = 0;

	VECTOR initPos = VGet(0, -10, 0);
	for (int num = 0; num < 50; num++)
	{
		walls[num] = new AddSpeedWall(initPos);
		walls[num]->SetState(Actor::ActiveState::Paused);
	}
}


WallSpawner::~WallSpawner()
{
}

void WallSpawner::WallSpawn()
{
	float gameSpeed = Game::GetInstance()->GetGameSpeed();
	count++;
	if (count >= spawnTime-((gameSpeed-1)*10))
	{
		VECTOR wallPos;
		wallPos = CreateWallPosition();

		Wall* posingWall = nullptr;
		posingWall = GetPausingWall();
		posingWall->ResetWall(wallPos);

		wallPos = CreateWallPosition();
		//”½“]‚³‚¹‚é
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
	for (int num = 0; num < 50; num++)
	{
		Actor::ActiveState state = walls[num]->GetState();
		if (state == Actor::ActiveState::Paused)
		{
			return walls[num];
		}
	}
	return new Wall(VGet(0, -10, 0),BoxColliderComponent::ColliderTag::JammerWall);
}

VECTOR WallSpawner::CreateWallPosition()
{
	int rand = GetRand(1);

	VECTOR wallPos = VGet(1, 0, 100);
	wallPos.x += (rand * 2);

	return wallPos;
}
