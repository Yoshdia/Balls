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
	//キー情報の取得と初期化
	key = new char[ControlKeyNum];
	UpdateKey();
}

void InputKey::UpdateKey()
{
	//全ての入力状態をtmpKeyに格納
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	//num番目のキーが押されていたら加算
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			key[num]++;
		}
		else
		{
			//押されていないキーは0にする
			key[num] = 0;
		}
	}
}



