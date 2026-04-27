#pragma once
#include"EnemyBase.h"

class C_Enemy3 :public C_EnemyBase
{
public:
	C_Enemy3(KdTexture* enemy, KdTexture* breaktex, int num);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	bool GetBulletHitCheck() { return isHit; }
private:

	bool isHit;
	static const int ENEMY_RADIUS = 32;
	int shotCnt;
};