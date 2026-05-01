#include "GameOver.h"
#include "SceneManager.h"

C_GameOver::C_GameOver()
{
	tex.Load("Assets/Image/GameOver/GameOver.png");
	blackBackTex.Load("Assets/Image/BackGround/Black.png");
	retryTex.Load("Assets/Image/GameOver/Retry.png");
	LclickTex.Load("Assets/Image/GameOver/Lclick.png");
	RclickTex.Load("Assets/Image/GameOver/Rclick.png");
	SunTex.Load("Assets/Image/Effect/Sun.png");
}

C_GameOver::~C_GameOver()
{
	tex.Release();
	blackBackTex.Release();
	retryTex.Release();
	LclickTex.Release();
	RclickTex.Release();
	SunTex.Release();
}

void C_GameOver::Init()
{
	pos = { 0,250 };
	retryPos = { 0,0 };
	LclickPos = { 0,-100 };
	RclickPos = { 0,-300 };
	

	size = 3.0f;
	retrySize = 6.0f;
	LclickSize = 0.7f;
	RclickSize = 0.5f;
	SunSize = 7.0f;
	
	sizeAdd = 0.02f;
	posAdd = 0.5f;
	angle = 0;
	sunAlpha = 1.0f;
	sunAlphaAdd = 0.02f;
}

void C_GameOver::Update()
{

	angle += 3;
	if (angle >= 360)
	{
		angle -= 360;
	}


	//sinカーブをプレイヤーのY座標に影響させる
	retryPos.y = sinf(DirectX::XMConvertToRadians(angle)) * 15;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		SCENE_MGR.SetNowScene(Game);
	}
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		SCENE_MGR.SetNowScene(Title);
	}


	sunAlpha -= sunAlphaAdd;
	if (sunAlpha >= 1.0f || sunAlpha <= 0.0f)
	{
		sunAlphaAdd *= -1;
	}


	Math::Matrix trans, scale;
	trans = Math::Matrix::CreateTranslation(pos.x, pos.y, 0);
	scale = Math::Matrix::CreateScale(size, size, 0);
	mat = scale * trans;

	trans = Math::Matrix::CreateTranslation(retryPos.x, retryPos.y, 0);
	scale = Math::Matrix::CreateScale(retrySize, retrySize, 0);
	retryMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(LclickPos.x, retryPos.y - 150, 0);
	scale = Math::Matrix::CreateScale(LclickSize, LclickSize, 0);
	LclickMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(RclickPos.x, RclickPos.y, 0);
	scale = Math::Matrix::CreateScale(RclickSize, RclickSize, 0);
	RclickMat = scale * trans;

	for (int i = 0;i < 4;++i)
	{
		trans = Math::Matrix::CreateTranslation(SunPos[i].x, SunPos[i].y, 0);
		scale = Math::Matrix::CreateScale(SunSize, SunSize, 0);
		SunMat[i] = scale * trans;
	}
}

void C_GameOver::Draw()
{
	Math::Color color = { 1,1,1,0.8 };

	//色のブレンド方法の設定（半透明）
	D3D.SetBlendState(BlendMode::Alpha);


	SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(0, 0, 0));
	SHADER.m_spriteShader.DrawTex(&blackBackTex, Math::Rectangle{ 0,0,1280,720 }, &color);

	color = { 1,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&tex, Math::Rectangle{ 0,0,207,61 }, &color);

	SHADER.m_spriteShader.SetMatrix(LclickMat);
	SHADER.m_spriteShader.DrawTex(&LclickTex, Math::Rectangle{ 0,0,387,71 });

	SHADER.m_spriteShader.SetMatrix(RclickMat);
	SHADER.m_spriteShader.DrawTex(&RclickTex, Math::Rectangle{ 0,0,467,71 });

	color = { 1,1,1,0.7 };
	SHADER.m_spriteShader.SetMatrix(retryMat);
	SHADER.m_spriteShader.DrawTex(&retryTex, Math::Rectangle{ 0,0,147,67 },&color);

	//色のブレンド方法の設定（加算合成）
	D3D.SetBlendState(BlendMode::Add);

	//太陽
	color = { 0.8,0.8,1,sunAlpha };
	for (int i = 0;i < 4;++i)
	{
		SHADER.m_spriteShader.SetMatrix(SunMat[i]);
		SHADER.m_spriteShader.DrawTex(&SunTex, Math::Rectangle(0, 0, 128, 128), &color);
	}
	//色のブレンド方法の設定（合成なし）
	D3D.SetBlendState(BlendMode::Alpha);

}

void C_GameOver::Release()
{
	tex.Release();
	blackBackTex.Release();
	retryTex.Release();
	LclickTex.Release();
	RclickTex.Release();
}
