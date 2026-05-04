#include "Text.h"
#include "../../Scene.h"

C_Text::C_Text()
{
	shotTex.Load("Assets/Image/Game/Ute.png");
	waveTex.Load("Assets/Image/Game/Wave.png");
	finalTex.Load("Assets/Image/Game/Final.png");
}

C_Text::~C_Text()
{
	shotTex.Release();
	waveTex.Release();
	finalTex.Release();
}

void C_Text::Init()
{
	wavePos = { -150,50 };
	shotAlpha = 0.8f;
	shotAlphaAdd = 0.02f;
	waveAlpha = 0.0f;
	waveAlphaAdd = 0.02f;
	waveCnt = 0;
	nextWave = 0;
	isChangingWave = false;
	isUp = false;
	isFinishDirection = false;
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

	if (isChangingWave)
	{
		waveAlpha += waveAlphaAdd;
		if (waveAlpha >= 1.0f && !isUp)
		{
			waveAlpha = 1.0f;
			waveCnt++;
			if (waveCnt >= 100)
			{
				isUp = true;
				waveCnt = 0;
				waveAlphaAdd = -0.03f;
			}
		}

		if (isUp)
		{
			wavePos.y += 4;
			waveCnt++;
			if (waveAlpha <= 0.0f)
			{
				waveAlpha = 0.0f;

			}

			if (waveCnt >= 90)
			{
				isFinishDirection = true;
				isChangingWave = false;
			}

		}
	}

	Math::Matrix scale, trans;

	scale = Math::Matrix::CreateScale(7, 7, 1);
	trans = Math::Matrix::CreateTranslation(0, -100, 0);
	shotMat = scale * trans;

	scale = Math::Matrix::CreateScale(3, 3, 1);
	trans = Math::Matrix::CreateTranslation(wavePos.x, wavePos.y, 0);
	waveMat = scale * trans;

	if (nextWave != 5)
	{
		scale = Math::Matrix::CreateScale(15, 15, 1);
		trans = Math::Matrix::CreateTranslation(wavePos.x + 250, wavePos.y - 10, 0);
		numberMat = scale * trans;
	}
	else
	{
		scale = Math::Matrix::CreateScale(3, 3, 1);
		trans = Math::Matrix::CreateTranslation(wavePos.x + 330, wavePos.y , 0);
		numberMat = scale * trans;
	}
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


	if (isChangingWave)
	{
		color = { 1,1,1,waveAlpha };
		SHADER.m_spriteShader.SetMatrix(waveMat);
		SHADER.m_spriteShader.DrawTex(&waveTex, Math::Rectangle{ 0,0,107,61 }, &color);

		color = { 0.6,1,1,waveAlpha };
		SHADER.m_spriteShader.SetMatrix(numberMat);

		if (nextWave != 5)
		{
			SHADER.m_spriteShader.DrawTex(SCENE_MGR.GetNumberTex(), Math::Rectangle{ 6 * nextWave,0,6,11 }, &color);
		}
		else
		{
			color = { 1,0,0,waveAlpha };
			SHADER.m_spriteShader.DrawTex(&finalTex, Math::Rectangle{ 0,0,127,61 }, &color);
		}
	}
}

void C_Text::ChangeWave(int nextwave)
{
	Init();
	nextWave = nextwave;
	isChangingWave = true;
}
