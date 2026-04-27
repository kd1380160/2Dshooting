#pragma once
#include "BulletBase.h"

class C_Enemy2Bullet :public C_BulletBase
{
public:

	C_Enemy2Bullet(KdTexture* tex, Math::Vector2 pos, Math::Vector2 move);

	void Update(Math::Vector2 playerpos);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
	bool GetIsAbsorption() const { return isAbsorption; }

private:

	

	bool isAbsorption;	//プレイヤーに吸収されたかどうか

};
