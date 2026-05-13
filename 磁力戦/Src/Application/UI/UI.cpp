#include "UI.h"
#include"../Scene.h"
C_UI::C_UI()
{
	//heartTex.Load("Assets/Image/Player/heart.png");
	energyTex.Load("Assets/Image/Player/life.png");
	redEnergyTex.Load("Assets/Image/Player/RedLife.png");
	redEnergyBlockTex.Load("Assets/Image/Player/RedLifeBlock.png");
	SunTex.Load("Assets/Image/Effect/Sun.png");
	leftEnemyTex.Load("Assets/Image/UI/enemy.png");
	slashTex.Load("Assets/Image/UI/slash.png");
	hpTex.Load("Assets/Image/UI/hp.png");
}

C_UI::~C_UI()
{
	energyTex.Release();
	redEnergyTex.Release();
	redEnergyBlockTex.Release();
	SunTex.Release();
	leftEnemyTex.Release();
	slashTex.Release();
	hpTex.Release();
}

void C_UI::Init()
{
	life = LIFE_MAX;
	leftEnemyNum = 0;
	maxEnemyNum = 0;
	nextWave = 1;
	isInvincible = false;
	isShake = false;
	isRedBlockDisappear = false;
	isFirstAppear = false;
	canShowLeftEnemy = false;
	canCntUp = false;
	shakeLock = 0;
	enemyUpCnt = 0;
	enemyMaxUpCnt = 0;
	energyAlpha = 0.0f;
	leftEnemyAlpha = 0.0f;
	redEnergyBlockAlpha = 1.0f;
	sunAlpha = 1.0f;
	energyColor = { 1,1,1,energyAlpha };
	redEnergyBlockPos = { 159,-320 };
}

void C_UI::Update()
{
	//=========発表会用===========

	//体力MAX
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		life = LIFE_MAX;
		redEnergyBlockPos = { 159,-320 };
		isRedBlockDisappear = false;
	}

	//============================

	
	//体力ゲージの表示
	if (!isFirstAppear)
	{
		energyAlpha += 0.01f;
		if (energyAlpha >= 0.7f)
		{
			energyAlpha = 0.7f;
			isFirstAppear = true;
		}
	}

	//残り敵数の表示
	if (canShowLeftEnemy)
	{
		leftEnemyAlpha += 0.01f;
		if (leftEnemyAlpha >= 1.0f)
		{
			leftEnemyAlpha = 1.0f;
			canShowLeftEnemy = false;
		}
	}

	//残り敵数・MAX敵数のカウントアップ
	if (canCntUp)
	{
		if (leftEnemyNum < ENEMY_MGR.GetMaxEnemyWaveNum(nextWave))
		{
			enemyUpCnt++;
			if (enemyUpCnt >= 10)
			{
				leftEnemyNum++;
				enemyUpCnt = 0;
			}
		}
		else
		{
			canCntUp = false;
		}

		if (maxEnemyNum < ENEMY_MGR.GetMaxEnemyWaveNum(nextWave))
		{
			enemyMaxUpCnt++;
			if (enemyMaxUpCnt >= 3)
			{
				maxEnemyNum++;
				enemyMaxUpCnt = 0;
			}
		}
		else if(maxEnemyNum>ENEMY_MGR.GetMaxEnemyWaveNum(nextWave))
		{
			enemyMaxUpCnt++;
			if (enemyMaxUpCnt >= 3)
			{
				maxEnemyNum--;
				enemyMaxUpCnt = 0;
			}
		}
	}
	else
	{
		if (!ENEMY_MGR.GetIsFinishWave())
		{
			leftEnemyNum = ENEMY_MGR.GetLeftEnemyNum();
			maxEnemyNum = ENEMY_MGR.GetMaxEnemyWaveNum(nextWave);
		}
	}

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

	if (ENEMY_MGR.GetIsFinishWave4())
	{
		leftEnemyAlpha -= 0.01f;
		if (leftEnemyAlpha <= 0.0f)leftEnemyAlpha = 0.0f;
	}


	ShakeEnergy();

	Math::Matrix scale, trans;

	scale = Math::Matrix::CreateScale(ENERGY_SIZE_X, ENERGY_SIZE_Y, 0);
	trans = Math::Matrix::CreateTranslation(energyPos.x+shakeLock, energyPos.y+shakeLock, 0);
	energyMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(redEnergyBlockPos.x + shakeLock, redEnergyBlockPos.y + shakeLock, 0);
	redEnergyBlockMat = scale * trans;

	scale = Math::Matrix::CreateScale(0.6f, 0.6f, 0);
	trans = Math::Matrix::CreateTranslation(energyPos.x - 150 + shakeLock, energyPos.y + 4 + shakeLock, 0);
	hpMat = scale * trans;

	scale = Math::Matrix::CreateScale(1, 1, 0);
	trans = Math::Matrix::CreateTranslation(SunPos.x, SunPos.y, 0);
	SunMat = scale * trans;

	scale = Math::Matrix::CreateScale(0.5f, 0.5f, 0);
	trans = Math::Matrix::CreateTranslation(leftEnemyPos.x + shakeLock, leftEnemyPos.y + shakeLock, 0);
	leftEnemyMat = scale * trans;

	for (int i = 0;i < 5;++i)
	{
		if (i == 2)
		{
			scale = Math::Matrix::CreateScale(0.6f, 0.6f, 0);
		}
		else
		{
			scale = Math::Matrix::CreateScale(3.3f, 3.3f, 0);
		}

		if (i == 2)
		{
			trans = Math::Matrix::CreateTranslation(leftEnemyPos.x + i * 25 + 40 + shakeLock, leftEnemyPos.y  + shakeLock, 0);
		}
		else
		{
			trans = Math::Matrix::CreateTranslation(leftEnemyPos.x + i * 25 + 40 + shakeLock, leftEnemyPos.y - 4 + shakeLock, 0);
		}
		numberMat[i] = scale * trans;
	}
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

	
	SHADER.m_spriteShader.SetMatrix(hpMat);
	SHADER.m_spriteShader.DrawTex(&hpTex, Math::Rectangle{ 0,0,67,61 }, &energyColor);

	if (SCENE_MGR.GetNowScene() != SceneList::Tutorial)
	{
		color = { 1,1,1,leftEnemyAlpha };
		SHADER.m_spriteShader.SetMatrix(leftEnemyMat);
		SHADER.m_spriteShader.DrawTex(&leftEnemyTex, Math::Rectangle{ 0,0,150,61 }, &color);

		for (int i = 0;i < 5;++i)
		{
			SHADER.m_spriteShader.SetMatrix(numberMat[i]);

			if (i == 2)
			{
				SHADER.m_spriteShader.DrawTex(&slashTex, Math::Rectangle{ 0,0,47,64 }, &color);
			}
			else if (i == 0)
			{
				SHADER.m_spriteShader.DrawTex(SCENE_MGR.GetResult()->GetNumberTex(), Math::Rectangle{ leftEnemyNum / 10 * 6,0,6,11 }, &color);
			}
			else if (i == 1)
			{
				SHADER.m_spriteShader.DrawTex(SCENE_MGR.GetResult()->GetNumberTex(), Math::Rectangle{ leftEnemyNum % 10 * 6,0,6,11 }, &color);
			}
			else if (i == 3)
			{
				SHADER.m_spriteShader.DrawTex(SCENE_MGR.GetResult()->GetNumberTex(), Math::Rectangle{ maxEnemyNum / 10 * 6,0,6,11 }, &color);
			}
			else if (i == 4)
			{
				SHADER.m_spriteShader.DrawTex(SCENE_MGR.GetResult()->GetNumberTex(), Math::Rectangle{ maxEnemyNum % 10 * 6,0,6,11 }, &color);
			}
		}
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

