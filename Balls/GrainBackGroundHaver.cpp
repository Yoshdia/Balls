#include "GrainBackGroundHaver.h"


GrainBackGroundHaver::GrainBackGroundHaver()
{
	Create();
}


GrainBackGroundHaver::~GrainBackGroundHaver()
{
}

void GrainBackGroundHaver::Create()
{
	for (int num = 0; num < 200; num++)
	{
		ground[num] = new GrainBackGround();
	}
	for (int num = 0; num < 200; num++)
	{
		box[num] = new BoxShape();
	}
}

void GrainBackGroundHaver::StopGrain(BackGround * back)
{
	back->StopMove();
}

void GrainBackGroundHaver::ReStartGrain(BackGround * back)
{
	Actor::ActiveState backState = back->GetState();
	if (backState == Actor::ActiveState::Active)
	{
		back->MoveReStart();
	}
}

GrainBackGround * GrainBackGroundHaver::GetPauseGrain()
{
	GrainBackGround* groundNum=nullptr;
	for (int num = 0; num < 200; num++)
	{
		if (ground[num]->GetState() == Actor::ActiveState::Paused)
		{
			groundNum = ground[num];
			break;
		}
	}
	if(!groundNum)
	{
	groundNum = new GrainBackGround();	
	}
	return groundNum;
}

BoxShape * GrainBackGroundHaver::GetPauseBox()
{
	BoxShape* boxNum = nullptr;
	for (int num = 0; num < 200; num++)
	{
		if (box[num]->GetState() == Actor::ActiveState::Paused)
		{
			boxNum = box[num];
			break;
		}
	}
	if (!boxNum)
	{
		boxNum = new BoxShape();
	}
	return boxNum;
}

void GrainBackGroundHaver::AllGrainsStop()
{
	for (auto back : ground)
	{
		StopGrain(back);
		back->StopMove();
	}
	for (auto back : box)
	{
		StopGrain(back);
	}
}

void GrainBackGroundHaver::AllGrainReStart()
{
	for (auto back : ground)
	{
		ReStartGrain(back);
	}
	for (auto back : box)
	{
		ReStartGrain(back);
	}
}
