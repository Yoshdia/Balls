#include "Wall.h"

Wall::Wall()
{
	pos = VGet(0, 0, 10);
	model = new int;
	*model = NULL;
	*model = MV1LoadModel("model/wall.mqo");
	duplicateModel = new int;
	*duplicateModel = NULL;
	*duplicateModel = MV1DuplicateModel(*model);
	modelTexture = new int;
	*modelTexture = NULL;
	*modelTexture = LoadGraph("model/grade.JPG");

	//モデルを縮小
	float scale = 0.2f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//モデルにテクスチャを張り付ける
	MV1SetTextureGraphHandle(*duplicateModel, 0, *modelTexture, FALSE);
	movingSpeed = 0.1f;
	comeOutCamera = false;
}

Wall::~Wall()
{
	MV1DeleteModel(*model);
	delete model;
	model = NULL;
	MV1DeleteModel(*duplicateModel);
	delete duplicateModel;
	duplicateModel = NULL;
	DeleteGraph(*modelTexture);
	delete modelTexture;
	modelTexture = NULL;
}

void Wall::Update()
{
	pos = VSub(pos, VGet(0, 0, movingSpeed));

	if (pos.z < -10)
	{
		comeOutCamera=true;
		
	}
}

void Wall::Render()
{
	//posに描画
	MV1SetPosition(*duplicateModel, pos);
	MV1DrawModel(*duplicateModel);
}

void Wall::ResetWall(float x)
{
	pos = VGet(x, 0, 10);
	comeOutCamera = false;

}
