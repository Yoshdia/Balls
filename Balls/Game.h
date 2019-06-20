#pragma once

//�Q�[���S�̂̏���
class Game
{
private:
	Game() {};
	static Game *game;

	bool ScreenUpdate();
	void SetUpdateKey(char* control);

	//�X�N���[���T�C�Y
	const int ScreenWidth = 500;
	const int ScreenHeight = 500;
	const int ControlKeyNum = 256;
public:
	static Game *GetInstance() { return game; }

	//game�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();
	
	//�S�̂̏������s���֐�
	void Update();
};