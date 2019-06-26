#pragma once

#include "Game.h"
#include "component.h"

class ModelComponent : public Component
{
public:
	ModelComponent(class Actor* owner,int drawNumber=100);//int drawOrder = 100
	~ModelComponent();
	virtual void DrawModel();
	virtual void SetModel(int model);
	void SetModelScale(float scale) ;

protected:
	//����Component���������Ă��郂�f���̃|�C���^(�ǂݍ��݃G���[�̍ۂ�-1�����邽�ߏ����l�ɂ�-1������)
	int modelId;//mModelID;

};