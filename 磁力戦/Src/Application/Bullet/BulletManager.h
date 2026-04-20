#pragma once
#include "MagneticBullet.h"
#include "NormalBullet.h"
#include"Enemy1Bullet.h"
#include"Enemy2Bullet.h"


class C_BulletManager
{
public:

	void Draw();
	void Update();
	void Init();

	void SpawnMagBullet(Math::Vector2 enemyPos);
	
	void ShotNormalBullet(Math::Vector2 playerPos);
	void ShotEnemy1Bullet(Math::Vector2 enemyPos);
	void ShotEnemy2Bullet(Math::Vector2 enemyPos, int num);
	void ShotMagBullet();

	bool EnemyHitCheck(Math::Vector2 pos,int radius);

	void Release();

private:

	//存在可能な磁力弾の最大数(10)
	static const int MAGNETIC_BULLET_MAX = 30;
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
	
	//存在可能な通常弾の最大数(30)
	static const int NORMAL_BULLET_MAX = 30;
	C_NormalBullet* normalBullets[NORMAL_BULLET_MAX] = {};
	KdTexture normalBulletTex;



	bool isLClick;
private:

	C_BulletManager() {
		normalBulletTex.Load("Assets/Image/Bullet/bullet.png");
		magneticBulletTex.Load("Assets/Image/Bullet/GetMagBullet.png");
		enemy1BulletTex.Load("Assets/Image/Bullet/MagBullet.png");
		enemy2BulletTex.Load("Assets/Image/Bullet/MagBullet2.png");
	}

public:
	static C_BulletManager& GetInstance()
	{
		static C_BulletManager instance;
		return instance;
	}
};

#define BULLET_MGR C_BulletManager::GetInstance()
