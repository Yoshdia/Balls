#pragma once
#include "Component.h"
#include "DxLib.h"

class Actor;

struct BoxInfo
{
	VECTOR position;
	//�����`�̂��߁A�����ƕ����܂Ƃ߂Ă����Ɋi�[
	float length;
};

class BoxColliderComponent :
	public Component
{
public:
	BoxColliderComponent(Actor* owner,int processNumber,float length);
	~BoxColliderComponent();
	void SetIsCollision(bool flag) { isCollision = flag; }
	bool GetIsCollision() { return isCollision; }
	 void Update(float deltaTime);
	 BoxInfo GetIndo() { return info; }
private:
	BoxInfo info;
	void updatePosition();
	//�Փ˔�����s�����ǂ����BBox�͈����W�ɗ���܂ł��̃t���O��|��
	bool isCollision;
};

