#include "Enemy3.h"
#include "../Scene.h"

C_Enemy3::C_Enemy3(KdTexture* tex,KdTexture* breaktex, KdTexture* enginetex, KdTexture* lockonTex)
{
	enemy.Tex = tex;
	enemy.BreakTex = breaktex;
	enemy.EngineTex = enginetex;
	enemy.LockOnTex = lockonTex;
	//enemy.Pos = { (float)( - 300 + 200 * num),400};
	//enemy.Pos = { (float)(-550 + 150 * (rand() % 8) + (rand() % 100 - 50)),400 };
	enemy.Pos = { 0,400 };
	enemy.Move = { 0,-10 };
	enemy.Radius = ENEMY_RADIUS;
	enemy.HP = ENEMY_HP_MAX;
	shotCnt = 160;
	isLockOn =		false;
	isHit =			false;
	isJamming =		false;
	enemy.animCnt = 0;
	enemy.isFinishAnim = false;
	enemy.engineAnimCnt = 0;
}

void C_Enemy3::Init()
{
}

void C_Enemy3::Update(Math::Vector2 playerpos)
{
	enemy.Pos += enemy.Move;
	if (enemy.Pos.y <= 200)enemy.Pos.y = 200;

	LockOn();

	shotCnt++;
	if (shotCnt >= 240)
	{
		if ((shotCnt - 240) % 10 == 0)
		{
			isJamming = true;
			BULLET_MGR.ShotEnemy3Bullet(enemy.Pos);
		}

		if (shotCnt >= 360)
		{
			shotCnt = 0;
			isJamming = false;
		}
	}


	if (BULLET_MGR.EnemyHitCheck(enemy.Pos, ENEMY_RADIUS, false))
	{
		enemy.HP--;
		if (enemy.HP <= 0)
		{
			enemy.HP = 0;
			if (isHit == false)
			{
				isHit = true;
				enemy.animCnt = 0;
			}
		}
	}

	//エンジンアニメーション
	enemy.engineAnimCnt++;
	if (enemy.engineAnimCnt >= 21)
	{
		enemy.engineAnimCnt = 0;
	}

	//死亡アニメーション
	enemy.animCnt++;
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

	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale * enemy.Trans;

	enemy.EngineMat = enemy.Scale * enemy.Rot * enemy.Trans;

	enemy.Scale = Math::Matrix::CreateScale(7, 7, 1);
	enemy.LockOnMat = enemy.Scale * enemy.Trans;

	
}

void C_Enemy3::Draw()
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
		SHADER.m_spriteShader.DrawTex(enemy.EngineTex, Math::Rectangle{ 64 * (enemy.engineAnimCnt / 3),0,64,64 });

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

void C_Enemy3::LockOn()
{
	const float x = enemy.Pos.x - SCENE.GetMousePos().x;
	const float y = enemy.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < ENEMY_RADIUS)
	{
		isLockOn = true;
	}
}
