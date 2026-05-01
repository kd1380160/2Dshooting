#pragma once
#include"BulletInfo.h"


class C_BulletBase
{
public:

	 void Draw();
	 void Update();

	//ゲッター
	Math::Vector2 GetPos() { return bullet.Pos; }
	int GetRadius() { return bullet.Radius; }

protected:

	S_Bullet bullet;
};