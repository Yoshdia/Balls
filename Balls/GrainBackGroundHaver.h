#pragma once

class GrainBackGround;

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGrain();
	//すべてのGrainを停止させる
	void AllGrainsStop();

	void AllGrainReStart();
private:
	void Create();
	GrainBackGround* grain[500];
};

