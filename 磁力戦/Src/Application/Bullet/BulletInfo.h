#pragma once

struct S_Bullet
{
	KdTexture* Tex;
	Math::Matrix Mat;
	Math::Matrix Trans;
	Math::Matrix Scale;
	Math::Vector2 Pos;
	Math::Vector2 Move;
	int Radius;
};