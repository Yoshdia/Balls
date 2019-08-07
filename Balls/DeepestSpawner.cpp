#include "DxLib.h"
#include "DeepestSpawner.h"
#include "GrainBackGroundHaver.h"
#include "GrainBackGround.h"
#include <math.h>
#include "InputKey.h"

const float DeepestSpawner::Radius = 6;
const float DeepestSpawner::grainHeight = 2;

DeepestSpawner::DeepestSpawner()
{
	grains = new GrainBackGroundHaver();
	myPos = VGet(0, 0, 30);
	grainMiddlePos = myPos;
	grainMiddlePos.y += grainHeight;
	count = 0;
	rightMoving = false;
}


DeepestSpawner::~DeepestSpawner()
{
	delete grains;
}

void DeepestSpawner::SpawnerUpdate(float deltaTime)
{
	GrainSpawn(deltaTime);
}

void DeepestSpawner::GrainSpawn(float deltaTime)
{
	count++;
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_1])
		myPos.x -= 0.01f;
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_2])
		myPos.x += 0.01f;
	grainMiddlePos = myPos;
	grainMiddlePos.y += grainHeight;
	if (count >= 10)
	{
		count = 0;
		for (int num = 1; num <= 12; num++)
		{
				GrainBackGround* grain = grains->GetPauseGrain();
				float x = (double)cos(num * 60);
				float y = (double)sin(num * 60);
				VECTOR circleOnPos = VGet(x,y, 0)*Radius;
				VECTOR grainPos = VAdd(grainMiddlePos, circleOnPos);
				grain->ResetBackGround(grainPos, circleOnPos);
		}
	}
}
