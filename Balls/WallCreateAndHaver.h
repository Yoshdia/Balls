#pragma once

class Wall;
#include"BoxColliderComponent.h"

class WallCreateAndHaver
{
public:
	WallCreateAndHaver();
	~WallCreateAndHaver();
	//�SWall��State��Pause�ɂ��Đ�������
	void CreatePauseWalls();
	//����State��Pausing��Wall���擾
	Wall* GetPausingWall(const BoxColliderComponent::ColliderTag& tag);
	//���ׂĂ�Wall���~������
	void AllWallsStop();
	//���ׂĂ�Wall��������Pause��Ԃɖ߂�
	void AllWallsClear();
private:
	//Wall���ꂼ��̃A�h���X��ۑ����Ă����z��
	Wall* jammerWalls[50];
	//Wall���ꂼ��̗v�f��
	static const int JammerNum;
	Wall* addSpeedWalls[5];
	static const int AddSpeedNum;
	Wall* addPointWalls[5];
	static const int AddPointNum;
	Wall* superWalls[5];
	static const int SuperNum;
};

