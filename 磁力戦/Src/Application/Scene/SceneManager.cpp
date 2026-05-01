#include "SceneManager.h"
#include"../Scene.h"
#include"../Effect/EffectManager.h"
#include"../UI/UI.h"


void C_SceneManager::Init()
{
	switch (NowScene)
	{
	case SceneList::Title:
		title.Init();
		break;
	case SceneList::Game:
		SCENE.GetPlayer()->Init();
		BULLET_MGR.Init();
		ENEMY_MGR.Init();
		text.Init();
		EFFECT_MGR.Init();
		UI.Init();
		NowWave = WaveList::Wave2;
		
		break;
	case SceneList::Result:
		result.Init();
		break;
	case SceneList::GameOver:

		gameOver.Init();
		break;
	}
}

void C_SceneManager::Update()
{
	switch (NowScene)
	{
	case SceneList::Title:
		BACKGRND.Update();
		title.Update();
		break;
	case SceneList::Game:
		BACKGRND.Update();
		SCENE.GetPlayer()->Update();
		if (SCENE.GetPlayer()->GetCanStartGame())
		{
			ENEMY_MGR.Update();
			BULLET_MGR.Update();
			text.Update();
			EFFECT_MGR.Update();
		}
		UI.Update();
		break;
	case SceneList::Result:
		BACKGRND.Update();
		result.Update();
		break;
	case SceneList::GameOver:
		
		gameOver.Update();
		break;
	}
}

void C_SceneManager::Draw()
{
	switch (NowScene)
	{
	case SceneList::Title:
		BACKGRND.Draw();
		title.Draw();
		break;
	case SceneList::Game:
		BACKGRND.Draw();
		text.Draw();
		SCENE.GetPlayer()->Draw();
		BULLET_MGR.Draw();
		ENEMY_MGR.Draw();
		EFFECT_MGR.Draw();
		UI.Draw();
		break;
	case SceneList::Result:
		result.Draw();
		BACKGRND.Draw();
		break;	
	case SceneList::GameOver:
		BACKGRND.Draw();
		
		SCENE.GetPlayer()->Draw();
		BULLET_MGR.Draw();
		ENEMY_MGR.Draw();
		EFFECT_MGR.Draw();
		gameOver.Draw();
		break;
	}
}

void C_SceneManager::Release()
{
	title.Release();
	gameOver.Release();
}

void C_SceneManager::SetNowScene(SceneList now)
{
	NowScene = now;
	Init();
}
