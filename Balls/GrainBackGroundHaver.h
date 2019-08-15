#pragma once

#include "GrainBackGround.h"
#include "BoxShape.h"
#include "SphereShape.h"

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGround();
	GrainBackGround* GetPauseGrain();
	BoxShape* GetPauseBox();
	SphereShape* GetPauseSphare();
	//‚·‚×‚Ä‚ÌGrain‚ð’âŽ~‚³‚¹‚é
	void AllGrainsStop();

	void AllGrainReStart();
private:
	void Create();
	void StopGrain(BackGround* back);
	void ReStartGrain(BackGround* back);
	GrainBackGround* ground[200];
	GrainBackGround* grain[200];
	BoxShape* box[200];
	SphereShape* sphere[10];
};

