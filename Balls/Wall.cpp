#include "Wall.h"

Wall::Wall()
{
	pos = VGet(0, 0, 10);
	*model = MV1LoadModel("model/wall.mqo");
	*duplicateModel = MV1DuplicateModel(*model);
	*modelTexture = LoadGraph("model/grade.JPG");

	//モデルを縮小
	float scale = 0.2f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//モデルにテクスチャを張り付ける
	MV1SetTextureGraphHandle(*duplicateModel, 0, *modelTexture, FALSE);
	movingSpeed = 0.1f;
}


Wall::~Wall()
{
}

void Wall::Update()
{
	pos = VSub(pos, VGet(0, 0, movingSpeed));
}

void Wall::Render()
{
	//posに描画
	MV1SetPosition(*duplicateModel, pos);
	MV1DrawModel(*duplicateModel);
}
