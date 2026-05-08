#include "BackGround.h"
#include "../Scene.h"

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

	if (SCENE_MGR.GetNowScene() == Result)
	{
		backgroundMat[0] = Math::Matrix::CreateTranslation(backgroundPos[0].x + SCENE_MGR.GetResult()->GetShakeAmount(), backgroundPos[0].y + SCENE_MGR.GetResult()->GetShakeAmount(), 0);
		backgroundMat[1] = Math::Matrix::CreateTranslation(backgroundPos[1].x + SCENE_MGR.GetResult()->GetShakeAmount(), backgroundPos[1].y + SCENE_MGR.GetResult()->GetShakeAmount(), 0);
	}
	else
	{
		backgroundMat[0] = Math::Matrix::CreateTranslation(backgroundPos[0].x + SCENE.GetPlayer()->GetShakeAmount(), backgroundPos[0].y + SCENE.GetPlayer()->GetShakeAmount(), 0);
		backgroundMat[1] = Math::Matrix::CreateTranslation(backgroundPos[1].x + SCENE.GetPlayer()->GetShakeAmount(), backgroundPos[1].y + SCENE.GetPlayer()->GetShakeAmount(), 0);
	}
}

void C_BackGround::Draw()
{
	

	SHADER.m_spriteShader.SetMatrix(backgroundMat[0]);
	SHADER.m_spriteShader.DrawTex(&backgroundTex, Math::Rectangle{ 0,0,1320,730 });

	SHADER.m_spriteShader.SetMatrix(backgroundMat[1]);
	SHADER.m_spriteShader.DrawTex(&backgroundTex, Math::Rectangle{ 0,0,1320,730 });

	
}

void C_BackGround::Release()
{
	backgroundTex.Release();
	
}
