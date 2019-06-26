#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"

//画面手前で左右に移動する球。二つ生成される
class Player:
	public Actor
{
public:
	//初期座標、初めに進む方向(左右)、移動のトリガーになるキーを受け取り保存する
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey,int texture);
	~Player();

	void UpdateActor(float deltaTime);
private:
	Game::MoveDirection nextMoveDirection;
	//移動予定地点
	float targetPos;
	//毎F移動する距離
	float moveDistance;
	//Gameから受け取る、このオブジェクトが動くきっかけとなるキー
	char moveInThisKey;
	//移動処理関数
	void Move();
	//移動時間
	const float movingRequiredTime = 10;
	//移動距離
	const float MovingDistance = 2;
};

