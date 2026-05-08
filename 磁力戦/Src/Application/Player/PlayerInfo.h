#pragma once

struct S_player
{
	KdTexture* HP4Tex;
	KdTexture* HP3Tex;
	KdTexture* HP2Tex;
	KdTexture* HP1Tex;
	KdTexture* EngineTex;
	KdTexture* EngineBaseTex;
	KdTexture* ExplosionTex;
	Math::Matrix Mat;
	Math::Matrix Trans;
	Math::Matrix Scale;
	Math::Vector2 Pos;
	Math::Vector2 Move;
	Math::Color Color;
	int Hp;
	int Speed;
};