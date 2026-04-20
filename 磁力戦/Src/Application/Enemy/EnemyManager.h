#pragma once
#include "../Enemy/Enemy1.h"
#include"Boss.h"

class C_EnemyManager
{
public:

	void Draw();
	void Init();
	void Update();
	void Release();

	int GetEnemyKillCnt() { return enemyKillCnt; }
	Math::Vector2 GetEnemy1Pos();
private:

	bool isClick;

	//敵
	static const int ENEMY1_MAX = 3;
	static const int ENEMY1_AMOUNT = 10;
	C_Enemy1* enemy1[ENEMY1_MAX] = {};
	KdTexture enemy1Tex;

	int enemyKillCnt=0;
	int returnPosCnt=0;
	Math::Vector2 LockOnEnemyPos[3] = { {0,0},{0,0},{0,0} };

	KdTexture bossTex;
	C_Boss* boss = {};
	
	bool isCallBoss;
	bool isBoss;

private:

	C_EnemyManager(){
		enemy1Tex.Load("Assets/Image/Enemy/enemy.png");
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
