#include "BackGround.h"

void C_BackGround::Init()
{
	backgroundPos[0] = {0,0};
	backgroundPos[1] = {0,720};
	
}

void C_BackGround::Update()
{
	backgroundPos[0].y -= 8;
	backgroundPos[1].y -= 8;

	if (backgroundPos[0].y <= -720)backgroundPos[0].y = 720;
	if (backgroundPos[1].y <= -720)backgroundPos[1].y = 720;

	backgroundMat[0] = Math::Matrix::CreateTranslation(backgroundPos[0].x, backgroundPos[0].y, 0);
	backgroundMat[1] = Math::Matrix::CreateTranslation(backgroundPos[1].x, backgroundPos[1].y, 0);
}

void C_BackGround::Draw()
{
	SHADER.m_spriteShader.SetMatrix(backgroundMat[0]);
	SHADER.m_spriteShader.DrawTex(&backgroundTex, Math::Rectangle{ 0,0,1280,720 });

	SHADER.m_spriteShader.SetMatrix(backgroundMat[1]);
	SHADER.m_spriteShader.DrawTex(&backgroundTex, Math::Rectangle{ 0,0,1280,720 });
}

void C_BackGround::Release()
{
	backgroundTex.Release();
}
