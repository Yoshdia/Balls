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
	SphereColliderComponent(Actor* owner,int processNumber,float length);
	~SphereColliderComponent();
	SphereInfo GetInfo() { return info; }
private:
	void Update(float deltaTime);
	void UpdatePosition();
	SphereInfo info;
};

