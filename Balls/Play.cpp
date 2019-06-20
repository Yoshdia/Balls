#include"DxLib.h"
#include "Play.h"

Play::Play()
{
	//FIXME
	//プレイヤーモデルにint型の3dモデルを読み込む
	playerModel = new int;
	*playerModel = MV1LoadModel("model/Ball.x");
	if (*playerModel == -1)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "error!");
	}
}


Play::~Play()
{
	//解放
	MV1DeleteModel(*playerModel);
	delete playerModel;
}

void Play::Update()
{
}

void Play::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Play");
	//3D空間の認識とカメラの正常動作のために中央に10時の線を描く
	DrawLine3D(VGet(-5, 0, 0), VGet(5, 0, 0), GetColor(255, 255, 255));
	DrawLine3D(VGet(0, -5, 0), VGet(0, 5, 0), GetColor(255, 255, 255));
	//中央にプレイヤーモデルを描画
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
