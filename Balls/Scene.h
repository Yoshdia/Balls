#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

#include "WallSpawner.h"

//Scene���N���X
class Scene
{
public:
	Scene(WallSpawner* pSpawn) { wallSpawner = pSpawn; };
	virtual ~Scene() {};
	//�X�V
	virtual void Update(float deltaTime) {};
	//�`��
	virtual void Render() {};
	//���ꂼ���Scene�ŕʃV�[���Ɉړ���������Ɩ��O���w��ł���
	virtual sceneName SceneChange() = 0;
protected:
	WallSpawner* wallSpawner;
};