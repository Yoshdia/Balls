#pragma once

class GrainBackGround;

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGrain();
private:
	void Create();
	GrainBackGround* grain[500];
};

