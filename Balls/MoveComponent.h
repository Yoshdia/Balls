#pragma once

#include "Component.h"
class Actor;

//受け取ったdistanceをActorの座標に加算し続けるComponent
class MoveComponent :
	public Component
{
public:
	MoveComponent(Actor* owner ,int processNumber, VECTOR distance);
	~MoveComponent();
	void Update(float deltaTime);
protected:
	//座標にmoveDistanceを足すだけの関数
	void Move(float deltaTime);
	//継承先から呼ばれる、deltaTimeを継承先で計算するため引数や関数内にdeltaTimeがないMove関数
	void Move();
	VECTOR position;
	//毎F移動する距離
	VECTOR moveDistance;
};

