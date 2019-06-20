#include"DxLib.h"
#include "Play.h"

Play::Play()
{
	//FIXME
	//�v���C���[���f����int�^��3d���f����ǂݍ���
	playerModel = new int;
	*playerModel = MV1LoadModel("model/Ball.x");
	if (*playerModel == -1)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "error!");
	}
}


Play::~Play()
{
	//���
	MV1DeleteModel(*playerModel);
	delete playerModel;
}

void Play::Update()
{
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	//3D��Ԃ̔F���ƃJ�����̐��퓮��̂��߂ɒ�����10���̐���`��
	DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
	//�����Ƀv���C���[���f����`��
	MV1SetPosition(*playerModel, VGet(0, 0, 0));
	MV1DrawModel(*playerModel);
}

sceneName Play::SceneChange(char* key)
{
	if (key[KEY_INPUT_0] == 1)
	{
		return sceneName::clear;
	}
	return sceneName::noChange;
}
