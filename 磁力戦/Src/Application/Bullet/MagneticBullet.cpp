#include "MagneticBullet.h"
#include "../Scene.h"

C_MagneticBullet::C_MagneticBullet(KdTexture* tex, Math::Vector2 pos)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Radius = 16;
	magDeg = 0;
	degree = 0;
	cnt = 0;
	moveAmount = { 0,0 };
	isAbsorption = false;
	isShot = false;
	isHoming = false;
}

void C_MagneticBullet::Init()
{
}

void C_MagneticBullet::Update(Math::Vector2 playerpos, Math::Vector2 enemypos,int degreeIncrease)
{
	/*if (enemypos.x == 0 && enemypos.y == 0)
	{
		isShot = false;
	}*/

	

	if (!isShot) //放つ前
	{
		//自機の周りをまわる
		const float x = bullet.Pos.x - SCENE.GetPlayer()->GetPlayerPos().x;
		const float y = bullet.Pos.y - SCENE.GetPlayer()->GetPlayerPos().y;
		const float z = sqrt(x * x + y * y);

		magDeg += degreeIncrease;

		float a = cos(magDeg * 3.14f / 180) * 100;
		float b = sin(magDeg * 3.14f / 180) * 100;

		bullet.Pos.x = SCENE.GetPlayer()->GetPlayerPos().x + a;
		bullet.Pos.y = SCENE.GetPlayer()->GetPlayerPos().y + b;
	}
	else //放たれた後
	{
		const float a = bullet.Pos.x - destinationPos.x;
		const float b = bullet.Pos.y - destinationPos.y;
		const float c = sqrt(a * a + b * b);

		if (c<10)
		{
			isHoming = false;
		}

		if(isHoming)
		{
			degree = GetAngleDeg(bullet.Pos.x, bullet.Pos.y, destinationPos.x, destinationPos.y);

			moveAmount.x = cos(DirectX::XMConvertToRadians(degree)) * SPEED;
			moveAmount.y = sin(DirectX::XMConvertToRadians(degree)) * SPEED;
		}
	

		bullet.Pos += moveAmount;
	}
	
	

	//行列作成
	bullet.Trans = Math::Matrix::CreateTranslation(bullet.Pos.x, bullet.Pos.y, 0);
	bullet.Scale = Math::Matrix::CreateScale(1, 1, 1);
	bullet.Mat = bullet.Scale * bullet.Trans;
}

void C_MagneticBullet::Draw()
{
	Math::Color color = { 5,5,5,1 };

	SHADER.m_spriteShader.SetMatrix(bullet.Mat);
	SHADER.m_spriteShader.DrawTex(bullet.Tex, Math::Rectangle(0, 0, 16, 16), &color);
}

float C_MagneticBullet::GetAngleDeg(float srcX, float srcY, float destX, float destY)
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

void C_MagneticBullet::Shot()
{
	isShot = true;
}

void C_MagneticBullet::SetTarget(int enemytype, int enemynum)
{
	targetEnemyType = enemytype;
	targetEnemyNum = enemynum;
}
