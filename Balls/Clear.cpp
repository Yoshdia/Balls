#include"DxLib.h"
#include "Clear.h"
#include "InputKey.h"



Clear::Clear(WallSpawner* wallSpawn, Score* score):
	Scene(wallSpawn,score)
{
}


Clear::~Clear()
{
}

void Clear::Update(float deltaTime)
{
}

void Clear::Render()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Clear");
}

sceneName Clear::SceneChange()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		//�S�Ă̕ǂ��N���A����
		wallSpawner->WallClear();
		return sceneName::title;
	}
	return sceneName::noChange;
}

