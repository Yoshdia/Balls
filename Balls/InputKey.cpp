#include "DxLib.h"
#include "InputKey.h"

InputKey* InputKey::inputKey = nullptr;

void InputKey::Create()
{
	if (!inputKey)
	{
		inputKey = new InputKey;
	}
}

void InputKey::Delete()
{
	delete inputKey;
	inputKey = nullptr;
}

InputKey::~InputKey()
{
	delete[] key;
}

InputKey::InputKey()
{
	//�L�[���̎擾�Ə�����
	key = new char[ControlKeyNum];
	UpdateKey();
}

void InputKey::UpdateKey()
{
	//�S�Ă̓��͏�Ԃ�tmpKey�Ɋi�[
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	//num�Ԗڂ̃L�[��������Ă�������Z
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			key[num]++;
		}
		else
		{
			//������Ă��Ȃ��L�[��0�ɂ���
			key[num] = 0;
		}
	}
}



