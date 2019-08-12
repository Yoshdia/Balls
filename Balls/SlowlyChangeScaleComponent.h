#pragma once
#include "ModelComponent.h"
class Actor;
class SlowlyChangeScaleComponent :
	public ModelComponent
{
public:
	SlowlyChangeScaleComponent(Actor* owner, int setProcessNumber);
	//モデルに変更を加えないActorに呼ばせる、Loadやscaleを最初にまとめて設定するインスタンス
	SlowlyChangeScaleComponent(Actor* owner, int setProcessNumber, VECTOR scale, const std::string& fileName);
	~SlowlyChangeScaleComponent();

	 void Update(float deltaTime);
	 void StartCoroutine(const VECTOR& howManyScale, const float& howMuchTime);
private:
	//StartCoroutineが呼ばれたときに立つフラグ。UpDateで状態を確認し処理を実行する
	bool updating;
	VECTOR scale;
	VECTOR increaseScale;


	float CulculationScale(const float& ownerScale, const float& targetScale);
};

