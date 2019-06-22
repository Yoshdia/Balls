#include "WallSetter.h"



WallSetter::WallSetter()
{
	//for (int num = 0; num < wallMax; num++)
	//{
	//	waitingWalls[num] = new Wall;
	//}
}

WallSetter::~WallSetter()
{
	//for (int num = 0; num < wallMax; num++)
	//{
	//	if (waitingWalls[num] != NULL)
	//	{
	//		delete waitingWalls[num];
	//	}
	//}
	activeWalls.clear();
}

void WallSetter::Update()
{
	//auto itr = activeWalls.begin();
	//for (; itr != activeWalls.end();)
	//{
	//	if (*itr != NULL)
	//	{
	//		(*itr)->Update();
	//		if ((*itr)->GetComeOutCameraFlag() == true)
	//		{
	//			Wall *wall = GetNullWall();
	//			if (wall != nullptr)
	//			{
	//				wall = *itr;
	//			}
	//			itr = activeWalls.erase(itr);
	//		}
	//		else
	//		{
	//			++itr;
	//			continue;
	//		}
	//	}
	//	++itr;
	//}
	for (std::list<Wall*>::const_iterator itr = activeWalls.begin(); itr != activeWalls.end();)
	{
		(*itr)->Update();
		if ((*itr)->GetComeOutCameraFlag())
		{
			itr = activeWalls.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void WallSetter::Render()
{
	for (auto itr : activeWalls)
	{
		itr->Render();
	}
}

void WallSetter::SetWall()
{
	//Wall *wall = GetWaitingWall();
	//(*wall).ResetWall(Game::MoveDirection::Left);
	//activeWalls.push_back(wall);

	//Wall *secondWall = GetWaitingWall();
	//(*secondWall).ResetWall(Game::MoveDirection::Right);
	//activeWalls.push_back(secondWall);

	activeWalls.push_back(new Wall);
	activeWalls.back()->ResetWall(2);

	activeWalls.push_back(new Wall);
	activeWalls.back()->ResetWall(-2);
}



Wall * WallSetter::GetWaitingWall()
{
	//for (int num = 0; num < wallMax; num++)
	//{
	//	if (waitingWalls[num] != NULL)
	//	{
	//		return waitingWalls[num];
	//	}
	//}
	return nullptr;
}

Wall * WallSetter::GetNullWall()
{
	//for (int num = 0; num < wallMax; num++)
	//{
	//	if (waitingWalls[num] == NULL)
	//	{
	//		return waitingWalls[num];
	//	}
	//}
	return nullptr;
}



