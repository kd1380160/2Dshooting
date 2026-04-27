#include "Enemy2Bullet.h"
#include "../Scene.h"

C_Enemy2Bullet::C_Enemy2Bullet(KdTexture* tex, Math::Vector2 pos,Math::Vector2 move)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Move = move;
	isAbsorption = false;
}

void C_Enemy2Bullet::Update(Math::Vector2 playerpos)
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

	/*if (!isAbsorption)
	{
		座標確定
		bullet.Pos += bulletMove;
	}*/

	bullet.Pos += bullet.Move;

	//行列作成
	bullet.Trans = Math::Matrix::CreateTranslation(bullet.Pos.x, bullet.Pos.y, 1);
	bullet.Scale = Math::Matrix::CreateScale(1, 1, 1);
	bullet.Mat = bullet.Scale * bullet.Trans;
}

void C_Enemy2Bullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(bullet.Mat);
	SHADER.m_spriteShader.DrawTex(bullet.Tex, Math::Rectangle(0, 0, 16, 16));
}

float C_Enemy2Bullet::GetAngleDeg(float srcX, float srcY, float destX, float destY)
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
