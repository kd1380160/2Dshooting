#include "Generator.h"
#include "../Scene.h"

C_Generator::C_Generator(KdTexture* tex, int num)
{
	enemy.Tex = tex;
	enemy.Pos = { (float)(-300 + num * 600),400 };
	enemy.HP = 20;
	enemy.Move = { 0,-10 };
	isLockOn = false;
	isHit = false;
	rotateAngle = 0;
}

void C_Generator::Init()
{
}

void C_Generator::Update()
{
	enemy.Pos += enemy.Move;
	if (enemy.Pos.y <= 200)enemy.Pos.y = 200;

	LockOn();

	if (BULLET_MGR.EnemyHitCheck(enemy.Pos, ENEMY_RADIUS))
	{
		enemy.HP--;
		if (enemy.HP <= 0)enemy.HP = 0;
		isHit = true;
	}
	else
	{
		isHit = false;
	}

	rotateAngle += 70;
	if (rotateAngle >= 360)rotateAngle = 0;

	rotateMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotateAngle));
	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale * rotateMat * enemy.Trans;
}

void C_Generator::Draw()
{
	Math::Color col = { 1,1,1,1 };
	if (isLockOn)col = { 10,10,10,1 };

	SHADER.m_spriteShader.SetMatrix(enemy.Mat);
	SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle{ 0,0,64,64 },&col);
}

void C_Generator::LockOn()
{
	const float x = enemy.Pos.x - SCENE.GetMousePos().x;
	const float y = enemy.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < ENEMY_RADIUS)
	{
		isLockOn = true;
	}
}
