#pragma once

#include "DxLib.h"
#include "component.h"
#include <string>
class Actor;

class ModelComponent : public Component
{
public:
	ModelComponent(Actor* owner, int setProcessNumber);
	//���f���ɕύX�������Ȃ�Actor�ɌĂ΂���ALoad��scale���ŏ��ɂ܂Ƃ߂Đݒ肷��C���X�^���X
    ModelComponent(Actor* owner, int setProcessNumber, VECTOR scale, const std::string& fileName);
	virtual ~ModelComponent();
	virtual void DrawModel();
	virtual void SetModel(int model);
	void SetModelScale(VECTOR scale) ;
	void SetModel(int model, int tex);

	static const int DrawPlayerNumber;
	static const int DrawWallNumber;
	static const int DrawBoxEffectNumber;
	static const int DrawGrainNumber;
protected:
	//����Component���������Ă��郂�f���̃|�C���^(�ǂݍ��݃G���[�̍ۂ�-1�����邽�ߏ����l�ɂ�-1������)
	int modelId;
};