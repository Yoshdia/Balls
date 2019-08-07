#include"DxLib.h"
#include "InputKey.h"
#include "Title.h"

Title::Title(DeepestSpawner* deepestSpawner, Score* score):
	Scene(deepestSpawner,score)
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
		deepestSpawner->ReStartDeepestObject();
		return sceneName::play;
	}
	return sceneName::noChange;
}
