#include "Wall.h"

Wall::Wall()
{
	pos = VGet(0, 0, 10);
	*model = MV1LoadModel("model/wall.mqo");
	*duplicateModel = MV1DuplicateModel(*model);
	*modelTexture = LoadGraph("model/grade.JPG");

	//���f�����k��
	float scale = 0.2f;
	MV1SetScale(*duplicateModel, VGet(scale, scale, scale));
	//���f���Ƀe�N�X�`���𒣂�t����
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
	//pos�ɕ`��
	MV1SetPosition(*duplicateModel, pos);
	MV1DrawModel(*duplicateModel);
}
