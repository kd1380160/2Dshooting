#pragma once
#include "EnemyBase.h"


class C_Enemy1 :public C_EnemyBase
{
public:

	C_Enemy1(KdTexture* enemy, KdTexture* breakTex, KdTexture* enginetex,KdTexture* lockonTex, int num, int nowwave,int setCnt);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	bool GetBulletHitCheck() const{ return isHit; }
	

private:

	bool isHit;
	int shotCnt;
	int shotRandCnt;
	int nowWave;
	int nowSet;
	static const int ENEMY_RADIUS = 32;
	static const int ENEMY_HP_MAX = 5;

};
