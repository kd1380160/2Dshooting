#include "Result.h"
#include "../Scene.h"
#include "../Transition/Transition.h"
C_Result::C_Result()
{
	numberTex.Load("Assets/Image/Result/number.png");
	clearTex.Load("Assets/Image/Result/clear.png");
	clearTimeTex.Load("Assets/Image/Result/cleartime.png");
	lightTex.Load("Assets/Image/Effect/Sun.png");
	LclickTex.Load("Assets/Image/GameOver/Lclick.png");
	RclickTex.Load("Assets/Image/GameOver/Rclick.png");
	SscoreTex.Load("Assets/Image/Result/S.png");
	AscoreTex.Load("Assets/Image/Result/A.png");
	BscoreTex.Load("Assets/Image/Result/B.png");
}

C_Result::~C_Result()
{
	numberTex.Release();
	clearTex.Release();
	clearTimeTex.Release();
	lightTex.Release();
	LclickTex.Release();
	RclickTex.Release();
	SscoreTex.Release();
	AscoreTex.Release();
	BscoreTex.Release();
}

void C_Result::Init()
{
	isFinishCounting = false;
	isBlight = false;
	isShow = false;
	isBigScore = false;
	isSmallScore = false;
	isShowScore = false;
	clearAlpha = 0.0f;
	clearSize = 3.3f;
	LclickSize = 0.7f;
	RclickSize = 0.7f;
	scoreSize = 4.0f;
	lightAlpha = 0.0f;
	lightAlphaAdd = 0.05f;
	choiceLightAlpha = 0.0f;
	choiceLightAlphaAdd = 0.03f;
	scoreLightAlpha = 1.0f;
	textAlpha = 0.0f;
	textAlphaAdd = 0.01;
	time = SCENE_MGR.GePlayTime();
	ScoreCheck();
	minute = 0;
	second = 0;
	timeCnt = 0;
	LclickPos = { -30,-70 };
	RclickPos = { 0,-300 };
	scoreLightPos = { 400,0 };
	timeColor = { 1,1,1,textAlpha };
}

void C_Result::Update()
{
	if (!TRANSITION.GetIsTransition())
	{
		clearAlpha += 0.01f;
		if (clearAlpha >= 1.0f)clearAlpha = 1.0f;

		clearSize += 0.02f;
		if (clearSize >= 4.0f)clearSize = 4.0f;

		if (!isShow)
		{
			textAlpha += textAlphaAdd;
			if (textAlpha >= 1.0f)
			{
				isShow = true;
				textAlpha = 1.0f;
			}
			timeColor = { 1,1,1,textAlpha };
		}


		if (isShow)
		{

			if (!isFinishCounting && clearSize == 4.0f)
			{
				timeCnt++;
				if (timeCnt >= time)
				{
					isFinishCounting = true;
				}

				//1秒ずつ加算
				second++;
				if (second >= 60)
				{
					second = 0;
					minute++;
				}
				isShake = true;
			}

			if (!isBlight)
			{
				if (isFinishCounting)
				{
					lightAlpha += lightAlphaAdd;
					if (lightAlpha >= 1.0f)
					{
						lightAlphaAdd *= -1;
					}
					if (lightAlpha < 0)
					{
						isBlight = true;
						isShowScore = true;
					}
				}
			}
			else
			{
				if (!isBigScore)
				{
					if (!isSmallScore)
					{
						scoreSize += 0.08f;
						if (scoreSize >= 5.0f)
						{
							scoreSize = 5.0f;
							isSmallScore = true;
						}
					}
					else
					{
						scoreSize -= 0.08f;
						if(scoreSize <= 4.0f)
						{
							scoreSize = 4.0f;
							isBigScore = true;
						}
					}

				}

				choiceLightAlpha += choiceLightAlphaAdd;
				if (choiceLightAlpha >= 1.0f || choiceLightAlpha <= 0.0f)
				{

					choiceLightAlphaAdd *= -1;
				}

				scoreLightPos += {-1.5, -2};
				if (choiceLightAlpha <= 0.0f)
				{
					scoreLightPos = { 400,0 };
				}
			}
		}





		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!isLClick)
			{
				isLClick = true;
				TRANSITION.Start(Game);
			}
		}
		else
		{
			isLClick = false;
		}

		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if (!isRClick)
			{
				isRClick = true;
				TRANSITION.Start(Title);
			}
		}
		else
		{
			isRClick = false;
		}


		if (isShake)
		{
			if (shakeCnt == 0)shakeAmount = 3;

			shakeCnt++;
			if (shakeCnt % 3 == 0)
			{
				shakeAmount *= -0.8;
				if (shakeCnt == 21)
				{
					shakeAmount = 0;
					shakeCnt = 0;
					isShake = false;
					
				}
			}
		}
	}

	Math::Matrix scale, trans;

	//クリアタイムテキスト
	trans = Math::Matrix::CreateTranslation(-350+shakeAmount, -15 + shakeAmount, 0);
	scale = Math::Matrix::CreateScale(CLEARTIME_TEXT_SIZE, CLEARTIME_TEXT_SIZE, 1);
	clearTimeTextMat = scale * trans;

	//クリアタイム
	for (int i = 0;i < 5;i++)
	{
		trans = Math::Matrix::CreateTranslation(i*6*NUMBER_SIZE-100 + shakeAmount, -20 + shakeAmount, 0);
		scale = Math::Matrix::CreateScale(NUMBER_SIZE, NUMBER_SIZE, 1);
		clearTimeMat[i] = scale * trans;
	}

	//クリア表示
	trans = Math::Matrix::CreateTranslation(0 + shakeAmount, 220 + shakeAmount, 0);
	scale = Math::Matrix::CreateScale(clearSize, clearSize, 1);
	clearMat = scale * trans;

	//ライト
	scale = Math::Matrix::CreateScale(2, 2, 0);
	trans = Math::Matrix::CreateTranslation(90 + shakeAmount, 0 + shakeAmount, 0);
	lightMat = scale * trans;

	scale = Math::Matrix::CreateScale(2, 2, 0);
	trans = Math::Matrix::CreateTranslation(LclickPos.x-160 + shakeAmount, LclickPos.y-150 + shakeAmount, 0);
	choiceLightMat[0] = scale * trans;

	scale = Math::Matrix::CreateScale(2, 2, 0);
	trans = Math::Matrix::CreateTranslation(RclickPos.x - 190 + shakeAmount, RclickPos.y + shakeAmount, 0);
	choiceLightMat[1] = scale * trans;

	trans = Math::Matrix::CreateTranslation(LclickPos.x + shakeAmount, LclickPos.y - 150 + shakeAmount, 0);
	scale = Math::Matrix::CreateScale(LclickSize, LclickSize, 0);
	LclickMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(RclickPos.x + shakeAmount, RclickPos.y + shakeAmount, 0);
	scale = Math::Matrix::CreateScale(RclickSize, RclickSize, 0);
	RclickMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(350, -100, 0);
	scale = Math::Matrix::CreateScale(scoreSize, scoreSize, 0);
	scoreMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(scoreLightPos.x, scoreLightPos.y, 0);
	scale = Math::Matrix::CreateScale(4, 4, 0);
	scoreLightMat = scale * trans;
}

void C_Result::Draw()
{
	Math::Color col;

	//色のブレンド方法の設定（加算合成）
	D3D.SetBlendState(BlendMode::Add);

	if (isFinishCounting&&!isBlight)
	{
		//ライト
		col = { 0,1,1,lightAlpha };

		SHADER.m_spriteShader.SetMatrix(lightMat);
		SHADER.m_spriteShader.DrawTex(&lightTex, Math::Rectangle(0, 0, 128, 128), &col);
	}

	
	for (int i = 0;i < 2;i++)
	{
		if(i==0)col = { 0.2f,0.8f,0.8f,choiceLightAlpha };
		if(i==1)col = { 0.5f,0.5f,0.6f,choiceLightAlpha };
		SHADER.m_spriteShader.SetMatrix(choiceLightMat[i]);
		SHADER.m_spriteShader.DrawTex(&lightTex, Math::Rectangle(0, 0, 128, 128), &col);
	}


	//色のブレンド方法の設定（合成なし）
	D3D.SetBlendState(BlendMode::Alpha);


	col = { 1,1,1,textAlpha };
	//クリアタイムテキスト表示
	SHADER.m_spriteShader.SetMatrix(clearTimeTextMat);
	SHADER.m_spriteShader.DrawTex(&clearTimeTex, Math::Rectangle{ 0,0,207,64 },&col);

	//クリアタイム表示
	for (int i = 0;i < 5;i++)
	{
		SHADER.m_spriteShader.SetMatrix(clearTimeMat[i]);
		switch (i)
		{
		case 0:
			if (minute < 10)
			{
				SHADER.m_spriteShader.DrawTex(&numberTex, Math::Rectangle{ 0,0,6,10 }, &timeColor);
			}
			else
			{
				SHADER.m_spriteShader.DrawTex(&numberTex, Math::Rectangle{ 6*(minute/10),0,6,10}, &timeColor);
			}
			break;
		case 1:
			SHADER.m_spriteShader.DrawTex(&numberTex, Math::Rectangle{ 6 * (minute % 10),0,6,10 }, &timeColor);
			break;
		case 2:
			//コロン
			col = { 1,0,0,textAlpha };
			SHADER.m_spriteShader.DrawTex(&numberTex, Math::Rectangle{ 60,0,6,10 },&col);
			break;
		case 3:
			SHADER.m_spriteShader.DrawTex(&numberTex, Math::Rectangle{ 6*(second/10),0,6,10}, &timeColor);
			break;
		case 4:
			SHADER.m_spriteShader.DrawTex(&numberTex, Math::Rectangle{ 6*(second%10),0,6,10},&timeColor);
			break;
		}

			//分秒
	
	}

	//クリア表示
	col = {0,1,1,clearAlpha };
	SHADER.m_spriteShader.SetMatrix(clearMat);
	SHADER.m_spriteShader.DrawTex(&clearTex, Math::Rectangle{ 0,0,260,61 },&col);

	col = { 1,1,1,textAlpha };
	//リトライ案内
	SHADER.m_spriteShader.SetMatrix(LclickMat);
	SHADER.m_spriteShader.DrawTex(&LclickTex, Math::Rectangle{ 0,0,387,71 },&col);

	//タイトル案内
	SHADER.m_spriteShader.SetMatrix(RclickMat);
	SHADER.m_spriteShader.DrawTex(&RclickTex, Math::Rectangle{ 0,0,467,71 },&col);

	if (isShowScore)
	{
		col = { 1,1,1,1.0f };
		SHADER.m_spriteShader.SetMatrix(scoreMat);
		switch (rank)
		{
		case Score::S:
			SHADER.m_spriteShader.DrawTex(&SscoreTex, Math::Rectangle{ 0,0,87,98 }, &col);
			break;
		case Score::A:
			SHADER.m_spriteShader.DrawTex(&AscoreTex, Math::Rectangle{ 0,0,92,98 }, &col);
			break;
		case Score::B:
			SHADER.m_spriteShader.DrawTex(&BscoreTex, Math::Rectangle{ 0,0,92,98 }, &col);
			break;
		}
	}

	D3D.SetBlendState(BlendMode::Add);
	if (isShowScore)
	{
		col = { 0.4,0.4,0.4,choiceLightAlpha };
		SHADER.m_spriteShader.SetMatrix(scoreLightMat);
		SHADER.m_spriteShader.DrawTex(&lightTex, Math::Rectangle(0, 0, 128, 128), &col);
	}
	D3D.SetBlendState(BlendMode::Alpha);
}

void C_Result::ScoreCheck()
{
	if (time <= 180)
	{
		rank = Score::S;
	}
	else if (time <= 240)
	{
		rank = Score::A;
	}
	else
	{
		rank = Score::B;
	}
}
