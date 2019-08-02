#include "DxLib.h"
#include "DeepestSpawner.h"
#include "GrainBackGroundHaver.h"
#include "GrainBackGround.h"
#include <math.h>
#include "InputKey.h"

const float DeepestSpawner::Radius = 6;

DeepestSpawner::DeepestSpawner()
{
	grains = new GrainBackGroundHaver();
	myPos = VGet(0, 0, 50);
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
	if (count >= 10)
	{
		count = 0;
		for (int num = 1; num <= 12; num++)
		{
			//if (GetRand(3) >= 2)
			{
				GrainBackGround* grain = grains->GetPauseGrain();
				VECTOR circleOnPos = VGet(cos(num * 30), sin(num * 30), 0)*Radius;
				VECTOR grainPos = VAdd(myPos, circleOnPos);
				grain->ResetBackGround(grainPos, circleOnPos);
			}

		}
	}

}
