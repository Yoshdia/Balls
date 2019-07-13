#pragma once
#include "Component.h"
#include "DxLib.h"
#include <vector>

class Actor
{
public:
	enum ActiveState
	{
		Active,
		Paused,
	};

	Actor();
	virtual ~Actor();
	//ActorとComponentをまとめて更新する関数
	void Update(float deltaTime);
	//ActorとComponentの更新内容
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// セッター
	void SetState(ActiveState setState) { state = setState; }
	void SetPosition(const VECTOR pos) { position = pos; }
	void SetScale(VECTOR setScale) { scale = setScale; }
	void SetRotation(VECTOR rotate) { rotation = rotate; }

	// ゲッター
	const ActiveState GetState() { return state; }
	VECTOR GetPosition() { return position; }
	const VECTOR GetScale() { return scale; }
	const VECTOR GetRotation() { return rotation; }
	//VECTOR  GetForward() const;
	//int      GetID() { return mIndex; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	virtual void OnCollision() {};
protected:

	ActiveState state;
	VECTOR position;
	VECTOR rotation;
	VECTOR scale;

	//Actorが所持しているComponent
	std::vector<class Component*> myComponents;//mComponents;
	static int actorNumber;/*mNo*/
	//座標、向き、大きさを指定されなかった場合の初期値
	const VECTOR OriginPos = VGet(0, 0, 0);
	const VECTOR OriginQua = VGet(0, 0, 0);
	const VECTOR OriginScale = VGet(0,0,0);

};