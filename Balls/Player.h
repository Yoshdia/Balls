#pragma once


class Player
{
private:
	VECTOR pos;
	//�v���C���[���f��
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

	//�ړ�����
	const float movingRequiredTime=60;
	//�ړ�����
	const float MovingDistance = 10;
public:
	Player(VECTOR initPos);
	~Player();

	void Update();
	void Render();
};

