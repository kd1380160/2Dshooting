#pragma once
#include"BulletBase.h"

class C_NormalBullet:public C_BulletBase
{
public:
	C_NormalBullet(Math::Vector2 pos,KdTexture* tex);

	void Update();
	void Draw();


private:
	
};