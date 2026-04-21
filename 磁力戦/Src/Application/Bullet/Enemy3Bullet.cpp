#include "Enemy3Bullet.h"

C_Enemy3Bullet::C_Enemy3Bullet(KdTexture* tex, Math::Vector2 pos)
{
	bullet.Tex = tex;
	bullet.Pos = pos;
	bullet.Move= { 0,-5 };
	circleSize = 3.0f;
	colorChangeCount = 0;
	alpha = 0.9f;
	isAlpha = false;
	Red = rand() % 256 / 255.0f + 0.5f;
	Green = rand() % 256 / 255.0f + 0.5f;
	Blue = rand() % 256 / 255.0f + 0.5f;
	color = { Red, Green, Blue, alpha };
}

void C_Enemy3Bullet::Update(Math::Vector2 playerpos)
{
	circleSize += 0.2f;
	colorChangeCount++;

	

	alpha -= 0.01f;
	if (alpha <= 0.0f)
	{
		isAlpha = true;
		alpha = 0;
	}

	if (colorChangeCount % 30 == 0)
	{
		//color = { 1,1,1,alpha };
		Red = rand() % 256 / 255.0f ;
		Green = rand() % 256 / 255.0f ;
		Blue = rand() % 256 / 255.0f ;
	}
	color = { Red, Green, Blue, alpha };
	//行列作成
	bullet.Trans = Math::Matrix::CreateTranslation(bullet.Pos.x, bullet.Pos.y, 1);
	bullet.Scale = Math::Matrix::CreateScale(circleSize, circleSize, 1);
	bullet.Mat = bullet.Scale * bullet.Trans;
}

void C_Enemy3Bullet::Draw()
{

	SHADER.m_spriteShader.SetMatrix(bullet.Mat);
	SHADER.m_spriteShader.DrawTex(bullet.Tex, Math::Rectangle(0, 0, 64, 64), &color);

	//SHADER.m_spriteShader.DrawCircle(bullet.Pos.x, bullet.Pos.y, circleSize, &Math::Color{ 1,1,1,1 }, false);
}
