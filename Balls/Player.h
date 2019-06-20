#pragma once


class Player
{
private:
	VECTOR pos;
	//プレイヤーモデル
	int *playerModel;
public:
	Player(VECTOR initPos);
	~Player();

	void Update();
	void Render();
};

