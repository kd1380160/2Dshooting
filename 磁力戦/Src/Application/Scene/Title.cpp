#include "Title.h"
#include "../Scene.h"
#include"../Transition/Transition.h"

C_Title::C_Title()
{
	MAGTex.Load("Assets/Image/Title/MAG.png");
	LOCKONTex.Load("Assets/Image/Title/LOCKON.png");
	startTex.Load("Assets/Image/Title/start.png");
	wTex.Load("Assets/Image/Title/W.png");
	aTex.Load("Assets/Image/Title/A.png");
	sTex.Load("Assets/Image/Title/S.png");
	dTex.Load("Assets/Image/Title/D.png");
	wPressTex.Load("Assets/Image/Title/Wpress.png");
	aPressTex.Load("Assets/Image/Title/Apress.png");
	sPressTex.Load("Assets/Image/Title/Spress.png");
	dPressTex.Load("Assets/Image/Title/Dpress.png");

	startTexAlpha = 1.0f;
	alphaAdd = 0.03f;
	isClick = true;
}

void C_Title::Init()
{
	isClick = true;
	isChangeScene = false;
	isFinishTransition = false;
	startTexAlpha = 1.0f;
	bulletAlpha = 0.4f;
	alphaAdd = 0.02f;
	titleCnt = 0;
	transitionCnt = 0;

	for (int i = 0;i < BULLET_MAX;++i)
	{
		bulletPos[i] = { (float)(rand() % 1280 - 610),(float)(rand() % 710 - 330) };
		bulletMove[i] = { (float)(rand() % 3 - 1),(float)((rand() % 31 - 15 )/10.0f)};
		bulletSize[i] = (rand() % 10) / 10.0f + 1.5f;
		boostCnt[i] = 0;
	}

}

void C_Title::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!isEnter_Debug)
		{
			isEnter_Debug = true;
			if (canStartGame_Debug)
			{
				canStartGame_Debug = false;
			}
			else
			{
				canStartGame_Debug = true;
			}
		}
	}
	else
	{
		isEnter_Debug = false;
	}


	if (!TRANSITION.GetIsTransition())
	{
		if (canStartGame_Debug)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				if (!isClick)
				{
					isClick = true;
					if (!isChangeScene)
					{
						isChangeScene = true;
					}

				}
			}
			else
			{
				isClick = false;
			}
		}

		if (GetAsyncKeyState('W') & 0x8000)
		{
			isWpress = true;
			if (!isW)
			{
				isW = true;
				for (int i = 0;i < BULLET_MAX;++i)
				{
					bulletMove[i].y += 3;
				}
			}
		}
		else
		{
			isW = false;
			isWpress = false;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			isApress = true;
			if (!isA)
			{
				isA = true;
				for (int i = 0;i < BULLET_MAX;++i)
				{
					bulletMove[i].x -= 3;
				}
			}
		}
		else
		{
			isA = false;
			isApress = false;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			isSpress = true;
			if (!isS)
			{
				isS = true;
				for (int i = 0;i < BULLET_MAX;++i)
				{
					bulletMove[i].y -= 3;
				}
			}
		}
		else
		{
			isS = false;
			isSpress = false;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			isDpress = true;
			if (!isD)
			{
				isD = true;
				for (int i = 0;i < BULLET_MAX;++i)
				{
					bulletMove[i].x += 3;
				}
			}
		}
		else
		{
			isD = false;
			isDpress = false;
		}

		titleCnt++;
	
		if (isChangeScene)
		{
			startTexAlpha -= 0.05f;
			bulletAlpha -= 0.01f;
			if (bulletAlpha <= 0)
			{
				bulletAlpha = 0.0f;
			}

			if (startTexAlpha <= 0.0f)
			{
				startTexAlpha = 0.0f;
				transitionCnt++;
				if (transitionCnt >= 90)
				{

					SCENE_MGR.SetNowScene(SceneList::Tutorial);
					//SCENE_MGR.SetNowScene(SceneList::Game);
				}
			}
		}


		for (int i = 0; i < BULLET_MAX; i++) {
			// マウスと弾の距離を計算
			float dx = SCENE.GetMousePos().x - bulletPos[i].x;
			float dy = SCENE.GetMousePos().y - bulletPos[i].y;
			float dist = sqrt(dx * dx + dy * dy);

			if (dist < 140) { // マウスから150ピクセル以内なら
				// ほんの少しだけマウスの方へ加速させる（磁力）
				bulletMove[i].x += dx * 0.001f;
				bulletMove[i].y += dy * 0.001f;
			}
		}
	}



	//弾の更新
	for (int i = 0;i < BULLET_MAX;++i)
	{
		bulletPos[i] += bulletMove[i];
		if (bulletPos[i].x <= -630 || bulletPos[i].x >= 630)
		{
			bulletMove[i].x *= -1;
		}
		if (bulletPos[i].y <= -350 || bulletPos[i].y >= 350)
		{
			bulletMove[i].y *= -1;
		}

		if (bulletMove[i].x > 2.0f)
		{
			bulletMove[i].x -= 0.1f;
		}
		else if (bulletMove[i].x < -2.0f)
		{
			bulletMove[i].x += 0.1f;
		}

		if (bulletMove[i].y > 2.0f)
		{
			bulletMove[i].y -= 0.1f;
		}
		else if (bulletMove[i].y < -2.0f)
		{
			bulletMove[i].y += 0.1f;
		}


	}

	float textscale = 1.0f + 0.05f * sin(titleCnt * 0.05f);
	Math::Matrix trans;
	Math::Matrix scale;

	trans = Math::Matrix::CreateTranslation(-300, 170, 0);
	scale = Math::Matrix::CreateScale(2.3, 2.3, 1);
	MAGMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(200, 170, 0);
	scale = Math::Matrix::CreateScale(2.3, 2.3, 1);
	LOCKONMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(0, -100, 0);
	scale = Math::Matrix::CreateScale(textscale + 0.5f, textscale + 0.5f, 1);
	startMat = scale * trans;

	for (int i = 0;i < BULLET_MAX;++i)
	{
		trans = Math::Matrix::CreateTranslation(bulletPos[i].x, bulletPos[i].y, 0);
		scale = Math::Matrix::CreateScale(bulletSize[i], bulletSize[i], 1);
		bulletMat[i] = scale * trans;
	}

	trans = Math::Matrix::CreateTranslation(0, -250, 0);
	scale = Math::Matrix::CreateScale(3.0f, 3.0f, 1);
	wMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(0, -298, 0);
	scale = Math::Matrix::CreateScale(3.0f, 3.0f, 1);
	sMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(-48, -298, 0);
	scale = Math::Matrix::CreateScale(3.0f, 3.0f, 1);
	aMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(48, -298, 0);
	scale = Math::Matrix::CreateScale(3.0f, 3.0f, 1);
	dMat = scale * trans;
}

void C_Title::Draw()
{
	Math::Color color;

	color = { 1,1,1,bulletAlpha};
	for (int i = 0;i < BULLET_MAX;++i)
	{
		SHADER.m_spriteShader.SetMatrix(bulletMat[i]);
		SHADER.m_spriteShader.DrawTex(BULLET_MGR.GetMagBulletTex(), Math::Rectangle{ 0,0,16,16 }, &color);
	}

	color = { 1,1,1,startTexAlpha };
	SHADER.m_spriteShader.SetMatrix(MAGMat);
	SHADER.m_spriteShader.DrawTex(&MAGTex, Math::Rectangle{ 0,0,196,99 },&color);
	
	SHADER.m_spriteShader.SetMatrix(LOCKONMat);
	SHADER.m_spriteShader.DrawTex(&LOCKONTex, Math::Rectangle{ 0,0,324,98 }, &color);

	color = { 2,2,2,startTexAlpha };
	SHADER.m_spriteShader.SetMatrix(startMat);
	SHADER.m_spriteShader.DrawTex(&startTex,Math::Rectangle{0,0,307,64},&color);

	color = { 2.0f,2.0f,2.0f,startTexAlpha };
	SHADER.m_spriteShader.SetMatrix(wMat);
	if(isWpress)SHADER.m_spriteShader.DrawTex(&wPressTex, Math::Rectangle{ 0,0,16,16 }, &color);
	else        SHADER.m_spriteShader.DrawTex(&wTex, Math::Rectangle{ 0,0,16,16 }, &color);
	
	SHADER.m_spriteShader.SetMatrix(aMat);
	if (isApress)SHADER.m_spriteShader.DrawTex(&aPressTex, Math::Rectangle{ 0,0,16,16 }, &color);
	else        SHADER.m_spriteShader.DrawTex(&aTex, Math::Rectangle{ 0,0,16,16 }, &color);

	SHADER.m_spriteShader.SetMatrix(sMat);
	if (isSpress)SHADER.m_spriteShader.DrawTex(&sPressTex, Math::Rectangle{ 0,0,16,16 }, &color);
	else        SHADER.m_spriteShader.DrawTex(&sTex, Math::Rectangle{ 0,0,16,16 }, &color);

	SHADER.m_spriteShader.SetMatrix(dMat);
	if (isDpress)SHADER.m_spriteShader.DrawTex(&dPressTex, Math::Rectangle{ 0,0,16,16 }, &color);
	else        SHADER.m_spriteShader.DrawTex(&dTex, Math::Rectangle{ 0,0,16,16 }, &color);

}

void C_Title::Release()
{
	startTex.Release();
	MAGTex.Release();
	LOCKONTex.Release();
	wTex.Release();
	aTex.Release();
	sTex.Release();
	dTex.Release();
	wPressTex.Release();
	aPressTex.Release();
	sPressTex.Release();
	dPressTex.Release();

}
