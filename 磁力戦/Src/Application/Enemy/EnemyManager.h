#pragma once
#include "../Enemy/Enemy1.h"
#include "../Enemy/Enemy2.h"
#include "../Enemy/Enemy3.h"
#include "../Enemy/Enemy4.h"
#include "../Enemy/Generator.h"
#include"Boss.h"
#include "../Bullet/BulletManager.h"

class C_EnemyManager
{
public:

	void Draw();
	void Init();
	void Update();
	void Release();

	void WaveInterval();
	int GetEnemyKillCnt() { return enemyKillCnt; }
	Math::Vector2 GetEnemyWavePos();
	Math::Vector2 GetEnemy4Pos(int num);
	Math::Vector2 GetGeneratorPos(int num);
	Math::Vector2 GetBossPos();

	bool GetIsEnemy4Alive(int num);
	bool GetIsGeneratorAlive(int num);
	bool GetIsEnemyAlive(int type, int num);
	bool GetIsLockonGenerator(int num){ return generator[num]->GetIsLockOn(); }
	void RegisterLockonEnemyNum();								//ロックオンしている敵の情報を登録
	bool GetEnemy3Annihilation();								//磁力弾阻害のため全滅チェック
	int GetLockonEnemyNum(int num);								//ロックオンした敵の番号を返す
	int GetLockonEnemyType(int num);							//ロックオンした敵の種類を返す
	int GetGeneratorHp();										//ボスのお供（ジェネレーター）のHPを返す
	int GetBossHp();											//ボスのHPを返す
	bool GetBossFinisher();										//ボスのフィニッシャー可能かどうかを返す
	bool GetCanShotMagBullet();									//磁力弾発射可能かどうかを返す（ロックオン対象がいるかどうか）
	bool PlayerEnemyHitCheck(Math::Vector2 pos, int radius);	//敵と自機の当たり判定チェック
	bool GetIsBossSecond();										//ボスが第二形態に移行したかどうかを返す
	bool GetIsBossDead();										//ボスを倒したかどうかを返す
	bool GetIsEnemy1Lockon();
	bool GetIsEnemy1Dead()const;
	Math::Vector2 GetLockOnEnemyPos(int type, int number);

	KdTexture* GetEnemy1Tex() { return &enemy1Tex; }
	KdTexture* GetLockOnTex() { return &lockOnTex; }
private:

	bool isClick;

	//敵
	static const int ENEMY1_MAX = 5;
	static const int ENEMY1_AMOUNT = 10;
	C_Enemy1* enemy1[ENEMY1_MAX] = {};
	KdTexture enemy1Tex;
	KdTexture enemy1BreakTex;
	KdTexture enemy1EngineTex;


	//敵２
	static const int ENEMY2_MAX = 5;
	static const int ENEMY2_AMOUNT = 10;
	C_Enemy2* enemy2[ENEMY2_MAX] = {};
	KdTexture enemy2Tex;
	KdTexture enemy2BreakTex;
	KdTexture enemy2EngineTex;

	//敵3
	static const int ENEMY3_MAX = 1;
	static const int ENEMY3_AMOUNT = 10;
	C_Enemy3* enemy3= {};
	KdTexture enemy3Tex;
	KdTexture enemy3BreakTex;
	KdTexture enemy3EngineTex;
	int setCnt;
	bool spawnEnemy;

	//敵4
	static const int ENEMY4_MAX = 5;
	static const int ENEMY4_AMOUNT = 10;
	C_Enemy4* enemy4[ENEMY4_MAX] = {};
	KdTexture enemy4Tex;
	KdTexture enemy4BreakTex;
	KdTexture enemy4EngineTex;

	//ボスのお供(バリア発生装置)
	static const int GENERATOR_MAX = 2;
	C_Generator* generator[GENERATOR_MAX] = {};
	KdTexture generatorTex;

	int enemyKillCnt=0;
	int returnPosCnt=0;
	
	static	const int LOCKON_ENEMY_MAX = 5;
	Math::Vector2 LockOnEnemyPos[LOCKON_ENEMY_MAX] = {};
	int lockonCnt = 0;

	int lockonEnemyNumType[LOCKON_ENEMY_MAX][2] = { {},{}, {}, {}, {} };

	KdTexture bossTex;
	KdTexture bossShieldTex;
	KdTexture bossBreakTex;
	KdTexture bossEngineTex;
	C_Boss* boss;

	KdTexture lockOnTex;

	bool isCallBoss;
	bool isBoss;

	bool isFinishWave;
	bool isTutorialEnemySpawn;
	bool isTutorialEnemyDead;
	bool isStartChangeWave;
	int SpawnCnt;
	
	
private:

	C_EnemyManager(){
		enemy1Tex.Load			("Assets/Image/Enemy/enemy.png");
		enemy1BreakTex.Load		("Assets/Image/Enemy/enemyBreak.png");
		enemy1EngineTex.Load	("Assets/Image/Enemy/enemyEngine.png");
		enemy2Tex.Load			("Assets/Image/Enemy/enemy2.png");
		enemy2BreakTex.Load		("Assets/Image/Enemy/enemy2Break.png");
		enemy2EngineTex.Load	("Assets/Image/Enemy/enemy2Engine.png");
		enemy3Tex.Load			("Assets/Image/Enemy/enemy3.png");
		enemy3BreakTex.Load		("Assets/Image/Enemy/enemy3Break.png");
		enemy3EngineTex.Load	("Assets/Image/Enemy/enemy3Engine.png");
		enemy4Tex.Load			("Assets/Image/Enemy/enemy4.png");
		enemy4BreakTex.Load		("Assets/Image/Enemy/enemy4Break.png");
		enemy4EngineTex.Load	("Assets/Image/Enemy/enemy4Engine.png");
		generatorTex.Load		("Assets/Image/Enemy/generator.png");
		bossTex.Load			("Assets/Image/Enemy/Boss.png");
		bossShieldTex.Load		("Assets/Image/Enemy/BossShield.png");
		bossBreakTex.Load		("Assets/Image/Enemy/BossBreak.png");
		bossEngineTex.Load		("Assets/Image/Enemy/BossEngine.png");
		lockOnTex.Load			("Assets/Image/Reticle/LockOn.png");
	}

public:
	static C_EnemyManager& GetInstance()
	{
		static C_EnemyManager instance;
		return instance;
	}
};
#define ENEMY_MGR C_EnemyManager::GetInstance()
