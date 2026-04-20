#pragma once
#include "BulletBase.h"

class C_Enemy1Bullet:public C_BulletBase
{
public:
	C_Enemy1Bullet(KdTexture* tex,Math::Vector2 pos);

	void Update(Math::Vector2 playerpos);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
	bool GetIsAbsorption() { return isAbsorption; }

private:

	 Math::Vector2 bulletMove = {0,-5};
	bool isAbsorption;	//プレイヤーに吸収されたかどうか
};
