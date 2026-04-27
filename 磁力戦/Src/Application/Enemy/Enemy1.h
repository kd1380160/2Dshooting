#pragma once
#include "EnemyBase.h"


class C_Enemy1 :public C_EnemyBase
{
public:

	C_Enemy1(KdTexture* enemy, KdTexture* breakTex, int num);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	bool GetBulletHitCheck() { return isHit; }
	

private:

	bool isHit;
	int shotCnt;
	static const int ENEMY_RADIUS = 32;
};
