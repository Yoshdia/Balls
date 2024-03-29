#pragma once
#include "Component.h"
#include "DxLib.h"
class Actor;

struct SphereInfo
{
	VECTOR position;
	float length;
};

class SphereColliderComponent :
	public Component
{
public:
	enum CollisionTag
	{
		NormalPlayer,
		SuperPlayer,
	};
	SphereColliderComponent(Actor* owner,int processNumber,float length);
	~SphereColliderComponent();
	SphereInfo GetInfo() { return info; }
	void TagChange(CollisionTag tag) { myTag = tag; };
	CollisionTag GetTag() { return myTag; }
	void OnCollision();
	void Update(float deltaTime);
	void OutOfScreen() ;
private:
	CollisionTag myTag;
	void UpdatePosition();
	SphereInfo info;
};

