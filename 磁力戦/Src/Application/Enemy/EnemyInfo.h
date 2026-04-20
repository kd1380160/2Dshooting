#pragma once

struct S_Enemy
{
	KdTexture* Tex;
	Math::Matrix Mat;
	Math::Matrix Trans;
	Math::Matrix Scale;
	Math::Vector2 Pos;
	Math::Vector2 Move;
	int HP;
	int Radius;
};