#include "DxLib.h"
#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "WallSetter.h"

Game *Game::game = NULL;

void Game::Create()
{
	if (!game)
	{
		game = new Game;
	}
}

void Game::Delete()
{
	delete game;
	game = NULL;
}

char * Game::GetAllInputKey()
{
	return key;
}

void Game::Update()
{
	//dxlib��������
	if (DxLib_Init() == -1)
	{
		return;
	}
	//�X�N���[�����[�h�̕ύX�Btrue=�E�B���h�E���[�h
	ChangeWindowMode(true);
	//��ʃ��[�h�̕ύX
	SetGraphMode(ScreenWidth, ScreenHeight, 32);
	//�`���O���t�B�b�N�̈�𗠂�
	SetDrawScreen(DX_SCREEN_BACK);
	//�L�[���̎擾�Ə�����
	key = new char[ControlKeyNum];
	SetUpdateKey();

	//�ŏ��̃V�[�����쐬
	scene = new Play;

	//�J�����̎���͈͂�ݒ�
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//�J�����̏ꏊ��ݒ�
	SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
	//���C�g�̏ꏊ���J�����Ɠ����ʒu�ɐݒ�
	SetLightPosition(CameraPos);
	//���C�g�̌������J��������0,0,0������悤�ɐݒ�
	SetLightDirection(VGet(0, 0, 1));

	int *playerModel;
	playerModel = new int;
	*playerModel=MV1LoadModel("model/whiteBall.mqo");
	int *playerModelTexture;
	playerModelTexture = new int;
	*playerModelTexture = NULL;
	*playerModelTexture = LoadGraph("model/grade.JPG");

	Player *leftPlayer = new Player(leftPlayerPos, Game::MoveDirection::Left,KEY_INPUT_SPACE,*playerModel, *playerModelTexture);
	Player *rightPlayer = new Player(rightPlayerPos, Game::MoveDirection::Right,KEY_INPUT_RETURN,*playerModel, *playerModelTexture);

	WallSetter *wallSetter = new WallSetter;

	wallSetter->SetWall();
	//��ʍX�V���ɃG���[���N���������AEscape�L�[�������ꂽ��I��
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE] == 0)
	{
		SetUpdateKey();

		scene->Update();
		leftPlayer->Update();
		rightPlayer->Update();
		wallSetter->Update();

		scene->Render();
		leftPlayer->Render();
		rightPlayer->Render();
		wallSetter->Render();

		SceneChange();
	}

	delete[] key;
	delete scene;
	delete leftPlayer;
	delete rightPlayer;
	delete wallSetter;

	MV1DeleteModel(*playerModel);
	delete playerModel;
	playerModel = NULL;
	DeleteGraph(*playerModelTexture);
	delete playerModelTexture;
	playerModelTexture = NULL;

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return;
}

bool Game::ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//��ʂ̗��y�[�W�̓��e��\�y�[�W�ɔ��f����
	if (ScreenFlip() != 0) return false;
	//��ʂ�������
	if (ClearDrawScreen() != 0) return false;
	return true;
}

void Game::SetUpdateKey()
{

	//�S�Ă̓��͏�Ԃ�tmpKey�Ɋi�[
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	//num�Ԗڂ̃L�[��������Ă�������Z
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			key[num]++;
		}
		else
		{
			//������Ă��Ȃ��L�[��0�ɂ���
			key[num] = 0;
		}
	}
}

void Game::SceneChange()
{
	sceneName nextScene = scene->SceneChange();
	switch (nextScene)
	{
	case(sceneName::title):
		delete scene;
		scene = new Title;
		break;
	case(sceneName::play):
		delete scene;
		scene = new Play;
		break;
	case(sceneName::clear):
		scene = new Clear;
		break;
	}
}
