#pragma once
#include "EnemyBase.h"

class C_Enemy4 : public C_EnemyBase
{
public:
	C_Enemy4(KdTexture* tex, KdTexture* breaktex, KdTexture* engineTex, KdTexture* lockonTex);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	int GetHP() { return enemy.HP; }
	bool GetBulletHitCheck() const { return isHit; }
private:
	static const int ENEMY_RADIUS = 32;
	bool isHit;
	bool isAppear;
	int rotateAngle;
};
