#pragma once

#include "MoveComponent.h"
class Actor;
class Game;

class MovePlayerComponent :
	protected MoveComponent
{
public:
	//移動を検知するmoveKey、初めにどちらへ移動するかのnextを指定
	MovePlayerComponent(Actor* owner,int processNumber, char moveKey, Game::MoveDirection next,VECTOR rotateSpeed);
	~MovePlayerComponent();
	void Update(float deltaTime);

	void StartCorutine();
	void StopCorutine() { updating = false; }
	void SetMoveDirection(Game::MoveDirection next) { nextMoveDirection = next; }
protected:

	bool updating;
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
	//移動距離の二分の一
	float middlePos;

	//移動時間F
	static const float MovingRequiredTime ;
	//移動距離
	static const float MovingDistanceSum ;
};

