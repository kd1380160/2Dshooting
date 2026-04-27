#pragma once

struct S_Enemy
{
	KdTexture* Tex;
	KdTexture* BreakTex;
	Math::Matrix Mat;
	Math::Matrix Trans;
	Math::Matrix Scale;
	Math::Matrix Rot;
	Math::Vector2 Pos;
	Math::Vector2 Move;
	int HP;
	int Radius;
	int Shield;
	bool isFinishAnim;
	int animCnt;
};