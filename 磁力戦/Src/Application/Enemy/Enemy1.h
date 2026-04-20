#pragma once
#include "EnemyBase.h"


class C_Enemy1 :public C_EnemyBase
{
public:

	C_Enemy1(KdTexture* enemy,int num);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	bool GetBulletHitCheck() { return isHit; }


private:

	static const int MAGNETIC_BULLET_MAX = 10;
	KdTexture* magneticBulletTex;
	KdTexture* magneticBulletGetTex;
	int shotCnt;

	static const int ENEMY_RADIUS = 32;
	bool isHit;
	

};
