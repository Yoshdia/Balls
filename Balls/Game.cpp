#include "DxLib.h"
#include "InputKey.h"
#include "ActorManager.h"
#include "Renderer.h"
#include "Collider.h"
#include "GameSpeedManager.h"

#include "Scene.h"
#include "Player.h"
#include "Title.h"
#include "Play.h"
#include "Clear.h"

#include "Score.h"
#include "EffectFactory.h"

#include "DeepestSpawner.h"
//DeltaTime�̌v���ɕK�v
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") 




void Game::MainProcess()
{
	//Dxlib����������
	if (DxLib_Init() == -1) { return; }
	DxlibWindowSetting();
	DxlibCameraSetting();
	DxlibLightSetting();

	CreateSingleTons();
	CreateFirstActors();

	//�ŏ��̃V�[�����쐬
	scene = new Play(deepestSpawner, leftPlayer,rightPlayer,score);

	//deltaTime�̌v��
	DWORD nowTick, prevTick;
	prevTick = timeGetTime();

	float boxHeight = ScreenHeight / 3.0f;

	//��ʍX�V���ɃG���[���N���������AEscape�L�[�������ꂽ��I��
	while (ScreenUpdate() && InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_ESCAPE] == 0)
	{
		DrawBox(0, 0, (float)ScreenWidth, boxHeight*3.0f, GetColor(150,150,150), TRUE);
		DrawBox(0, 0, (float)ScreenWidth, boxHeight*2.0f, GetColor(100,100,100), TRUE);
		DrawBox(0, 0, (float)ScreenWidth, boxHeight*1.0f, GetColor(50,50,50), TRUE);

		DeltaTimeSet(nowTick, prevTick);
				
		InputKey::GetInstance()->UpdateKey();
		ActorManager::GetInstance()->ActorUpdate(deltaTime);

		scene->Update(deltaTime);

		Renderer::GetInstance()->DrawModel();
		scene->Render();

		SceneChange();
	}

	delete score;
	score = nullptr;
	delete scene;
	scene = nullptr;

	ShutDown();
	DeleteLightHandleAll();
	//Dxlib�̏I��
	DxLib_End();

	return;
}

void Game::DxlibWindowSetting()
{
	//�X�N���[�����[�h�̕ύX�Btrue=�E�B���h�E���[�h
	ChangeWindowMode(true);
	//��ʃ��[�h�̕ύX
	SetGraphMode(ScreenWidth, ScreenHeight, 32);
	//�`���O���t�B�b�N�̈�𗠂�
	SetDrawScreen(DX_SCREEN_BACK);
}

void Game::DxlibCameraSetting()
{
	//�J�����̎���͈͂�ݒ�
	SetCameraNearFar(nearCameraPos, farCameraPos);
	//�J�����̏ꏊ��ݒ�
	//SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(0, 0, 0));
	SetCameraPositionAndAngle(CameraPos, 0.3, 0, 0.1);
}

void Game::DxlibLightSetting()
{
	//���C�g�̌�����ݒ�
	SetLightDirection(VGet(0, -1, 2));
	//int secondLight = CreateDirLightHandle(VGet(1,-1,2));
	//int thirdLight = CreateDirLightHandle(VGet(-1, -1, 2));
}

void Game::CreateSingleTons()
{
	InputKey::GetInstance()->Create();
	ActorManager::GetInstance()->Create();
	Renderer::GetInstance()->Create();
	GameSpeedManager::GetInstance()->Create();
	EffectFactory::GetInstance()->Create();
	Collider::GetInstance()->Create();
}

void Game::DeleteSingleTons()
{
	ActorManager::GetInstance()->ShutDown();
	ActorManager::Delete();
	Renderer::GetInstance()->ShutDown();
	Renderer::GetInstance()->Delete();
	Collider::GetInstance()->ShutDown();
	Collider::GetInstance()->Delete();
	GameSpeedManager::GetInstance()->Delete();
	EffectFactory::GetInstance()->Delete();
}

void Game::CreateFirstActors()
{
	deepestSpawner = new DeepestSpawner;
	score = new Score;
	leftPlayer=new Player(leftPlayerPos, Game::MoveDirection::Left, KEY_INPUT_SPACE);
	rightPlayer=new Player(rightPlayerPos, Game::MoveDirection::Right, KEY_INPUT_RETURN);
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

void Game::SceneChange()
{
	sceneName nextScene = scene->SceneChange();
	switch (nextScene)
	{
	case(sceneName::title):
		delete scene;
		scene = new Title(deepestSpawner, leftPlayer,rightPlayer,score);
		break;
	case(sceneName::play):
		delete scene;
		scene = new Play(deepestSpawner, leftPlayer, rightPlayer, score);
		break;
	case(sceneName::clear):
		scene = new Clear(deepestSpawner, leftPlayer, rightPlayer, score);
		break;
	}
}

void Game::DeltaTimeSet(DWORD& nowTick, DWORD& prevTick)
{
	nowTick = timeGetTime();
	DWORD mTicks = DWORD(nowTick - prevTick);
	prevTick = timeGetTime();

	deltaTime = mTicks / 1000.0f;
	prevTick = nowTick;

	if (deltaTime >= 0.07f)
	{
		deltaTime = 0.07f;
	}
}

void Game::ShutDown()
{
	DeleteSingleTons();
	DxLib::DxLib_End();
}

VECTOR operator*(const VECTOR& vec, const float& flo)
{
	VECTOR vector;
	vector = VGet(vec.x*flo, vec.y*flo, vec.z*flo);
	return vector;
}

VECTOR operator*(const VECTOR & vec, const VECTOR & multi)
{
	VECTOR vector;
	vector = VGet(vec.x*multi.x, vec.y*multi.y, vec.z*multi.z);
	return vector;
}
