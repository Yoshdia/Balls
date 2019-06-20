#pragma once

class Scene;
class Camera;

//�Q�[���S�̂̏���
class Game
{
public:
	static Game *GetInstance() { return game; }

	//game�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();
	
	char* GetAllInputKey();

	//�S�̂̏������s���֐�
	void Update();

private:
	Game() {};
	static Game *game;

	Scene *scene;

	char* key;

	//��ʂ̍X�V�B�G���[���N�����ꍇ�Q�[�����I������
	bool ScreenUpdate();
	//�S�Ă̓��͏�Ԃ��擾
	void SetUpdateKey();
	//�V�[���`�F���W�BScene�̔h���N���X��������ƑJ�ڐ�����߂�
	void SceneChange();

	//�X�N���[���T�C�Y
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;
	//�L�[�{�[�h����擾�ł���L�[�̍ő吔
	const int ControlKeyNum = 256;
	//�J�����̍��W
	const VECTOR CameraPos = VGet(0, 0, -10);
	//�J�����̎���͈�
	const float nearCameraPos = 0;
	const float farCameraPos = 50.0f;

	//�v���C���[�̏������W
	const VECTOR leftPlayerPos = VGet(-1, 0, 0);
	const VECTOR rightPlayerPos = VGet(1, 0, 0);
};