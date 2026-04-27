#include "BossBullet2.h"

C_BossBullet2::C_BossBullet2(KdTexture* tex, Math::Vector2 pos, int degree)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Radius = 16;
	
	bullet.Move.x = cos(DirectX::XMConvertToRadians(degree)) * 5;
	//	bullet.Move.y = -10;
	if (degree > 180)degree -= 180;
	bullet.Move.y = -sin(DirectX::XMConvertToRadians(degree)) * 5;
}

C_BossBullet2::C_BossBullet2(KdTexture* tex, Math::Vector2 pos, Math::Vector2 playerPos)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Radius = 16;

	angle = GetAngleDeg(bullet.Pos.x, bullet.Pos.y, playerPos.x, playerPos.y);
	bullet.Move.x = cos(DirectX::XMConvertToRadians(angle)) * 7;
	bullet.Move.y = sin(DirectX::XMConvertToRadians(angle)) * 7;
}

C_BossBullet2::C_BossBullet2(KdTexture* tex, Math::Vector2 pos, int moveX, int moveY)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Radius = 16;

	bullet.Move.x = moveX;
	bullet.Move.y = moveY;
}

void C_BossBullet2::Init()
{
}

void C_BossBullet2::Update(Math::Vector2 playerpos)
{
	

	bullet.Pos += bullet.Move;

	bullet.Scale = Math::Matrix::CreateScale(1, 1, 1);
	bullet.Trans = Math::Matrix::CreateTranslation(bullet.Pos.x, bullet.Pos.y, 0);
	bullet.Mat = bullet.Scale * bullet.Trans;
}

void C_BossBullet2::Draw()
{
	SHADER.m_spriteShader.SetMatrix(bullet.Mat);
	SHADER.m_spriteShader.DrawTex(bullet.Tex, Math::Rectangle{ 0,0,16,16 });
}

float C_BossBullet2::GetAngleDeg(float srcX, float srcY, float destX, float destY)
{
	float rad;	//ラジアン
	float deg;	//ディグリー
	float a;	//底辺
	float b;	//高さ

	//目的地から元の位置を引く！
	a = destX - srcX;
	b = destY - srcY;

	//角度を求める
	rad = atan2(b, a);

	//ディグリーに直す
	deg = DirectX::XMConvertToDegrees(rad);

	//負の値を正の値に直す
	if (deg < 0)
	{
		deg += 360;
	}

	return deg;
}
