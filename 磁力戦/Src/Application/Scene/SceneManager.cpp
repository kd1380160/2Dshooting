#include "SceneManager.h"
#include"../Scene.h"
#include"../Effect/EffectManager.h"
#include"../Transition/Transition.h"
#include"../UI/UI.h"


void C_SceneManager::Init()
{
	switch (NowScene)
	{
	case SceneList::Title:
		title.Init();
		break;
	case SceneList::Game:
		isTime = false;
		isWave1TextFinish = false;
		isWave1TextStart = false;
		timeCnt = 0;
		SCENE.GetPlayer()->Init();
		BULLET_MGR.Init();
		ENEMY_MGR.Init();
		text.Init();
		EFFECT_MGR.Init();
		UI.Init();
		NowWave = WaveList::Wave1;
		
		break;
	case SceneList::Result:
		result.Init();
		break;
	case SceneList::GameOver:

		gameOver.Init();
		break;
	case SceneList::Tutorial:
		SCENE.GetPlayer()->Init();
		BULLET_MGR.Init();
		ENEMY_MGR.Init();
		text.Init();
		EFFECT_MGR.Init();
		UI.Init();
		tutorial.Init();
		break;
	}

	cursor.Init();
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


			if (!isWave1TextFinish)
			{
				if (!isWave1TextStart)
				{
					
					ENEMY_MGR.Update();
				
					isWave1TextStart = true;
					SCENE_MGR.GetText()->ChangeWave(1);
				}
				SCENE.GetPlayer()->Update();
				BACKGRND.Update();
				UI.Update();
				
				if (SCENE_MGR.GetText()->GetIsFinishDirection())
				{
					isWave1TextFinish = true;
				}
			}
			else
			{
				if (isTime)
				{
					timeCnt++;
				}

				SCENE.GetPlayer()->Update();
				if (SCENE.GetPlayer()->GetPlayerHp() > 0)
				{

					BACKGRND.Update();


					if (SCENE.GetPlayer()->GetCanStartGame())
					{
						ENEMY_MGR.Update();
						BULLET_MGR.Update();

						EFFECT_MGR.Update();
					}
					UI.Update();
				}
			}
			text.Update();
			break;
		case SceneList::Result:
			BACKGRND.Update();
			result.Update();
			break;
		case SceneList::GameOver:

			gameOver.Update();
			break;
		case SceneList::Tutorial:
			tutorial.Update();
			BACKGRND.Update();
			if (!tutorial.GetIsShowWindow())
			{
				SCENE.GetPlayer()->Update();
				ENEMY_MGR.Update();
				BULLET_MGR.Update();
				text.Update();
				EFFECT_MGR.Update();
				UI.Update();
			}
			break;
		}
	
	TRANSITION.Update();
	cursor.Update();
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
		
		BULLET_MGR.Draw();
		ENEMY_MGR.Draw();
		SCENE.GetPlayer()->Draw();
		EFFECT_MGR.Draw();
		if (SCENE.GetPlayer()->GetPlayerHp() > 0)
		{
			UI.Draw();
		}
		break;
	case SceneList::Result:
		
		BACKGRND.Draw();
		result.Draw();
		break;	
	case SceneList::GameOver:
		BACKGRND.Draw();
		
		SCENE.GetPlayer()->Draw();
		BULLET_MGR.Draw();
		ENEMY_MGR.Draw();
		EFFECT_MGR.Draw();
		gameOver.Draw();
		break;
	case SceneList::Tutorial:
		BACKGRND.Draw();
		SCENE.GetPlayer()->Draw();
		BULLET_MGR.Draw();
		ENEMY_MGR.Draw();
		EFFECT_MGR.Draw();
		UI.Draw();
		text.Draw();
		tutorial.Draw();
		break;
	}

	TRANSITION.Draw();
	cursor.Draw();
}

void C_SceneManager::Release()
{
	title.Release();
	gameOver.Release();
}

void C_SceneManager::SetNowScene(SceneList now)
{
	if (NowScene == SceneList::Tutorial && now == SceneList::Game)
	{
		NowScene = now;
		isTime = true;
		timeCnt = 0;
		BULLET_MGR.Init();
		ENEMY_MGR.Init();
		text.Init();
		EFFECT_MGR.Init();
		UI.Init();
		UI.ShowLeftEnemy();
		UI.StartCntUp();
		NowWave = WaveList::Wave1;
	}
	else
	{
		NowScene = now;
		Init();
	}

	Update();
}
