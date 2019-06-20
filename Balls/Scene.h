#pragma once

enum sceneName
{
	noChange,
	title,
	play,
	clear,
};

//Scene���N���X
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	//�X�V
	virtual void Update() {};
	//�`��
	virtual void Render() {};
	//���ꂼ���Scene�ŕʃV�[���Ɉړ���������Ɩ��O���w��ł���
	virtual sceneName SceneChange(char* key) = 0;
};