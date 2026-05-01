#pragma once

struct S_Enemy
{
	KdTexture* Tex;
	KdTexture* BreakTex;
	KdTexture* EngineTex;
	KdTexture* LockOnTex;
	Math::Matrix Mat;
	Math::Matrix EngineMat;
	Math::Matrix LockOnMat;
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
	int engineAnimCnt;
};