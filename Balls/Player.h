#pragma once

#include "Dxlib.h"
#include "Game.h"
#include "Actor.h"

//��ʎ�O�ō��E�Ɉړ����鋅�B����������
class Player:
	public Actor
{
public:
	//�������W�A���߂ɐi�ޕ���(���E)�A�ړ��̃g���K�[�ɂȂ�L�[���󂯎��ۑ�����
	Player(VECTOR initPos, Game::MoveDirection next, char moveKey);
	~Player();

	void UpdateActor(float deltaTime);
private:

};

