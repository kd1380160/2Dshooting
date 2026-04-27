#include "Title.h"
#include "SceneManager.h"

C_Title::C_Title()
{
	titleTex.Load("Assets/Image/Title/title.png");
	startTex.Load("Assets/Image/Title/start.png");
	startTexAlpha = 1.0f;
	alphaAdd = 0.03f;
	isClick = true;
}

void C_Title::Init()
{
	isClick = true;
	startTexAlpha = 1.0f;
	alphaAdd = 0.02f;
}

void C_Title::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isClick)
		{
			isClick = true;
			SCENE_MGR.SetNowScene(SceneList::Game);
		}
	}
	else
	{
		isClick = false;
	}

	startTexAlpha += alphaAdd;
	if (startTexAlpha <= 0.4f)
	{
		startTexAlpha = 0.4f;
		alphaAdd *= -1;
	}
	else if(startTexAlpha >= 1.0f)
	{
		startTexAlpha = 1.0f;
		alphaAdd *= -1;
	}


	Math::Matrix trans;
	Math::Matrix scale;

	trans = Math::Matrix::CreateTranslation(0, 150, 0);
	scale = Math::Matrix::CreateScale(0.3, 0.3, 1);
	titleMat = scale * trans;

	trans = Math::Matrix::CreateTranslation(0, -150, 0);
	scale = Math::Matrix::CreateScale(1.5, 1.5, 1);
	startMat = scale * trans;
}

void C_Title::Draw()
{
	Math::Color color = { 1,1,1,startTexAlpha };

	SHADER.m_spriteShader.SetMatrix(titleMat);
	SHADER.m_spriteShader.DrawTex(&titleTex, Math::Rectangle{ 0,0,2549,640 });

	SHADER.m_spriteShader.SetMatrix(startMat);
	SHADER.m_spriteShader.DrawTex(&startTex,Math::Rectangle{0,0,307,64},&color);
}

void C_Title::Release()
{
	startTex.Release();
	titleTex.Release();
}
