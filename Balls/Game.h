#pragma once

class Scene;
class Camera;
class Actor;
#include <vector>
#include"DxLib.h"
#include<unordered_map>

class ModelComponent;

//�Q�[���S�̂̏���
class Game
{
public:
	static Game *GetInstance() { return game; }

	//game�V���O���g���̐����Ɖ���֐�
	static void Create();
	static void Delete();
	
	char* GetAllInputKey() { return key; };

	//�S�̂̏������s���֐�
	void MainProcess();

	//�I�u�W�F�N�g���ǂ���̌����֐i�ނ̂��̗񋓑́B�ړ�����MovingDistance�ɒ��ڏ�Z����
	enum MoveDirection
	{
		Right = 1,
		Left = -1,
	};

	void AddActor(Actor *actor);
	void RemoveActor(Actor *actor);
	void ActorUpdate();
	void ShowActor();

	void ShutDown();

	//fileName�̃��f�������ɓǂݍ��܂ꂽ���ǂ����������������łȂ������ꍇ�ǂݍ���ł��̃A�h���X��Ԃ�
	int LoadModel(const std::string &fileName, const std::string & textureFileName);
	void AddModel(ModelComponent* model);
	void RemoveModel(ModelComponent* model);
	void DrawModel();

private:
	Game() {};
	static Game *game;

	Scene *scene;

	char* key;

	//��ʂ̍X�V�B�G���[���N�����ꍇ�Q�[�����I������
	bool ScreenUpdate();
	//�S�Ă̓��͏�Ԃ��擾
	void UpdateKey();
	//�V�[���`�F���W�BScene�̔h���N���X��������ƑJ�ڐ�����߂�
	void SceneChange();
	//���Ԍv��
	void DeltaTimeSet(DWORD *nowTick, DWORD *prevTick);

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
	//�X�V����Actor
	std::vector<class Actor*> upDateActors;
	//�ۗ�����Actor
	std::vector<class Actor*> pendingActors;
	//ModelComponent
	std::vector<class ModelComponent*>  modelComponents;//mModel 
	//model�̃A�h���X���i�[
	std::unordered_map<std::string, int> models; // �e�N�X�`���A�z�z�� 
	//����
	float deltaTime;
};