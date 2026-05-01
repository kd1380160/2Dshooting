#include "Result.h"
#include "../Scene.h"

void C_Result::Init()
{
}

void C_Result::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isClick)
		{
			isClick = true;
			SCENE_MGR.SetNowScene(SceneList::Title);
		}
	}
	else
	{
		isClick = false;
	}
}

void C_Result::Draw()
{
	
}
