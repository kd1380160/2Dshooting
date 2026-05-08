#pragma once

class C_EmitHeat
{
public:

	C_EmitHeat(KdTexture* explosiontex, Math::Vector2 pos,Math::Color color);

	void Update();
	void Draw();

	bool GetIsFinish();
private:

	KdTexture* tex;
	Math::Matrix mat;
	Math::Vector2 heatPos;
	Math::Vector2 heatMove;
	Math::Color heatColor;
	float alpha;
	float size;
	float degree;
	float speed;
	int lifeTime;
};