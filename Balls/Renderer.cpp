#include "DxLib.h"
#include "Renderer.h"
#include "ModelComponent.h"

Renderer* Renderer::renderer = nullptr;

void Renderer::Create()
{
	if (!renderer)
	{
		renderer = new Renderer;
	}
}

void Renderer::Delete()
{
	delete renderer;
	renderer = nullptr;
}

int Renderer::LoadModel(const std::string & fileName)
{
	/*fileName�̃��f����originalModel���������Ă��Ȃ���
      �^�̏ꍇdupricateModel���̂��̃��f���A�h���X��Ԃ��A
      �U�̏ꍇ�V���ɓǂݍ���Ń��f���A�h���X���i�[����*/
	int modelId;
	int originId;
	auto iter = originalModel.find(fileName);
	if (iter != originalModel.end())
	{
		originId = iter->second;
	}
	else
	{
		originId = MV1LoadModel(fileName.c_str());
		originalModel.emplace(fileName.c_str(), originId);
	}

	modelId = MV1DuplicateModel(originId);
	duplicateModel.push_back(modelId);
	return modelId;
}

void Renderer::AddModel(ModelComponent * model)
{
	//����Model�̍X�V�������擾���A���̏������傫���l���������炻�̑O�ɑ}������
	int drawNumber = model->getProccesNumber();
	auto iter = modelComponents.begin();
	for (; iter != modelComponents.end(); ++iter)
	{
		int iterDrawNumber = (*iter)->getProccesNumber();
		if (drawNumber < iterDrawNumber ||
			drawNumber == iterDrawNumber)
		{
			break;
		}
	}
	modelComponents.insert(iter, model);
}

void Renderer::RemoveModel(ModelComponent * model)
{
	auto iter = std::find(modelComponents.begin(), modelComponents.end(), model);
	if (iter != modelComponents.end())
	{
		modelComponents.erase(iter);
	}
}

void Renderer::DrawModel()
{
	for (auto model : modelComponents)
	{
		model->DrawModel();
	}
}

void Renderer::ShutDown()
{
	//model�֘A�̉��
	for (auto model : originalModel)
	{
		MV1DeleteModel(model.second);
	}
	originalModel.clear();
	for (auto model : duplicateModel)
	{
		MV1DeleteModel(model);
	}
	duplicateModel.clear();
}
