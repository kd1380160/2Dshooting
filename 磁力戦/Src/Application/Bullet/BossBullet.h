#pragma once
#include"BulletBase.h"

class C_BossBullet :public C_BulletBase
{
public:
	C_BossBullet(KdTexture* tex, Math::Vector2 pos, int degree,int speed);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
	bool GetIsAbsorption() { return isAbsorption; }
private:
	bool isAbsorption;
	
};