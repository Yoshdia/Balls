#pragma once


class Player
{
private:
	VECTOR pos;
	//プレイヤーモデル
	int *playerModel;

	enum PlayerMoveDirection
	{
		rightMove,
		leftMove,
	};
	PlayerMoveDirection nextMoveDirection;
	float targetPos;
	float needDis;
	void Move();

	//移動時間
	const float movingRequiredTime=60;
	//移動距離
	const float MovingDistance = 10;
public:
	Player(VECTOR initPos);
	~Player();

	void Update();
	void Render();
};

