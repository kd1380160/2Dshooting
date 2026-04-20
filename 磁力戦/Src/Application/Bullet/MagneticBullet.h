#pragma once
#include"BulletBase.h"

class C_MagneticBullet:public C_BulletBase
{
public:

	C_MagneticBullet(KdTexture* tex, Math::Vector2 pos);

	void Init();
	void Update(Math::Vector2 playerpos, Math::Vector2 enemypos);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
	bool GetIsAbsorption() { return isAbsorption; }
	void SetIsShotFlg(bool flg) { isShot = flg; }
	void SetIsHomingTrue() { isHoming = true; }
	void SetDestinationPos(Math::Vector2 destpos) { destinationPos = destpos; }
private:

	Math::Vector2 destinationPos = {0,300};
	
	Math::Vector2 moveAmount;
	float degree;
	float magDeg;
	static const int SPEED = 13;
	bool isShot;	//ï˙ÇΩÇÍÇΩÇ©Ç«Ç§Ç©
	bool isAbsorption;	//ÉvÉåÉCÉÑÅ[Ç…ãzé˚Ç≥ÇÍÇΩÇ©Ç«Ç§Ç©
	bool isHoming;

	int cnt;
};