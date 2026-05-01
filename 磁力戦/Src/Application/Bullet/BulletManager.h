#pragma once
#include "MagneticBullet.h"
#include "NormalBullet.h"
#include"Enemy1Bullet.h"
#include"Enemy2Bullet.h"
#include"Enemy3Bullet.h"
#include"BossBullet.h"
#include"BossBullet2.h"


class C_BulletManager
{
public:

	void Draw();
	void Update();
	void Init();

	void TrackingUpdate(int num);
	void SpawnMagBullet(Math::Vector2 enemyPos);
	
	void ShotNormalBullet(Math::Vector2 playerPos);
	void ShotEnemy1Bullet(Math::Vector2 enemyPos);
	void ShotEnemy2Bullet(Math::Vector2 enemyPos, Math::Vector2 move);
	void ShotEnemy2Bullet(Math::Vector2 enemyPos, int angle);
	void ShotEnemy3Bullet(Math::Vector2 enemyPos);
	void ShotBossBullet(Math::Vector2 bossPos, int degree, int speed);
	void ShotBossBullet2(Math::Vector2 bossPos, int degree);
	void ShotBossBullet2(Math::Vector2 bossPos, Math::Vector2 playerPos);
	void ShotBossBullet2(Math::Vector2 bossPos, int moveX, int moveY);
	void ShotMagBullet();

	bool EnemyHitCheck(Math::Vector2 pos,int radius,bool shieldhit);
	bool PlayerHitCHeck(Math::Vector2 pos, int radius);
	bool EnemyBulletAliveCheck();
	bool MagneticBulletAliveCheck();
	bool GetIsJamming()const { return isJamming; }

	void Release();
	void ClearAllBullet();
	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
private:

	//存在可能な磁力弾の最大数(50)
	static const int MAGNETIC_BULLET_MAX = 50;
	C_MagneticBullet* magneticBullets[MAGNETIC_BULLET_MAX] = {};
	KdTexture magneticBulletTex;

	//存在可能な敵1の弾の最大数(30)
	static const int ENEMY1_BULLET_MAX = 30;
	C_Enemy1Bullet* enemy1Bullets[ENEMY1_BULLET_MAX] = {};
	KdTexture enemy1BulletTex;

	//存在可能な敵2の弾の最大数(30)
	static const int ENEMY2_BULLET_MAX = 60;
	C_Enemy2Bullet* enemy2Bullets[ENEMY2_BULLET_MAX] = {};
	KdTexture enemy2BulletTex;

	//存在可能な敵3の弾の最大数(4)
	static const int ENEMY3_BULLET_MAX = 8;
	C_Enemy3Bullet* enemy3Bullets[ENEMY3_BULLET_MAX] = {};
	KdTexture enemy3BulletTex;

	// 存在可能なボスの弾1の最大数(150)
	static const int BOSS_BULLET_MAX = 150;
	C_BossBullet* bossBullets[BOSS_BULLET_MAX] = {};
	KdTexture bossBulletTex;
	
	// 存在可能なボスの弾2(非吸収)の最大数(150)
	static const int BOSS_BULLET2_MAX = 300;
	C_BossBullet2* bossBullets2[BOSS_BULLET2_MAX] = {};
	KdTexture bossBullet2Tex;

	//存在可能な通常弾の最大数(30)
	static const int NORMAL_BULLET_MAX = 30;
	C_NormalBullet* normalBullets[NORMAL_BULLET_MAX] = {};
	KdTexture normalBulletTex;

	static const int LOCKON_MAX = 5;
	int lockonEnemyNumType[LOCKON_MAX][2] = { {},{}, {}, {}, {} };
	int lockonCnt=0;

	bool isLClick = false;
	bool isJamming = false;
	bool isMagShot = false;

private:

	C_BulletManager() {
		normalBulletTex.Load("Assets/Image/Bullet/bullet.png");
		magneticBulletTex.Load("Assets/Image/Bullet/GetMagBullet.png");
		enemy1BulletTex.Load("Assets/Image/Bullet/MagBullet.png");
		enemy2BulletTex.Load("Assets/Image/Bullet/MagBullet2.png");
		enemy3BulletTex.Load("Assets/Image/Bullet/circle.png");
		bossBulletTex.Load("Assets/Image/Bullet/BossBullet.png");
		bossBullet2Tex.Load("Assets/Image/Bullet/EnemyBullet.png");
	}

public:
	static C_BulletManager& GetInstance()
	{
		static C_BulletManager instance;
		return instance;
	}
};

#define BULLET_MGR C_BulletManager::GetInstance()
