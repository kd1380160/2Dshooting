#pragma once
#include"Game.h"
#include"Result.h"
#include"Title.h"

enum SceneList
{
	Title,
	Game,
	Result
};

class C_SceneManager
{
public:

	void Init();
	void Update();
	void Draw();


private:

	SceneList NowScene;

private:

	C_SceneManager() {}

public:
	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}
};

#define SCENE_MGR C_SceneManager::GetInstance()

