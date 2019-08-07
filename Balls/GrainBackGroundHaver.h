#pragma once

class GrainBackGround;

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGrain();
	//‚·‚×‚Ä‚ÌGrain‚ð’âŽ~‚³‚¹‚é
	void AllGrainsStop();

	void AllGrainReStart();
private:
	void Create();
	GrainBackGround* grain[500];
};

