#pragma once
#include"Game.h"
#include"Result.h"
#include"Title.h"
#include "../Player/Player.h"
#include"../BackGround/BackGround.h"
#include"../Bullet/BulletManager.h"
#include"../Enemy/EnemyManager.h"


enum SceneList
{
	Title,
	Game,
	Result
};

enum WaveList
{
	Wave1,
	Wave2,
	Wave3,
	Wave4,
	Wave5,
	Boss,
	WaveNum
};

class C_SceneManager
{
public:

	void Init();
	void Update();
	void Draw();

	void SetNowScene(SceneList now);

	WaveList	GetNowWave() { return NowWave; }
	void		SetNowWave(WaveList now) { NowWave = now; }
private:

	SceneList NowScene;
	WaveList NowWave;
	


private:

	C_SceneManager() { NowWave = WaveList::Wave1; }

public:
	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}
};

#define SCENE_MGR C_SceneManager::GetInstance()

