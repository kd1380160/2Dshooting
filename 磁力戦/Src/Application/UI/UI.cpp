#include "UI.h"
#include"../Scene.h"
C_UI::C_UI()
{
	//heartTex.Load("Assets/Image/Player/heart.png");
	energyTex.Load("Assets/Image/Player/life.png");
	redEnergyTex.Load("Assets/Image/Player/RedLife.png");
	redEnergyBlockTex.Load("Assets/Image/Player/RedLifeBlock.png");
	SunTex.Load("Assets/Image/Effect/Sun.png");
}

C_UI::~C_UI()
{
	energyTex.Release();
	redEnergyTex.Release();
	redEnergyBlockTex.Release();
	SunTex.Release();
}

void C_UI::Init()
{
	life = LIFE_MAX;
	isInvincible = false;
	isShake = false;
	isRedBlockDisappear = false;
	shakeLock = 0;
	energyAlpha = 0.7f;
	redEnergyBlockAlpha = 1.0f;
	sunAlpha = 1.0f;
	energyColor = { 1,1,1,energyAlpha };
	redEnergyBlockPos = { 159,-300 };
}

void C_UI::Update()
{

	if (!isInvincible)
	{
		if (SCENE.GetPlayer()->GetisInvincible())
		{
			isInvincible = true;
			life--;
			isShake = true;
			isRedBlockDisappear = true;
			energyAlpha = 1.0f;
			redEnergyBlockPos.x -= 65;
		}
	}
	else
	{
		if (!SCENE.GetPlayer()->GetisInvincible())
		{
			isInvincible = false;
			energyAlpha = 0.7f;
		}
	}

	
	if (life ==1)
	{
		sunCnt++;
		if (sunCnt >= 10)
		{	
			sunAlpha = 0.0f;
			energyColor = { 3,3,3,energyAlpha };
		}
		if (sunCnt >= 20)
		{
			sunAlpha = 1.0f;
			energyColor = { 10,10.10,energyAlpha };
			sunCnt = 0;

		}
	}
	else
	{
		energyColor = { 3,3,3,energyAlpha };
	}

	if (isRedBlockDisappear)
	{
		redEnergyBlockAlpha -= 0.01f;
		if (redEnergyBlockAlpha <= 0.0f)
		{
			redEnergyBlockAlpha = 1.0f;
			isRedBlockDisappear = false;

		}
	}


	ShakeEnergy();

	Math::Matrix scale, trans;

	scale = Math::Matrix::CreateScale(ENERGY_SIZE_X, ENERGY_SIZE_Y, 0);
	trans = Math::Matrix::CreateTranslation(energyPos.x+shakeLock, energyPos.y+shakeLock, 0);
	energyMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(redEnergyBlockPos.x + shakeLock, redEnergyBlockPos.y + shakeLock, 0);
	redEnergyBlockMat = scale * trans;

	scale = Math::Matrix::CreateScale(1, 1, 0);
	trans = Math::Matrix::CreateTranslation(SunPos.x, SunPos.y, 0);
	SunMat = scale * trans;

}

void C_UI::Draw()
{
	Math::Color color;


	//色のブレンド方法の設定（加算合成）
	D3D.SetBlendState(BlendMode::Add);

	if (life == 1)
	{
		//太陽
		color = { 1,0,0,sunAlpha };

		SHADER.m_spriteShader.SetMatrix(SunMat);
		SHADER.m_spriteShader.DrawTex(&SunTex, Math::Rectangle(0, 0, 128, 128), &color);
	}
	//色のブレンド方法の設定（合成なし）
	D3D.SetBlendState(BlendMode::Alpha);



	SHADER.m_spriteShader.SetMatrix(energyMat);
	if (life == 1)
	{
		SHADER.m_spriteShader.DrawTex(&redEnergyTex, Math::Rectangle{ 96 * (4 - life),0,96,32 }, &energyColor);
	}
	else
	{
		SHADER.m_spriteShader.DrawTex(&energyTex, Math::Rectangle{ 96 * (4 - life),0,96,32 }, &energyColor);
	}

	if (isRedBlockDisappear)
	{
		color = { 3,0,0,redEnergyBlockAlpha };
		SHADER.m_spriteShader.SetMatrix(redEnergyBlockMat);
		SHADER.m_spriteShader.DrawTex(&redEnergyBlockTex, Math::Rectangle{ 0,0,17,32 }, &color);
	}
}

void C_UI::ShakeEnergy()
{
	if (!isShake)return;
	if (shakeCnt == 0)shakeLock = 4;
	shakeCnt++;
	if (shakeCnt % 3 == 0)
	{
		shakeLock *= -1;
		if (shakeCnt == 12)
		{
			shakeLock = 0;
			shakeCnt = 0;
			isShake = false;
			
		}
	}
}
