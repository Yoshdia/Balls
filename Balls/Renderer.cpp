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
	/*fileNameのモデルをoriginalModelが所持していないか
      真の場合dupricateModel内のそのモデルアドレスを返し、
      偽の場合新たに読み込んでモデルアドレスを格納する*/
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
	//そのModelの更新順序を取得し、その順序より大きい値を見つけたらその前に挿入する
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
	//model関連の解放
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
