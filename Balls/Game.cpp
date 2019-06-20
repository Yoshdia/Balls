#include "DxLib.h"
#include "Game.h"
#include "Scene.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"
#include "Camera.h"


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

bool Game::ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//��ʂ̗��y�[�W�̓��e��\�y�[�W�ɔ��f����
	if (ScreenFlip() != 0) return false;
	//��ʂ�������
	if (ClearDrawScreen() != 0) return false;
	return true;
}

void Game::SetUpdateKey(char * control)
{
	//���݂̓��͏�Ԃ�tmpKey�ɃR�s�[
	char tmpKey[256];

	//�S�Ă̓��͏�Ԃ�tmpKey�Ɋi�[
	GetHitKeyStateAll(tmpKey);

	//num�Ԗڂ̃L�[��������Ă�������Z
	for (int num = 0; num < ControlKeyNum; num++)
	{
		if (tmpKey[num] != 0)
		{
			control[num]++;
		}
		else
		{
			//������Ă��Ȃ��L�[��0�ɂ���
			control[num] = 0;
		}
	}
}

void Game::SceneChange(char * key)
{
	sceneName nextScene= scene->SceneChange(key);
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
	char* key=new char[ControlKeyNum];
	SetUpdateKey(key);
	
    scene = new Play;
	camera = new Camera;

	//��ʍX�V���ɃG���[���N���������AEscape�L�[�������ꂽ��I��
	while (ScreenUpdate() && key[KEY_INPUT_ESCAPE]==0)
	{
		camera->Update();
		SetUpdateKey(key);
		scene->Update();
		scene->Render();
		SceneChange(key);
	}

	delete[] key;
	delete scene;
	delete camera;

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return;
}
