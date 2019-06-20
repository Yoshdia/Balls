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

	char* key;

	bool ScreenUpdate();
	void SetUpdateKey();
	void SceneChange();

	//�X�N���[���T�C�Y
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;
	const int ControlKeyNum = 256;
	const float nearCameraPos = 0;
	const float farCameraPos = 1000.0f;

	const VECTOR CameraPos = VGet(0, 0, -100);
public:
	static Game *GetInstance() { return game; }

	//game�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();
	
	char* GetAllInputKey();

	//�S�̂̏������s���֐�
	void Update();
};