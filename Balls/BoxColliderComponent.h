#pragma once
#include "Component.h"
#include "DxLib.h"

class Actor;

struct BoxInfo
{
	VECTOR position;
	//正方形のため、高さと幅をまとめてここに格納
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
	//衝突判定を行うかどうか。Boxは一定座標に来るまでこのフラグを倒す
	bool isCollision;
};

