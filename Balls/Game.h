#pragma once

class Scene;

//�Q�[���S�̂̏���
class Game
{
private:
	Game() {};
	static Game *game;
	Scene *scene;

	bool ScreenUpdate();
	void SetUpdateKey(char* control);
	void SceneChange(char* key);

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