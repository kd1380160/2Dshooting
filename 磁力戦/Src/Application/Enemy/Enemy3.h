#pragma once
#include"EnemyBase.h"

class C_Enemy3 :public C_EnemyBase
{
public:
	C_Enemy3(KdTexture* enemy, KdTexture* breaktex,KdTexture* enginetex, KdTexture* lockonTex);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	bool GetBulletHitCheck()	const { return isHit; }
	bool GetIsJamming()			const { return isJamming; }
private:

	bool isHit;
	static const int ENEMY_RADIUS = 32;
	static const int ENEMY_HP_MAX = 5;
	int shotCnt;
	bool isJamming;
};