#include "WallCreateAndHaver.h"
#include "AddSpeedWall.h"
#include "AddPointWall.h"
#include "JammerWall.h"
#include "SuperWall.h"

//íËêîÇÃêÈåæ
const int WallCreateAndHaver::JammerNum = 50;
const int WallCreateAndHaver::AddPointNum=5;
const int WallCreateAndHaver::AddSpeedNum=5;
const int WallCreateAndHaver::SuperNum=5;

WallCreateAndHaver::WallCreateAndHaver()
{
}

WallCreateAndHaver::~WallCreateAndHaver()
{
}

void WallCreateAndHaver::CreatePauseWalls()
{
	for (int num = 0; num < JammerNum; num++)
	{
		jammerWalls[num] = new JammerWall();
		jammerWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < AddSpeedNum; num++)
	{
		addSpeedWalls[num] = new AddSpeedWall();
		addSpeedWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < AddPointNum; num++)
	{
		addPointWalls[num] = new AddPointWall();
		addPointWalls[num]->SetState(Actor::ActiveState::Paused);
	}
	for (int num = 0; num < SuperNum; num++)
	{
		superWalls[num] = new SuperWall();
		superWalls[num]->SetState(Actor::ActiveState::Paused);
	}
}

Wall * WallCreateAndHaver::GetPausingWall(const BoxColliderComponent::ColliderTag& tag)
{
	switch (tag)
	{
	case(BoxColliderComponent::ColliderTag::JammerWall):
		for (int num = 0; num < JammerNum; num++)
		{
			Actor::ActiveState state = jammerWalls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return jammerWalls[num];
			}
		}			
		break;
	case(BoxColliderComponent::ColliderTag::AddPointWall):
		for (int num = 0; num < AddPointNum; num++)
		{
			Actor::ActiveState state = addPointWalls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return addPointWalls[num];
			}
		}
		break;
	case(BoxColliderComponent::ColliderTag::AddSpeedWall):
		for (int num = 0; num < AddSpeedNum; num++)
		{
			Actor::ActiveState state = addSpeedWalls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return addSpeedWalls[num];
			}
		}
		break;
	case(BoxColliderComponent::ColliderTag::SuperWall):
		for (int num = 0; num < SuperNum; num++)
		{
			Actor::ActiveState state = superWalls[num]->GetState();
			if (state == Actor::ActiveState::Paused)
			{
				return superWalls[num];
			}
		}
		break;
	}
	return new JammerWall;
}

void WallCreateAndHaver::AllWallsStop()
{
	for (auto wall : jammerWalls)
	{
		wall->StopMove();
	}
	for (auto wall : addPointWalls)
	{
		wall->StopMove();
	}
	for (auto wall : addSpeedWalls)
	{
		wall->StopMove();
	}
	for (auto wall : superWalls)
	{
		wall->StopMove();
	}
}

void WallCreateAndHaver::AllWallsClear()
{
	for (auto wall : jammerWalls)
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

