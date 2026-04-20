#pragma once
#include "BulletBase.h"

class C_Enemy2Bullet :public C_BulletBase
{
public:

	C_Enemy2Bullet(KdTexture* tex, Math::Vector2 pos, int num);

	void Update(Math::Vector2 playerpos);
	void Draw();

	float GetAngleDeg(float srcX, float srcY, float destX, float destY);
	bool GetIsAbsorption() const { return isAbsorption; }

private:

	const Math::Vector2 bulletMoveList[3] = { {-3,-5},{0,-7},{3,-5} };

	bool isAbsorption;	//プレイヤーに吸収されたかどうか

};
