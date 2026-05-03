#include "Text.h"
#include "../../Scene.h"

C_Text::C_Text()
{
	shotTex.Load("Assets/Image/Game/Ute.png");
	
}

C_Text::~C_Text()
{
	shotTex.Release();
}

void C_Text::Init()
{
	shotAlpha = 0.8f;
	shotAlphaAdd = 0.02f;
}

void C_Text::Update()
{

	if (SCENE_MGR.GetNowWave() == WaveList::Boss)
	{
		if (ENEMY_MGR.GetBossFinisher())
		{
			shotAlpha -= shotAlphaAdd;
			if (shotAlpha >= 0.8f)
			{
				shotAlpha = 0.8f;
				shotAlphaAdd *= -1;
			}
			else if (shotAlpha <= 0.2f)
			{
				shotAlpha = 0.2f;
				shotAlphaAdd *= -1;
			}
		}
	}
	Math::Matrix scale, trans;

	scale = Math::Matrix::CreateScale(7, 7, 1);
	trans = Math::Matrix::CreateTranslation(0, -100, 0);
	shotMat = scale * trans;
}

void C_Text::Draw()
{
	Math::Color color;


	if (SCENE_MGR.GetNowWave() == WaveList::Boss)
	{
		if (ENEMY_MGR.GetBossFinisher())
		{
			color = { 1,1,1,shotAlpha };
			SHADER.m_spriteShader.SetMatrix(shotMat);
			SHADER.m_spriteShader.DrawTex(&shotTex, Math::Rectangle{ 0,0,140,71 }, &color);
		}
	}
}
