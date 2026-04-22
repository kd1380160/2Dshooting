#pragma once
#include "../Enemy/Enemy1.h"
#include "../Enemy/Enemy2.h"
#include "../Enemy/Enemy3.h"
#include "../Enemy/Enemy4.h"
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
	Math::Vector2 GetEnemy2Pos();
	Math::Vector2 GetEnemy3Pos();

	bool GetEnemy3Annihilation();
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

	//敵3
	static const int ENEMY3_MAX = 4;
	static const int ENEMY3_AMOUNT = 10;
	C_Enemy3* enemy3[ENEMY3_MAX] = {};
	KdTexture enemy3Tex;

	//敵4
	static const int ENEMY4_MAX = 5;
	static const int ENEMY4_AMOUNT = 10;
	C_Enemy4* enemy4[ENEMY4_MAX] = {};
	KdTexture enemy4Tex;

	int enemyKillCnt=0;
	int returnPosCnt=0;
	Math::Vector2 LockOnEnemy1Pos[ENEMY1_MAX] = { {0,0},{0,0},{0,0} };
	Math::Vector2 LockOnEnemy2Pos[ENEMY2_MAX] = { {0,0},{0,0},{0,0},{0,0},{0,0} };
	Math::Vector2 LockOnEnemy3Pos[ENEMY3_MAX+ENEMY1_MAX] = { {0,0},{0,0},{0,0},{0,0}, {0,0},{0,0},{0,0} };
	Math::Vector2 LockOnEnemy4Pos[ENEMY4_MAX+ENEMY2_MAX] = { {0,0},{0,0},{0,0},{0,0}, {0,0},{0,0},{0,0}, {0,0},{0,0} };

	KdTexture bossTex;
	C_Boss* boss;
	
	bool isCallBoss;
	bool isBoss;
	bool isInterval;

	int intervalCnt;
	static const int  INTERVAL = 120;

private:

	C_EnemyManager(){
		enemy1Tex.Load("Assets/Image/Enemy/enemy.png");
		enemy2Tex.Load("Assets/Image/Enemy/enemy2.png");
		enemy3Tex.Load("Assets/Image/Enemy/enemy3.png");
		enemy4Tex.Load("Assets/Image/Enemy/enemy4.png");
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
