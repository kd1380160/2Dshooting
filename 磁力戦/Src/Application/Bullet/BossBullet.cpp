#include "BossBullet.h"
#include"../Scene.h"

C_BossBullet::C_BossBullet(KdTexture* tex, Math::Vector2 pos, int degree, int speed)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Radius = 16;
	isAbsorption = false;
	bullet.Move.x = cos(DirectX::XMConvertToRadians(degree)) * speed;
	//	bullet.Move.y = -10;
	if (degree > 180&&ENEMY_MGR.GetBossHp() > 0)degree -= 180;
	bullet.Move.y = -sin(DirectX::XMConvertToRadians(degree)) * speed;
	
}

void C_BossBullet::Init()
{
}

void C_BossBullet::Update(Math::Vector2 playerpos)
{

	//自機に近づいたら自機の周りをまわる
	const float x = bullet.Pos.x - SCENE.GetPlayer()->GetPlayerPos().x;
	const float y = bullet.Pos.y - SCENE.GetPlayer()->GetPlayerPos().y;
	const float z = sqrt(x * x + y * y);

	if (z < 130)
	{

		//自機に向かって近づいてくる
		float degree = GetAngleDeg(bullet.Pos.x, bullet.Pos.y, SCENE.GetPlayer()->GetPlayerPos().x, SCENE.GetPlayer()->GetPlayerPos().y);
		bullet.Move.x = cos(DirectX::XMConvertToRadians(degree)) * 10;
		bullet.Move.y = sin(DirectX::XMConvertToRadians(degree)) * 10;
	}

	//ある程度まで近づいたら回転運動に移行
	if (z < 100)isAbsorption = true;

	bullet.Pos += bullet.Move;

	bullet.Scale = Math::Matrix::CreateScale(1, 1, 1);
	bullet.Trans = Math::Matrix::CreateTranslation(bullet.Pos.x, bullet.Pos.y, 0);
	bullet.Mat = bullet.Scale * bullet.Trans;
}

void C_BossBullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(bullet.Mat);
	SHADER.m_spriteShader.DrawTex(bullet.Tex, Math::Rectangle{ 0,0,16,16 });
}

float C_BossBullet::GetAngleDeg(float srcX, float srcY, float destX, float destY)
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
