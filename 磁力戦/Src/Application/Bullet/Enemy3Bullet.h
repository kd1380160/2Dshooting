#pragma once
#include "BulletBase.h"

class C_Enemy3Bullet :public C_BulletBase
{
public:
	C_Enemy3Bullet(KdTexture* tex, Math::Vector2 pos);

	void Update(Math::Vector2 playerpos);
	void Draw();

	bool  GetIsAlpha() const { return isAlpha; }
	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
private:


	Math::Color color={1,1,1,1};
	bool isAlpha;
	float circleSize;
	float alpha;
	float Red, Green, Blue;
	int colorChangeCount = 0;

};