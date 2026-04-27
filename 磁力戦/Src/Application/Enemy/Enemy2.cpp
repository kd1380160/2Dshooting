#include "Enemy2.h"
#include "../Scene.h"

C_Enemy2::C_Enemy2(KdTexture* tex, KdTexture* breaktex, int num)
{
	enemy.Tex = tex;
	enemy.BreakTex = breaktex;
	//enemy.Pos = { (float)( - 300 + 200 * num),400};
	enemy.Pos = { (float)(rand() % (1280 - ENEMY_RADIUS) - 640),400 };
	enemy.Move = { 0,-10 };
	shotCnt = 0;
	shotRedBulletCnt = 0;
	isLockOn = false;
	isHit = false;
	enemy.isFinishAnim = false;
	enemy.animCnt = 0;
}

void C_Enemy2::Init()
{
}

void C_Enemy2::Update(Math::Vector2 playerpos)
{
	enemy.Pos += enemy.Move;
	if (enemy.Pos.y <= 200)enemy.Pos.y = 200;

	LockOn();

	shotCnt++;
	if (shotCnt >= 45)
	{
		shotRedBulletCnt++;
		int random = rand() % 3;
		//弾が無ければ生成
		for (int i = 0;i < 3;i++)
		{
			if (shotRedBulletCnt >= 3)
			{
				if (i == random)
				{
					BULLET_MGR.ShotBossBullet2(enemy.Pos, bulletMoveList[i].x, bulletMoveList[i].y);
					shotRedBulletCnt = 0;
				}
				else
				{
					BULLET_MGR.ShotEnemy2Bullet(enemy.Pos, bulletMoveList[i]);
				}
			}
			else
			{
				BULLET_MGR.ShotEnemy2Bullet(enemy.Pos, bulletMoveList[i]);
			}
		}
		
		shotCnt = 0;
	}

	if (BULLET_MGR.EnemyHitCheck(enemy.Pos, ENEMY_RADIUS))
	{
		if (isHit == false)
		{
			isHit = true;
			enemy.animCnt = 0;
		}
	}

	enemy.animCnt++;

	if (isHit)
	{
		if (enemy.animCnt >= 30)
		{
			enemy.animCnt = 30;
			enemy.isFinishAnim = true;
		}
	}


	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale * enemy.Trans;
}

void C_Enemy2::Draw()
{
	Math::Color col = { 1,1,1,1 };
	if (isLockOn)col = { 10,10,10,1 };

	if (isHit)
	{
		Math::Color col = { 1,1,1,1 };
		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.BreakTex, Math::Rectangle(64 * (enemy.animCnt/3), 0, 64, 64), &col);
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle(64 * (enemy.animCnt / 5	), 0, 64, 64), &col);
	}
}

void C_Enemy2::LockOn()
{
	const float x = enemy.Pos.x - SCENE.GetMousePos().x;
	const float y = enemy.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < ENEMY_RADIUS)
	{
		isLockOn = true;
	}
}
