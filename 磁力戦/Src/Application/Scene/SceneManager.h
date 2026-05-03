#pragma once
#include"Game.h"
#include"Result.h"
#include"Title.h"
#include"GameOver.h"
#include"Tutorial.h"
#include"../GameSystem/Cursor/Cursor.h"
#include "../Player/Player.h"
#include"../BackGround/BackGround.h"
#include"../Bullet/BulletManager.h"
#include"../Enemy/EnemyManager.h"
#include"../GameSystem/Text/Text.h"
#include"../Effect/EffectManager.h"

enum SceneList
{
	Title,
	Game,
	Result,
	GameOver,
	Tutorial
};

enum WaveList
{
	Wave1,
	Wave2,
	Wave3,
	Wave4,
	Boss,
	WaveNum
};

class C_SceneManager
{
public:

	void Init();
	void Update();
	void Draw();

	void Release();
	void SetNowScene(SceneList now);

	WaveList	GetNowWave()			 { return NowWave; }
	SceneList	GetNowScene()			 { return NowScene; }
	void		SetNowWave(WaveList now) { NowWave = now; }
	bool		GetIsFinishPage2()		 { return tutorial.GetIsFinishPage2(); }

	void StartTimeCnt() { isTime = true; }
	void StopTimeCnt()	{ isTime = false;}
	int GePlayTime()	{ return timeCnt/60; }
private:

	SceneList NowScene;
	WaveList NowWave;
	
	C_Title title;
	C_Result result;
	C_Text text;
	C_GameOver gameOver;
	C_Tutorial tutorial;
	C_Cursor cursor;

	int timeCnt=60*61;
	bool isTime;

private:

	C_SceneManager() { 
		NowWave = WaveList::Wave1; 
		NowScene = SceneList::Title;
	}

public:
	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}
};

#define SCENE_MGR C_SceneManager::GetInstance()

