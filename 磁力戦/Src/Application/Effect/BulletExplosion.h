#pragma once

class C_BulletExplosion
{
public:

	C_BulletExplosion(KdTexture* explosiontex,Math::Vector2 pos);
	
	void Update();
	void Draw();
	bool GetIsAnimFin() { return isAnimFinish; }

private:

	KdTexture* tex;
	int animXCnt;
	int animYCnt;
	Math::Matrix mat;
	Math::Vector2 exPos;
	const float SIZE = 3.0f;
	bool isAnimFinish;
};