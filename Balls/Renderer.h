#pragma once

class ModelComponent;
#include <vector>
#include<unordered_map>

//���f�������[�h�����L�A�`�悷��V���O���g���N���X
class Renderer
{
public:
	static Renderer* GetInstance() { return renderer; }
	static void Create();
	static void Delete();

	//fileName�̃��f�������ɓǂݍ��܂ꂽ���ǂ����������������łȂ������ꍇ�ǂݍ���ł��̃A�h���X��Ԃ�
	int LoadModel(const std::string &fileName);
	void AddModel(ModelComponent* model);
	void RemoveModel(ModelComponent* model);
	void DrawModel();

	void ShutDown();
private:
	static Renderer* renderer;
	Renderer() {};
	
	//�eActor�Ő������ꂽModelComponent���ǉ������
	std::vector<class ModelComponent*>  modelComponents;
	//model�ւ̃A�h���X(������Ō�ɍs�����߂�vector)
	std::unordered_map<std::string, int> originalModel;
	//originalModel�̕����i
	std::vector<int> duplicateModel;
};

