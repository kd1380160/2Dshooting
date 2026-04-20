#pragma once
#include"EnemyBase.h"

class C_Enemy2 :public C_EnemyBase
{
public:

	C_Enemy2(KdTexture* tex, int num);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();

	bool GetBulletHitCheck() const { return isHit; }
private:

	bool isHit;
	static const int ENEMY_RADIUS = 32;
	int shotCnt;
};