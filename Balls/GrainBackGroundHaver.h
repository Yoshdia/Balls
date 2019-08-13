#pragma once

#include "GrainBackGround.h"
#include "BoxShape.h"

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGrain();
	BoxShape* GetPauseBox();
	//‚·‚×‚Ä‚ÌGrain‚ð’âŽ~‚³‚¹‚é
	void AllGrainsStop();

	void AllGrainReStart();
private:
	void Create();
	void StopGrain(BackGround* back);
	void ReStartGrain(BackGround* back);
	GrainBackGround* ground[200];
	BoxShape* box[200];
};

