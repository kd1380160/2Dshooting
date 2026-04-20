#include "Boss.h"
#include"../Bullet/BulletManager.h"

C_Boss::C_Boss(KdTexture* tex)
{
	boss.Tex = tex;
	boss.Pos = { 0,400 };
	boss.Move = { 0,-3 };
	boss.HP = 5;
	boss.Radius = 64;
}

C_Boss::~C_Boss()
{

}

void C_Boss::Init()
{
	
}

void C_Boss::Update()
{
	
	if (boss.Pos.y < 250)boss.Pos.y = 250;


	if (BULLET_MGR.EnemyHitCheck(boss.Pos, boss.Radius))
	{
		boss.HP -= 1;
		
	}

	boss.Pos += boss.Move;
	

	boss.Scale = Math::Matrix::CreateScale(1.5f, -1.5f, 1);
	boss.Trans = Math::Matrix::CreateTranslation(boss.Pos.x, boss.Pos.y, 0);
	boss.Mat = boss.Scale * boss.Trans;
}

void C_Boss::Draw()
{
	SHADER.m_spriteShader.SetMatrix(boss.Mat);
	SHADER.m_spriteShader.DrawTex(boss.Tex, Math::Rectangle{ 0,0,128,128 });
}

void C_Boss::Release()
{
	boss.Tex->Release();
}
