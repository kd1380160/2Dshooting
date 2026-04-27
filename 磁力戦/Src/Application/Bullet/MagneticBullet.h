#pragma once
#include"BulletBase.h"

class C_MagneticBullet:public C_BulletBase
{
public:

	C_MagneticBullet(KdTexture* tex, Math::Vector2 pos);

	void Init();
	void Update(Math::Vector2 playerpos, Math::Vector2 enemypos, int degreeIncrease);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
	bool GetIsAbsorption() { return isAbsorption; }
	bool GetIsShotFlg() { return isShot; }
	void Shot();
	void SetIsHomingTrue() { isHoming = true; }
	void SetDestinationPos(Math::Vector2 destpos) { destinationPos = destpos; }
	void SetTarget(int enemytype, int enemynum);

	int GetTargetEnemyType() const { return targetEnemyType; }
	int GetTargetEnemyNum() const { return targetEnemyNum; }
private:

	Math::Vector2 destinationPos = { 0,500 };
	
	Math::Vector2 moveAmount;
	float degree;
	float magDeg;
	static const int SPEED = 13;
	bool isShot;	//•ú‚½‚ê‚½‚©‚Ç‚¤‚©
	bool isAbsorption;	//ƒvƒŒƒCƒ„[‚É‹zû‚³‚ê‚½‚©‚Ç‚¤‚©
	bool isHoming;

	int targetEnemyNum ;	//’Ç”ö‚·‚é“G‚Ì”Ô†
	int targetEnemyType	;	//’Ç”ö‚·‚é“G‚Ìí—Ş
	int cnt;
};