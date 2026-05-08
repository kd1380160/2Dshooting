#include "NormalBullet.h"
#include "../Scene.h"

C_NormalBullet::C_NormalBullet(Math::Vector2 pos, KdTexture* tex)
{
	bullet.Pos = pos;
	bullet.Move = { 0,10 };
	bullet.Tex=tex;
	bullet.Radius = 16;
}

void C_NormalBullet::Update()
{


	bullet.Pos += bullet.Move;

	bullet.Scale = Math::Matrix::CreateScale(1, 1, 1);
	bullet.Trans = Math::Matrix::CreateTranslation(bullet.Pos.x + SCENE.GetPlayer()->GetShakeAmount(), bullet.Pos.y + SCENE.GetPlayer()->GetShakeAmount(), 0);
	bullet.Mat = bullet.Scale * bullet.Trans;
}

void C_NormalBullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(bullet.Mat);
	SHADER.m_spriteShader.DrawTex(bullet.Tex, Math::Rectangle{ 0,0,16,16 });
}
