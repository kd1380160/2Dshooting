#include "UI.h"
#include"../Scene.h"
C_UI::C_UI()
{
	heartTex.Load("Assets/Image/Player/heart.png");
	heartBackTex.Load("Assets/Image/Player/heartBack.png");
}

C_UI::~C_UI()
{
	heartTex.Release();
	heartBackTex.Release();
}

void C_UI::Init()
{
	life = LIFE_MAX;
	isInvincible = false;
	for (int i = 0;i < LIFE_MAX;++i)
	{
		isFinishHeartAnim[i] = false;
		isDecreaseHeart[i] = false;
		heartAnimCnt[i] = 0;
	}
}

void C_UI::Update()
{
	
	if (!isInvincible)
	{
		if (SCENE.GetPlayer()->GetisInvincible())
		{
			isInvincible = true;
			life--;
			isDecreaseHeart[life] = true;
		}
	}
	else
	{
		if (!SCENE.GetPlayer()->GetisInvincible())
		{
			isInvincible = false;
		}
	}

	//life = SCENE.GetPlayer()->GetPlayerHp();
	for (int i = 0;i < LIFE_MAX;++i)
	{
		if (isDecreaseHeart[i]&&!isFinishHeartAnim[i])
		{
			heartAnimCnt[i]++;
			if (heartAnimCnt[i] >= 20)
			{
				isFinishHeartAnim[i] = true;
			}
		}
	}

	Math::Matrix scale, trans;

	for (int i = 0;i < LIFE_MAX;++i)
	{
		scale = Math::Matrix::CreateScale(HEART_SIZE, HEART_SIZE, 0);
		trans = Math::Matrix::CreateTranslation(heartPos[i].x, heartPos[i].y, 0);
		heartMat[i] = scale*trans;

		heartBackMat[i] = scale * trans;
	}
}

void C_UI::Draw()
{
	//ハートの背景
	for (int i = 0;i < LIFE_MAX;++i)
	{
		SHADER.m_spriteShader.SetMatrix(heartBackMat[i]);
		SHADER.m_spriteShader.DrawTex(&heartBackTex, Math::Rectangle{ 0,0,17,17 });
	}

	//ハート
	for (int i = 0;i < LIFE_MAX;++i)
	{
		SHADER.m_spriteShader.SetMatrix(heartMat[i]);
		SHADER.m_spriteShader.DrawTex(&heartTex, Math::Rectangle{ 17*(heartAnimCnt[i]/5),0,17,17});
	}
}
