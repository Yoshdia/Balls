#pragma once

class Scene;
class Camera;
#include"DxLib.h"

class BoxColliderComponent;
class SphereColliderComponent;
class DeepestSpawner;
class Score;

//�Q�[���S�̂̏���
class Game
{
public:
	Game() {};

	//�S�̂̏������s���֐�
	void MainProcess();

	//�I�u�W�F�N�g���ǂ���̌����֐i�ނ̂��̗񋓑́B�ړ�����MovingDistance�ɒ��ڏ�Z����
	enum MoveDirection
	{
		Right = 1,
		Left = -1,
	};

	void ShutDown();

private:
	Scene *scene;

	//Dxlib�֐��ɂ��邻�ꂼ��̐ݒ���s���֐�
	void DxlibWindowSetting();
	void DxlibCameraSetting();
	void DxlibLightSetting();

	//�V���O���g���N���X�̐����Ɖ��
	void CreateSingleTons();
	void DeleteSingleTons();

	//�ŏ��ɓo�ꂷ��Actor�B�𐶐�����֐�
	void CreateFirstActors();

	//��ʂ̍X�V�B�G���[���N�����ꍇ�Q�[�����I������
	bool ScreenUpdate();

	//�V�[���`�F���W�BScene�̔h���N���X��������ƑJ�ڐ�����߂�
	void SceneChange();
	//���Ԍv��
	void DeltaTimeSet(DWORD &nowTick, DWORD &prevTick);

	//�X�N���[���T�C�Y
	const int ScreenWidth = 1080;
	const int ScreenHeight = 900;

	//�J�����̍��W
	const VECTOR CameraPos = VGet(0, 5, -10);
	//�J�����̎���͈�
	const float nearCameraPos = 1;
	const float farCameraPos = 1000;
	const VECTOR LightPos = CameraPos;

	//�v���C���[�̏������W
	const VECTOR leftPlayerPos = VGet(-1, 0, 0);
	const VECTOR rightPlayerPos = VGet(1, 0, 0);

	DeepestSpawner* deepestSpawner;
	 Score* score;

	//����
	float deltaTime;
};

//VECTOR��float�̏�Z���ʂ�Ԃ�
VECTOR operator*(const VECTOR vec, const float flo);