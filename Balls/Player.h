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
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey);
	~Player();

	void UpdateActor(float deltaTime);
private:

};

