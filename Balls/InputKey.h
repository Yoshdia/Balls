#pragma once
class InputKey
{
public:
	static InputKey* GetInstance() { return inputKey; }
	void Create();
	void Delete();
	~InputKey();

	//�S�Ă̓��͏�Ԃ��擾
	void UpdateKey();
	char* GetAllInputKey() { return key; };
private:
	InputKey();
	static InputKey* inputKey;

	char* key;
	//�L�[�{�[�h����擾�ł���L�[�̍ő吔
	const int ControlKeyNum = 256;
};

