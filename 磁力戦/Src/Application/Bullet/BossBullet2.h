#pragma once
#include "BulletBase.h"

//吸えない弾
class C_BossBullet2 : public C_BulletBase
{
public:

	C_BossBullet2(KdTexture* tex, Math::Vector2 pos, int degree);
	C_BossBullet2(KdTexture* tex, Math::Vector2 pos, Math::Vector2 playerPos);
	C_BossBullet2(KdTexture* tex, Math::Vector2 pos, int moveX,int moveY);

	void Init();
	void Update(Math::Vector2 playerpos);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);

private:
	float angle;
};