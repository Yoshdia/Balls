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
		ground[num] = new GrainBackGround("Resouce/model/mqo/ground.mv1", VGet(0.01f, 0.001f, 0.06f));
	}	
	for (int num = 0; num < 200; num++)
	{
		grain[num] = new GrainBackGround("Resouce/model/whiteSphere.mv1", VGet(0.002f, 0.002f, 0.002f));
	}
	for (int num = 0; num < 200; num++)
	{
		box[num] = new BoxShape();
	}	
	for (int num = 0; num < 10; num++)
	{
		sphere[num] = new SphereShape();
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

GrainBackGround * GrainBackGroundHaver::GetPauseGround()
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
	groundNum = new GrainBackGround("Resouce/model/normalSphere.mv1", VGet(0.01f, 0.001f, 0.06f));
	}
	return groundNum;
}

GrainBackGround * GrainBackGroundHaver::GetPauseGrain()
{
	GrainBackGround* grainNum = nullptr;
	for (int num = 0; num < 200; num++)
	{
		if (grain[num]->GetState() == Actor::ActiveState::Paused)
		{
			grainNum = grain[num];
			break;
		}
	}
	if (!grainNum)
	{
		grainNum = new GrainBackGround("Resouce/model/normalSphere.mv1", VGet(0.002f, 0.002f, 0.002f));
	}
	return grainNum;
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

SphereShape * GrainBackGroundHaver::GetPauseSphare()
{
	SphereShape* sphereNum = nullptr;
	for (int num = 0; num < 10; num++)
	{
		if (sphere[num]->GetState() == Actor::ActiveState::Paused)
		{
			sphereNum = sphere[num];
			break;
		}
	}
	if (!sphereNum)
	{
		sphereNum = new SphereShape();
	}
	return sphereNum;
}

void GrainBackGroundHaver::AllGrainsStop()
{
	for (auto back : ground)
	{
		StopGrain(back);
	}
	for (auto back : grain)
	{
		StopGrain(back);
	}
	for (auto back : box)
	{
		StopGrain(back);
	}
	for (auto back : sphere)
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
	for (auto back : grain)
	{
		ReStartGrain(back);
	}
	for (auto back : box)
	{
		ReStartGrain(back);
	}
	for (auto back : sphere)
	{
		ReStartGrain(back);
	}
}
