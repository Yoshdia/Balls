#pragma once

class GrainBackGround;

class GrainBackGroundHaver
{
public:
	GrainBackGroundHaver();
	~GrainBackGroundHaver();
	GrainBackGround* GetPauseGrain();
	//���ׂĂ�Grain���~������
	void AllGrainsStop();

	void AllGrainReStart();
private:
	void Create();
	GrainBackGround* grain[500];
};

