#pragma once
#include"EnemyBase.h"

class C_Boss : public C_EnemyBase
{
public:
	C_Boss(KdTexture* tex, KdTexture* shieldTex, KdTexture* breakTex, KdTexture* LockOnTex);

	void Init();
	void Update(int generatorHp);
	void Draw();
	void Release();
	void LockOn();
	void BossLockOnAnimUpdate();
	void BossLockOnAnimDraw();
	int GetBossHp() { return boss.HP; }
	int GetSheildRadius() { return SHIELS_RADIUS; }
	void DecleaseBossHp() { boss.HP -= 1; }
	Math::Vector2 GetBossPos() { return boss.Pos; }
	bool GetIsLockOn() { return isLockOn; }
	bool GetFinisher() { return canFinisher; }
	bool GetisDead() { return isDead; }
	bool GetNowStatus() { return isSecond; }
	bool GetIsFinishAnim() { return boss.isFinishAnim; }
	int GetBossRadius()const { return BOSS_RADIUS; }
private:

	S_Enemy boss;
	const int BOSS_HP_MAX = 100;
	const int BOSS_RADIUS = 64;
	const int SHIELS_RADIUS = 64*2.5;
	bool isLockOn;
	int bossMoveXangle;
	const int bossShieldCutoutTexPos[8] = { 0,128,256,384,512,640,768,896 };
	int angle;
	int bullet2angle;
	int bullet2angleAdd;
	int bossLV1Angle;
	int bossLV1AngleDegree;
	int bossLV1AngleAdd;
	int shotCnt;
	int shotToPlayerCnt;
	int shieldCutoutPos;
	int canFinisher;
	bool isShield;
	bool isMove;
	bool isDead;
	bool isSecond;
	Math::Matrix bossShieldMat;
	Math::Matrix bossShieldRotateMat;
	Math::Matrix bossShieldScaleMat;
	KdTexture* bossShieldTex;
	bool isShot;
	int phaseInterval;
	int deadCnt;
};