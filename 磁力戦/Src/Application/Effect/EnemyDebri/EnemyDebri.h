#pragma once

class C_EnemyDebri
{
public:

	C_EnemyDebri(KdTexture* explosiontex, Math::Vector2 pos, Math::Color color);

	void Update();
	void Draw();

	bool GetIsFinish();
private:

	KdTexture* tex;
	Math::Matrix mat;
	Math::Vector2 debriPos;
	Math::Vector2 debriMove;
	Math::Color debriColor;
	const float SIZE = 3.0f;
	float alpha;
};