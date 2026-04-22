#include "SceneManager.h"
#include"../Scene.h"

void C_SceneManager::Init()
{
	switch (NowScene)
	{
	case SceneList::Title:
		break;
	case SceneList::Game:
		NowWave = WaveList::Wave4;
		SCENE.GetPlayer()->Init();
		BULLET_MGR.Init();
		ENEMY_MGR.Init();
		break;
	case SceneList::Result:
		break;
	}
}

void C_SceneManager::Update()
{
	switch (NowScene)
	{
	case SceneList::Title:
		break;
	case SceneList::Game:

		BACKGRND.Update();
		SCENE.GetPlayer()->Update();

		ENEMY_MGR.Update();

		BULLET_MGR.Update();
		break;
	case SceneList::Result:
		break;
	}
}

void C_SceneManager::Draw()
{
	switch (NowScene)
	{
	case SceneList::Title:
		break;
	case SceneList::Game:
		BACKGRND.Draw();
		SCENE.GetPlayer()->Draw();
		ENEMY_MGR.Draw();

		BULLET_MGR.Draw();
		break;
	case SceneList::Result:
		break;
	}
}

void C_SceneManager::SetNowScene(SceneList now)
{
	NowScene = now;
	Init();
}
