#include "Transition.h"
#include "../Scene.h"
void C_Transition::Init()
{
	alpha = 0.0f;
	
	isWhiteOut = false;
}

void C_Transition::Draw()
{
	if (!isTransition)return;
	Math::Color color = { 1.0f,1.0f,1.0f,alpha };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
	SHADER.m_spriteShader.DrawBox(0, 0, 640, 360, &color,true);
}

void C_Transition::Update()
{
	if (!isTransition)return;


	if (!isWhiteOut)
	{
		alpha += 0.02f;
		if (alpha >= 1.0f)
		{
			alpha = 1.0f;
			isWhiteOut = true;
			SCENE_MGR.SetNowScene(nextScene);
		}
	}
	else
	{
		cnt++;

		if (cnt > 50)
		{
			alpha -= 0.01f;
			if (alpha <= 0)
			{
				alpha = 0.0f;
				isTransition = false;
			}
		}
	}
}

void C_Transition::Start(SceneList next)
{
	Init();
	nextScene = next;
	isTransition = true;
}
