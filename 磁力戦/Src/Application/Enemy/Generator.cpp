#include "Generator.h"
#include "../Scene.h"

C_Generator::C_Generator(KdTexture* tex, KdTexture* lockontex, int num)
{
	enemy.Tex = tex;
	enemy.LockOnTex = lockontex;
	enemy.Pos = { (float)(-300 + num * 600),400 };
	enemy.HP = 20;
	enemy.Move = { 0,-10 };
	enemy.Radius = ENEMY_RADIUS;
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

	if (BULLET_MGR.EnemyHitCheck(enemy.Pos, ENEMY_RADIUS, false))
	{
		enemy.HP--;
		if (enemy.HP <= 0)enemy.HP = 0;
		isHit = true;
	}
	else
	{
		isHit = false;
	}

	if (isLockOn)
	{
		LockOnAnimUpdate();
	}
	if (isFinishLockOnAnim)
	{
		lockOnBlinkingCnt++;
	}

	rotateAngle += 70;
	if (rotateAngle >= 360)rotateAngle = 0;

	rotateMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotateAngle));
	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale * rotateMat * enemy.Trans;


	enemy.Scale = Math::Matrix::CreateScale(7, 7, 1);
	enemy.LockOnMat = enemy.Scale * enemy.Trans;
}

void C_Generator::Draw()
{
	Math::Color col = { 1,1,1,1 };
	if (isLockOn)col = { 10,10,10,1 };

	SHADER.m_spriteShader.SetMatrix(enemy.Mat);
	SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle{ 0,0,64,64 },&col);

	if (isLockOn)
	{
		LockOnAnimDraw();
	}

	if (isLockOn && !isHit && isFinishLockOnAnim)
	{
		if (lockOnBlinkingCnt >= 7)
		{
			col = { 2,0,0,1 };
		}
		if (lockOnBlinkingCnt >= 14)
		{
			lockOnBlinkingCnt = 0;
			col = { 20,0,0,1 };
		}

		SHADER.m_spriteShader.SetMatrix(enemy.LockOnMat);
		SHADER.m_spriteShader.DrawTex(enemy.LockOnTex, Math::Rectangle{ 0,0,17,17 }, &col);
	}
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
