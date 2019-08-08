#pragma once
#include "Actor.h"
#include "DxLib.h"
#include "BoxColliderComponent.h"

class HeadForTargetComponent;
class Wall :
	public Actor
{
public:
	Wall(BoxColliderComponent::ColliderTag tag,const std::string& modelFileName);
	~Wall();

	void UpdateActor(float deltaTime);

	//���W���Z�b�g�Astate��Active�ɂ��đ��点��
	void ResetWall(VECTOR pos,VECTOR target);
	//���W����ʊO�ɃZ�b�g���Astate��Pause�ɂ��đҋ@��Ԃɂ�����
	void ClearWall();

	void StopMove() ;
	void OnCollision();
	const VECTOR InitPos = VGet(-10, -10, -10);
protected:
	HeadForTargetComponent * headForTarget;
	BoxColliderComponent* boxCollider;
	const VECTOR moveSpeed = VGet(0, 0, -60.0f);
};

