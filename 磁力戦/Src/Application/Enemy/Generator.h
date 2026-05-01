#pragma once
#include "EnemyBase.h"

class C_Generator :public C_EnemyBase
{
public:
	C_Generator(KdTexture* tex,KdTexture* lockontex, int num);
	void Init();
	void Update();
	void Draw();
	void LockOn();
	bool GetBulletHitCheck() const { return isHit; }
	int GetHp() const { return enemy.HP; }
private:
	bool isHit;
	static const int ENEMY_RADIUS = 32;
	int rotateAngle;
	Math::Matrix rotateMat;
};