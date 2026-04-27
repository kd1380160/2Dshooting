#pragma once
#include"EnemyBase.h"

class C_Boss : public C_EnemyBase
{
public:
	C_Boss(KdTexture* tex, KdTexture* shieldTex, KdTexture* breakTex);

	void Init();
	void Update(int generatorHp);
	void Draw();
	void Release();
	void LockOn();
	int GetBossHp() { return boss.HP; }
	void DecleaseBossHp() { boss.HP -= 1; }
	Math::Vector2 GetBossPos() { return boss.Pos; }
	bool GetIsLockOn() { return isLockOn; }
	bool GetFinisher() { return canFinisher; }
	bool GetisDead() { return isDead; }
	bool GetIsFinishAnim() { return boss.isFinishAnim; }
private:

	S_Enemy boss;
	const int BOSS_HP_MAX = 100;
	const int BOSS_RADIUS = 64;
	bool isLockOn;
	int bossMoveXangle;
	const int bossShieldCutoutTexPos[8] = { 0,128,256,384,512,640,768,896 };
	int angle;
	int bullet2angle;
	int bullet2angleAdd;
	int shotCnt;
	int shotToPlayerCnt;
	int shieldCutoutPos;
	int canFinisher;
	bool isShield;
	bool isMove;
	bool isDead;
	Math::Matrix bossShieldMat;
	Math::Matrix bossShieldScaleMat;
	KdTexture* bossShieldTex;
	bool isShot;
	int phaseInterval;
	int deadCnt;
};