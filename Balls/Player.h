#pragma once

//画面手前で左右に移動する球。二つ生成される
class Player
{
public:
	//このオブジェクトがどちらの向きへ進むのかの列挙体。移動距離MovingDistanceに直接乗算する
	enum PlayerMoveDirection
	{
		RightMove = 1,
		LeftMove = -1,
	};
	//初期座標、初めに進む方向(左右)、移動のトリガーになるキーを受け取り保存する
	Player(VECTOR initPos, PlayerMoveDirection next, char moveKey);
	~Player();

	void Update();
	void Render();
private:

	PlayerMoveDirection nextMoveDirection;

	VECTOR pos;
	//プレイヤーモデル
	int *playerModel;
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

