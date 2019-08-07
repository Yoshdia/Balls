#include "GrainBackGroundHaver.h"
#include "GrainBackGround.h"


GrainBackGroundHaver::GrainBackGroundHaver()
{
	Create();
}


GrainBackGroundHaver::~GrainBackGroundHaver()
{
}

void GrainBackGroundHaver::Create()
{
	for (int num = 0; num < 500; num++)
	{
		grain[num] = new GrainBackGround();
	}
}

GrainBackGround * GrainBackGroundHaver::GetPauseGrain()
{
	for (int num = 0; num < 500; num++)
	{
		if (grain[num]->GetState() == Actor::ActiveState::Paused)
		{
			return grain[num];
		}

	}

	return new GrainBackGround();
}

void GrainBackGroundHaver::AllGrainsStop()
{
	for (auto back : grain)
	{
		back->StopMove();
	}
}

void GrainBackGroundHaver::AllGrainReStart()
{
	for (auto back : grain)
	{
		Actor::ActiveState backState = back->GetState();
		if (backState == Actor::ActiveState::Active)
		{
			back->MoveReStart();
		}
	}
}

