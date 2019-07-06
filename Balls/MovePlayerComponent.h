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
	//次の移動方向
	Game::MoveDirection nextMoveDirection;
	//移動予定地点
	float targetPos;
	//Gameから受け取る、このオブジェクトが動くきっかけとなるキー
	char moveInputeKey;
	//移動中かどうか
	bool moving ;
	//残りの移動距離、0になるとmovingを倒す
	float movement;

	//移動時間F
	const float movingRequiredTime = 0.1f;
	//移動距離
	const float MovingDistance = 2.0f;
};

