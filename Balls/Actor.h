#pragma once
#include "Game.h"
#include "Component.h"
#include "DxLib.h"

class Actor
{
public:
	enum ActiveState
	{
		Active,
		Paused,
		NoActive
	};

	Actor();
	virtual ~Actor();
	//Actor��Component���܂Ƃ߂čX�V����֐�
	void Update(float deltaTime);
	//Actor��Component�̍X�V���e
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// �Z�b�^�[
	void SetState(ActiveState setState) { state = setState; }
	void SetPosition(const VECTOR pos) { position = pos; }
	void SetScale(float setScale) { scale = setScale; }
	void SetRotation(VECTOR rotate) { rotation = rotate; }

	// �Q�b�^�[
	const ActiveState GetState() { return state; }
	VECTOR GetPosition() { return position; }
	const float GetScale() { return scale; }
	const VECTOR GetRotation() { return rotation; }
	//VECTOR  GetForward() const;
	//int      GetID() { return mIndex; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

protected:
	ActiveState state;
	VECTOR position;
	VECTOR rotation;
	float scale;

	//Actor���������Ă���Component
	std::vector<class Component*> myComponents;//mComponents;
	static int actorNumber;/*mNo*/
	//���W�A�����A�傫�����w�肳��Ȃ������ꍇ�̏����l
	const VECTOR OriginPos = VGet(0, 0, 0);
	const VECTOR OriginQua = VGet(0, 0, 0);
	const float OriginScale = 1.0f;

};