#pragma once
#include"EnemyBase.h"

class C_Enemy2 :public C_EnemyBase
{
public:

	C_Enemy2(KdTexture* tex, KdTexture* breaktex, KdTexture* enginetex, KdTexture* lockonTex, int num, Math::Vector2 pos);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	void LockOn();
	
	bool GetBulletHitCheck() const { return isHit; }
	
private:

	int shotRedBulletCnt;
	bool isHit;
	static const int ENEMY_RADIUS = 32;
	static const int ENEMY_HP_MAX = 3;
	int shotCnt;
	int angle;
	int redBulletCnt=0;
	int enemyNumber;
	const Math::Vector2 bulletMoveList[3] = { {-3,-5},{0,-7},{3,-5} };
};