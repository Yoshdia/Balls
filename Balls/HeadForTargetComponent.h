#pragma once
#include "MoveComponent.h"

//関数で受け取ったターゲットに向かう処理
class HeadForTargetComponent :
	public MoveComponent
{
public:
	HeadForTargetComponent(Actor* owner, int processNumber, VECTOR distance, VECTOR rotateSpeed);
	~HeadForTargetComponent();

	//移動速度を設定
	void SetMoveSpeed(const VECTOR& speed);
	//ターゲットの更新
	void SetTargetPos(const VECTOR& target);
	//ターゲットに向かう処理、毎F呼ぶ
	void HeadForTarget(float deltaTime);
private:
	VECTOR ownerPos;
	VECTOR targetPos;
	VECTOR moveSpeed;
	float CulculationVector(const float& pos, const float& target);
};

