#pragma once

#include "GrainBackGround.h"

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGrain();
	//すべてのGrainを停止させる
	void AllGrainsStop();

	void AllGrainReStart();

	void GrainColorChange(GrainBackGround::GrainColor color);
private:
	void Create();
	GrainBackGround* grain[500];
};

