#pragma once


class Player
{
private:
	VECTOR pos;
	//�v���C���[���f��
	int *playerModel;
public:
	Player(VECTOR initPos);
	~Player();

	void Update();
	void Render();
};

