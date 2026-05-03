#include "Cursor.h"
#include"../../Scene.h"

C_Cursor::C_Cursor()
{
	cursorTex.Load("Assets/Image/Reticle/Cursor.png");
}

C_Cursor::~C_Cursor()
{
	cursorTex.Release();
}

void C_Cursor::Init()
{
	cursorSize = 4.0f;
	cursorCnt;
}

void C_Cursor::Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isLclick)
		{
			cursorSize = 3.5f;
			isLclick = true;
		}
	}
	else { isLclick = false; }

	if (cursorSize == 3.5f)
	{
		cursorCnt++;
		if (cursorCnt >= 10)
		{
			cursorCnt = 0;
			cursorSize = 4.0f;
		}
	}

	Math::Matrix trans, scale;
	trans = Math::Matrix::CreateTranslation(SCENE.GetMousePos().x, SCENE.GetMousePos().y, 0);
	scale = Math::Matrix::CreateScale(cursorSize, cursorSize, 1);
	cursorMat = scale * trans;
}

void C_Cursor::Draw()
{
	Math::Color color = { 0.7f,0.7f,0.7f,1 };
	SHADER.m_spriteShader.SetMatrix(cursorMat);
	SHADER.m_spriteShader.DrawTex(&cursorTex, Math::Rectangle{ 0,0,17,17 },&color);
}
