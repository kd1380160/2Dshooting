#pragma once
#include "../Enemy/Enemy1.h"
#include "../Enemy/Enemy2.h"
#include"Boss.h"

class C_EnemyManager
{
public:

	void Draw();
	void Init();
	void Update();
	void Release();

	void WaveInterval();
	int GetEnemyKillCnt() { return enemyKillCnt; }
	Math::Vector2 GetEnemy1Pos();
private:

	bool isClick;

	//敵
	static const int ENEMY1_MAX = 3;
	static const int ENEMY1_AMOUNT = 10;
	C_Enemy1* enemy1[ENEMY1_MAX] = {};
	KdTexture enemy1Tex;

	//敵２
	static const int ENEMY2_MAX = 5;
	static const int ENEMY2_AMOUNT = 10;
	C_Enemy2* enemy2[ENEMY2_MAX] = {};
	KdTexture enemy2Tex;

	int enemyKillCnt=0;
	int returnPosCnt=0;
	Math::Vector2 LockOnEnemyPos[3] = { {0,0},{0,0},{0,0} };

	KdTexture bossTex;
	C_Boss* boss = {};
	
	bool isCallBoss;
	bool isBoss;
	bool isInterval;

	int intervalCnt;
	static const int  INTERVAL = 120;

private:

	C_EnemyManager(){
		enemy1Tex.Load("Assets/Image/Enemy/enemy.png");
		enemy2Tex.Load("Assets/Image/Enemy/enemy2.png");
		bossTex.Load("Assets/Image/Enemy/Boss.png");
	}

public:
	static C_EnemyManager& GetInstance()
	{
		static C_EnemyManager instance;
		return instance;
	}
};
#define ENEMY_MGR C_EnemyManager::GetInstance()
