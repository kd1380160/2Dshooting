#include "Tutorial.h"
#include"../Scene.h"

C_Tutorial::C_Tutorial()
{
	explainBackTex.Load("Assets/Image/Tutorial/explainBack.png");
	tutorialTex.Load("Assets/Image/Tutorial/tutorial.png");
	canInhaleTex.Load("Assets/Image/Tutorial/canInhale.png");
	cantInhaleTex.Load("Assets/Image/Tutorial/cantInhale.png");
	goNextPageTex.Load("Assets/Image/Tutorial/goNext.png");
	downArrowTex.Load("Assets/Image/Tutorial/DownArrow.png");
	lockOnTex.Load("Assets/Image/Tutorial/lockon.png");
	shotTex.Load("Assets/Image/Tutorial/fireLclick.png");

}

void C_Tutorial::Init()
{	
	isLClick = true;
	isWindow = false;
	isFinishWindow = false;
	isPage1 = false;
	isPage2 = false;
	canStartSceneChange = false;
	windowSize = 0.1;
	purgeCnt = 0;
	sceneChangeCnt = 0;
	page = WindowPage::page1;
}

void C_Tutorial::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isLClick)
		{
			isLClick = true;

			if (page == WindowPage::page1)
			{
				isWindow = false;
				isPage1 = false;
				isFinishPage1 = true;
				windowSize = 0.1;
				page = WindowPage::page2;
			}
			else if (page == WindowPage::page2)
			{
				if (isWindow)
				{
					if (!isFinishWindow)
					{
						isWindow = false;
						isFinishWindow = true;
						isFinishPage2 = true;
					}
				}
			}

		}
	}
	else
	{
		isLClick = false;
	}

	if (BULLET_MGR.GetMagBulletHaveAmount() >= 15 && !isFinishPage2)
	{
		isPage2 = true;
		isWindow = true;
	}


	if (!isPage1&&!isFinishPage1)
	{
		if (SCENE.GetPlayer()->GetCanStartGame())
		{
			isPage1 = true;
			isWindow = true;
		}
	}
	else
	{
		if (windowSize < 1.0f)
		{
			windowSize += 0.07f;
			if (windowSize >= 1.0f)
			{
				windowSize = 1.0f;
			}
		}
	}

	if (page == WindowPage::page2 && isWindow)
	{
		lockOnBlinkingCnt++;
	}


	//敵を倒した後残りの磁力弾をパージ
	if (ENEMY_MGR.GetIsEnemy1Dead())
	{
		purgeCnt++;
		if (purgeCnt >= 60)
		{
			BULLET_MGR.ShotMagBulletTutorial();
			canStartSceneChange = true;
		}

		if (canStartSceneChange)
		{
			sceneChangeCnt++;

			if (sceneChangeCnt == 60)
			{
				SCENE_MGR.GetText()->ChangeWave(1);
			}

			if (SCENE_MGR.GetText()->GetIsFinishDirection())
			{
				SCENE_MGR.SetNowScene(Game);
			}
		}
	}



	Math::Matrix trans, scale,rotate;

	//説明ウィンドウ
	trans = Math::Matrix::CreateTranslation(0, 0, 0);
	scale = Math::Matrix::CreateScale(4 * windowSize, 4*windowSize, 1);
	explainBackMat = scale * trans;

	//上部のチュートリアル表示
	trans = Math::Matrix::CreateTranslation(0, 190, 0);
	scale = Math::Matrix::CreateScale(2 * windowSize, 2 * windowSize, 1);
	tutorialMat = scale * trans;

	//吸える説明
	trans = Math::Matrix::CreateTranslation(50, 70, 0);
	scale = Math::Matrix::CreateScale(0.8f * windowSize, 0.8f * windowSize, 1);
	canInhaleMat = scale * trans;

	//吸えない説明
	trans = Math::Matrix::CreateTranslation(65, -80, 0);
	cantInhaleMat = scale * trans;

	//弾(吸える)
	trans = Math::Matrix::CreateTranslation(-150, 70, 0);
	scale = Math::Matrix::CreateScale(5.0f * windowSize, 5.0f * windowSize, 1);
	canInhaleBulletMat = scale * trans;

	//弾(吸えない)
	trans = Math::Matrix::CreateTranslation(-150, -80, 0);
	cantInhaleBulletMat = scale * trans;

	//次のページへ
	trans = Math::Matrix::CreateTranslation(115, -200, 0);
	scale = Math::Matrix::CreateScale(0.6 * windowSize, 0.6 * windowSize, 1);
	goNextPageMat = scale * trans;

	//敵の説明(非ロックオン)
	trans = Math::Matrix::CreateTranslation(-150, -70, 0);
	scale = Math::Matrix::CreateScale(2.6f * windowSize, -2.6f * windowSize, 1);
	enemy1Mat[0] = scale * trans;

	//敵の説明(被ロックオン)
	trans = Math::Matrix::CreateTranslation(150, -70, 0);
	scale = Math::Matrix::CreateScale(2.6f * windowSize, -2.6f * windowSize, 1);
	enemy1Mat[1] = scale * trans;

	//ロックオン
	scale = Math::Matrix::CreateScale(4.2f * windowSize, 4.2f * windowSize, 1);
	lockonMat = scale * trans;

	//矢印
	rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
	trans = Math::Matrix::CreateTranslation(0, -70, 0);
	scale = Math::Matrix::CreateScale(1.5 * windowSize, 1.5 * windowSize, 1);
	downArrowMat = scale * rotate * trans;

	//ロックオン説明
	trans = Math::Matrix::CreateTranslation(0, 60, 0);
	scale = Math::Matrix::CreateScale(0.9 * windowSize, 0.9 * windowSize, 1);
	lockonTextMat = scale * trans;

	//左クリックで発射
	trans = Math::Matrix::CreateTranslation(0, 60, 0);
	scale = Math::Matrix::CreateScale(1.5f * windowSize, 1.5f * windowSize, 1);
	shotMat = scale * trans;

}

void C_Tutorial::Draw()
{
	Math::Color col;

	//左クリックで発射！
	if (ENEMY_MGR.GetIsEnemy1Lockon())
	{
		col = { 1.0f,1.0f,1.0f,0.7f };
		SHADER.m_spriteShader.SetMatrix(shotMat);
		SHADER.m_spriteShader.DrawTex(&shotTex, Math::Rectangle{ 0,0,370,71 }, &col);
	}

	if (!isFinishWindow && isWindow)
	{
		col = { 1,1,1,0.7f };
		//説明ウィンドウ
		SHADER.m_spriteShader.SetMatrix(explainBackMat);
		SHADER.m_spriteShader.DrawTex(&explainBackTex, Math::Rectangle{ 0,0,128,128 }, &col);


		//上部のチュートリアル表示
		col = { 0.0f,0.0f,0.0f,1.0f };
		SHADER.m_spriteShader.SetMatrix(tutorialMat);
		SHADER.m_spriteShader.DrawTex(&tutorialTex, Math::Rectangle{ 0,0,184,64 }, &col);

		//次のページへ
		col = { 0,0,0,1.0f };
		SHADER.m_spriteShader.SetMatrix(goNextPageMat);
		SHADER.m_spriteShader.DrawTex(&goNextPageTex, Math::Rectangle{ 0,0,384,71 }, &col);

		if (page == WindowPage::page1)
		{
			//吸える説明
			col = { 0.0f,0.0f,0.0f,1.0f };
			SHADER.m_spriteShader.SetMatrix(canInhaleMat);
			SHADER.m_spriteShader.DrawTex(&canInhaleTex, Math::Rectangle{ 0,0,370,71 }, &col);

			col = { 1,1,1,1.0f };
			SHADER.m_spriteShader.SetMatrix(canInhaleBulletMat);
			SHADER.m_spriteShader.DrawTex(BULLET_MGR.GetMagBulletTex(), Math::Rectangle{ 0,0,16,16 }, &col);

			//吸えない説明
			col = { 0.0f,0.0f,0.0f,1.0f };
			SHADER.m_spriteShader.SetMatrix(cantInhaleMat);
			SHADER.m_spriteShader.DrawTex(&cantInhaleTex, Math::Rectangle{ 0,0,410,71 }, &col);
			col = { 1,1,1,1.0f };
			SHADER.m_spriteShader.SetMatrix(cantInhaleBulletMat);
			SHADER.m_spriteShader.DrawTex(BULLET_MGR.GetBossBulletTex(), Math::Rectangle{ 0,0,16,16 }, &col);
		}
		else if (page == WindowPage::page2)
		{
			//敵（非ロックオン）
			col = { 2.0f,2.0f,2.0f,1.0f };
			SHADER.m_spriteShader.SetMatrix(enemy1Mat[0]);
			SHADER.m_spriteShader.DrawTex(ENEMY_MGR.GetEnemy1Tex(), Math::Rectangle{0,0,64,64}, &col);

			//敵（被ロックオン）
			col = { 2.0f,2.0f,2.0f,1.0f };
			SHADER.m_spriteShader.SetMatrix(enemy1Mat[1]);
			SHADER.m_spriteShader.DrawTex(ENEMY_MGR.GetEnemy1Tex(), Math::Rectangle{ 0,0,64,64 }, &col);

			if (lockOnBlinkingCnt >= 7)
			{
				col = { 2,0,0,1 };
			}
			if (lockOnBlinkingCnt >= 14)
			{
				lockOnBlinkingCnt = 0;
				col = { 20,0,0,1 };
			}
			SHADER.m_spriteShader.SetMatrix(lockonMat);
			SHADER.m_spriteShader.DrawTex(ENEMY_MGR.GetLockOnTex(), Math::Rectangle{ 0,0,17,17 }, &col);

			//下矢印
			col = { 0.0f,0.0f,0.0f,1.0f };
			SHADER.m_spriteShader.SetMatrix(downArrowMat);
			SHADER.m_spriteShader.DrawTex(&downArrowTex, Math::Rectangle{ 0,0,61,67 }, &col);
		
			//ロックオンの説明
			col = { 1.0f,1.0f,1.0f,1.0f };
			SHADER.m_spriteShader.SetMatrix(lockonTextMat);
			SHADER.m_spriteShader.DrawTex(&lockOnTex, Math::Rectangle{ 0,0,384,117 }, &col);
		}
	}

	
}

void C_Tutorial::Release()
{
	explainBackTex.Release();
	tutorialTex.Release();
	canInhaleTex.Release();
	cantInhaleTex.Release();
	goNextPageTex.Release();
	downArrowTex.Release();
	lockOnTex.Release();
	shotTex.Release();
}
