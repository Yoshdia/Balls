#pragma once

class Scene;
class Camera;

//�Q�[���S�̂̏���
class Game
{
private:
	Game() {};
	static Game *game;
	Scene *scene;
	Camera *camera;

	bool ScreenUpdate();
	void SetUpdateKey(char* control);
	void SceneChange(char* key);

	//�X�N���[���T�C�Y
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;
	const int ControlKeyNum = 256;
public:
	static Game *GetInstance() { return game; }

	//game�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();
	
	//�S�̂̏������s���֐�
	void Update();
};