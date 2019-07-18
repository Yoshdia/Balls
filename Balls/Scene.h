#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

#include "WallSpawner.h"
#include "Score.h"

//Scene���N���X
class Scene
{
public:
	Scene(WallSpawner* pSpawn, Score* pScore) { wallSpawner = pSpawn; score = pScore; };
	virtual ~Scene() {};
	//�X�V
	virtual void Update(float deltaTime) {};
	//�`��
	virtual void Render() {};
	//���ꂼ���Scene�ŕʃV�[���Ɉړ���������Ɩ��O���w��ł���
	virtual sceneName SceneChange() = 0;
protected:
	WallSpawner* wallSpawner;
	Score* score;
};