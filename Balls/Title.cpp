#include"DxLib.h"
#include "InputKey.h"
#include "Title.h"

Title::Title(WallSpawner* wallSpawn):
	Scene(wallSpawn)
{
}

Title::~Title()
{
}

void Title::Update(float deltaTime)
{
	
}

void Title::Render()
{
	DrawFormatString(0,0,GetColor(255,255,255),"Title");
}

sceneName Title::SceneChange()
{
	if (InputKey::GetInstance()->GetAllInputKey()[KEY_INPUT_0] == 1)
	{
		return sceneName::play;
	}
	return sceneName::noChange;
}
