#pragma once
class InputKey
{
public:
	static InputKey* GetInstance() { return inputKey; }
	void Create();
	void Delete();
	~InputKey();

	//全ての入力状態を取得
	void UpdateKey();
	char* GetAllInputKey() { return key; };
private:
	InputKey();
	static InputKey* inputKey;

	char* key;
	//キーボードから取得できるキーの最大数
	const int ControlKeyNum = 256;
};

