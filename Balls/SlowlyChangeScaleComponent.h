#pragma once
#include "ModelComponent.h"
class Actor;
class SlowlyChangeScaleComponent :
	public ModelComponent
{
public:
	SlowlyChangeScaleComponent(Actor* owner, int setProcessNumber);
	//���f���ɕύX�������Ȃ�Actor�ɌĂ΂���ALoad��scale���ŏ��ɂ܂Ƃ߂Đݒ肷��C���X�^���X
	SlowlyChangeScaleComponent(Actor* owner, int setProcessNumber, VECTOR scale, const std::string& fileName);
	~SlowlyChangeScaleComponent();

	 void Update(float deltaTime);
	 void StartCoroutine(const VECTOR& howManyScale, const float& howMuchTime);
private:
	//StartCoroutine���Ă΂ꂽ�Ƃ��ɗ��t���O�BUpDate�ŏ�Ԃ��m�F�����������s����
	bool updating;
	VECTOR scale;
	VECTOR increaseScale;


	float CulculationScale(const float& ownerScale, const float& targetScale);
};

