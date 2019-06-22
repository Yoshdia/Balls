#pragma once

#include "Wall.h"
#include <list>

class WallSetter
{
public:
	WallSetter();
	~WallSetter();

	void Update();
	void Render();
	void SetWall();
private:
	//const int wallMax = 20;
	//Wall *waitingWalls[20];
	Wall* GetWaitingWall();
	Wall* GetNullWall();
	std::list<class Wall*> activeWalls;
};

