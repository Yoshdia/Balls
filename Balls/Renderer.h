#pragma once

class ModelComponent;
#include <vector>
#include<unordered_map>

//モデルをロードし所有、描画するシングルトンクラス
class Renderer
{
public:
	static Renderer* GetInstance() { return renderer; }
	static void Create();
	static void Delete();

	//fileNameのモデルが既に読み込まれたかどうかを検索しそうでなかった場合読み込んでそのアドレスを返す
	int LoadModel(const std::string &fileName);
	void AddModel(ModelComponent* model);
	void RemoveModel(ModelComponent* model);
	void DrawModel();

	void ShutDown();
private:
	static Renderer* renderer;
	Renderer() {};
	
	//各Actorで生成されたModelComponentが追加される
	std::vector<class ModelComponent*>  modelComponents;
	//modelへのアドレス(解放を最後に行うためのvector)
	std::unordered_map<std::string, int> originalModel;
	//originalModelの複製品
	std::vector<int> duplicateModel;
};

