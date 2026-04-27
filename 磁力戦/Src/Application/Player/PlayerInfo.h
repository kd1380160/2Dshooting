#pragma once

struct S_player
{
	KdTexture* Tex;
	KdTexture* EngineTex;
	KdTexture* EngineBaseTex;
	Math::Matrix Mat;
	Math::Matrix Trans;
	Math::Matrix Scale;
	Math::Vector2 Pos;
	Math::Vector2 Move;
	Math::Color Color;
	int Hp;
};