#pragma once
#include "Game.h"
#include "Component.h"
#include "DxLib.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor();
	virtual ~Actor();
	void     Update(float deltaTime);
	void     UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// セッター
	void     SetState(State state) { mState = state; }
	void     SetPosition(const VECTOR& vec) { mPosition = vec; }
	void     SetScale(float scale) { mScale = scale; }
	void     SetRotation(VECTOR rotate) { mRotation = rotate; }

	// ゲッター
	State    GetState() { return mState; }
	VECTOR& GetPosition() { return mPosition; }
	//VECTOR  GetForward() const;
	int      GetID() { return mIndex; }
	float    GetScale() { return mScale; }
	VECTOR    GetRotation() { return mRotation; }

	void     AddComponent(class Component* component);
	void     RemoveComponent(class Component* component);

protected:
	State mState;
	VECTOR mPosition;
	float mScale;
	VECTOR mRotation;

	std::vector<class Component*> mComponents;
	int mIndex;
	static int mNo;

};