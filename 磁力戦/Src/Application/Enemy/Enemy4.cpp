#include "Enemy4.h"
#include "../Scene.h"

C_Enemy4::C_Enemy4(KdTexture* tex, KdTexture* breaktex,KdTexture* enginetex, KdTexture* lockonTex)
{
	enemy.Tex = tex;
	enemy.BreakTex = breaktex;
	enemy.EngineTex = enginetex;
	enemy.LockOnTex = lockonTex;
	if (rand() % 2 == 0) //左から出現、右に移動
	{
		enemy.Pos.x = -700+rand() % 101; // -650から-550の範囲でランダムに出現
		enemy.Move = { 3,0 };
		rotateAngle = 90;
	}
	else //右から出現、左に移動
	{
		enemy.Pos.x = 700+rand() % 101; // 650から750の範囲でランダムに出現
		enemy.Move = { -3,0 };
		rotateAngle = -90;
	}

	enemy.HP = 1;
	enemy.Radius = ENEMY_RADIUS;
	enemy.Pos.y = rand() % 301 - 200;
	isLockOn = false;
	isHit = false;
	isAppear = false;
	enemy.Radius = ENEMY_RADIUS;
	enemy.isFinishAnim = false;
	enemy.animCnt = 0;
	enemy.engineAnimCnt = 0;
}

void C_Enemy4::Init()
{
}

void C_Enemy4::Update(Math::Vector2 playerpos)
{
//	enemy.Move.x = rand() % 11 - 5;
	
	if (enemy.Pos.x < -850 )
	{
		enemy.Move.x *= -1;
		rotateAngle = 90;
	}
	else if (enemy.Pos.x > 850)
	{
		enemy.Move.x *= -1;
		rotateAngle = -90;
	}

	enemy.Pos += enemy.Move;
	
	LockOn();
	if (BULLET_MGR.EnemyHitCheck(enemy.Pos, ENEMY_RADIUS, false))
	{
		enemy.HP -= 1;
		if (enemy.HP <= 0)
		{
			if (isHit == false)
			{
				isHit = true;
				enemy.animCnt = 0;
			}
		}

	}


	enemy.animCnt++;
	enemy.engineAnimCnt++;
	if (enemy.engineAnimCnt >= 21)
	{
		enemy.engineAnimCnt = 0;
	}


	if (isHit)
	{
		if (enemy.animCnt >= 18)
		{
			enemy.animCnt = 18;
			enemy.isFinishAnim = true;
		}
	}

	if (isLockOn)
	{
		LockOnAnimUpdate();
	}
	if (isFinishLockOnAnim)
	{
		lockOnBlinkingCnt++;
	}

	enemy.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(rotateAngle));
	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale * enemy.Rot * enemy.Trans;

	enemy.EngineMat = enemy.Scale * enemy.Rot * enemy.Trans;

	enemy.Scale = Math::Matrix::CreateScale(7, 7, 1);
	enemy.LockOnMat = enemy.Scale * enemy.Trans;

	
}

void C_Enemy4::Draw()
{
	Math::Color col = { 2,2,2,1 };
	

	if (isHit)
	{
		Math::Color col = { 1,1,1,1 };
		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.BreakTex, Math::Rectangle(64 * (enemy.animCnt / 2), 0, 64, 64), &col);
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(enemy.EngineMat);
		SHADER.m_spriteShader.DrawTex(enemy.EngineTex, Math::Rectangle{ 64*(enemy.engineAnimCnt/3),0,64,64});

		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle(64 * (enemy.animCnt / 5), 0, 64, 64), &col);
	}

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

void C_Enemy4::LockOn()
{
	const float x = enemy.Pos.x - SCENE.GetMousePos().x;
	const float y = enemy.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < ENEMY_RADIUS)
	{
		isLockOn = true;
	}
}
