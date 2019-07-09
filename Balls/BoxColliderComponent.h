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
	enum ColliderTag
	{
		JammerWall,
		AddSpeedWall,
		AddPointWall,
		SuperWall,
	};
	BoxColliderComponent(Actor* owner,int processNumber,float length, ColliderTag tag);
	~BoxColliderComponent();
	void SetIsCollision(bool flag) { isCollision = flag; }
	bool GetIsCollision() { return isCollision; }
	void Update(float deltaTime);
	BoxInfo GetIndo() { return info; }
	void OnCollision() ;
	ColliderTag GetTag() { return myTag; }
private:
	ColliderTag myTag;
	BoxInfo info;
	void UpdatePosition();
	//�Փ˔�����s�����ǂ����BBox�͈����W�ɗ���܂ł��̃t���O��|��
	bool isCollision;
};

