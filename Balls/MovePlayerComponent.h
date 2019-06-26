#pragma once

#include "MoveComponent.h"
class Actor;
class Game;

class MovePlayerComponent :
	protected MoveComponent
{
public:
	MovePlayerComponent(Actor* owner,int processNumber, char moveKey, Game::MoveDirection next);
	~MovePlayerComponent();
	void Update(float deltaTime);
protected:
	Game::MoveDirection nextMoveDirection;
	//移動予定地点
	float targetPos;
	//Gameから受け取る、このオブジェクトが動くきっかけとなるキー
	char moveInputeKey;

	//移動時間
	const float movingRequiredTime = 10;
	//移動距離
	const float MovingDistance = 2;
};

