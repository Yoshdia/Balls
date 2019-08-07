#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

#include "DeepestSpawner.h"
#include "Score.h"

//Scene���N���X
class Scene
{
public:
	Scene(DeepestSpawner* pDeepestSpawn, Score* pScore) { deepestSpawner = pDeepestSpawn; score = pScore; };
	virtual ~Scene() {};
	//�X�V
	virtual void Update(float deltaTime) {};
	//�`��
	virtual void Render() {};
	//���ꂼ���Scene�ŕʃV�[���Ɉړ���������Ɩ��O���w��ł���
	virtual sceneName SceneChange() = 0;
protected:
	DeepestSpawner* deepestSpawner;
		Score* score;
};