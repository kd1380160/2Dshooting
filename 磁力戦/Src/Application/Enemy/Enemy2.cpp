#include "Enemy2.h"
#include "../Scene.h"

C_Enemy2::C_Enemy2(KdTexture* tex, KdTexture* breaktex, KdTexture* enginetex, KdTexture* lockonTex, int num)
{
	enemy.Tex = tex;
	enemy.BreakTex = breaktex;
	enemy.EngineTex = enginetex;
	enemy.LockOnTex = lockonTex;
	enemyNumber = num;
	enemy.Pos = { (float)(-550 + 150 * (rand() % 8) + (rand() % 100 - 50)),400 };
	enemy.Move = { 0,-10 };
	angle = 0;
	if (enemyNumber == 0)
	{
		enemy.Pos = { -670,390 };
		angle = BULLET_MGR.GetAngleDeg(enemy.Pos.x, enemy.Pos.y, -600, 260);
		enemy.Move.x= cos(DirectX::XMConvertToRadians(angle)) * 7;
		enemy.Move.y= sin(DirectX::XMConvertToRadians(angle)) * 7;
	}
	if (enemyNumber == 1)
	{
		enemy.Pos = { 670,390 };
		angle = BULLET_MGR.GetAngleDeg(enemy.Pos.x, enemy.Pos.y, 600, 260);
		enemy.Move.x = cos(DirectX::XMConvertToRadians(angle)) * 7;
		enemy.Move.y = sin(DirectX::XMConvertToRadians(angle)) * 7;
	}
	
	isLockOn = false;
	isHit = false;
	enemy.isFinishAnim = false;
	enemy.animCnt = 0;
	enemy.engineAnimCnt = 0;
	shotCnt = 0;
	shotRedBulletCnt = 0;
	enemy.Radius = ENEMY_RADIUS;
	enemy.HP = ENEMY_HP_MAX;
}

void C_Enemy2::Init()
{
}

void C_Enemy2::Update(Math::Vector2 playerpos)
{
	enemy.Pos += enemy.Move;
	if (enemyNumber==0)
	{
		if (enemy.Pos.y <= 260)enemy.Pos.y = 260;
		if (enemy.Pos.x >= -600)enemy.Pos.x = -600;
	}
	else if(enemyNumber==1)
	{
		if (enemy.Pos.y <= 260)enemy.Pos.y = 260;
		if (enemy.Pos.x <= 600)enemy.Pos.x = 600;
	}
	else
	{
		if (enemy.Pos.y <= 200)enemy.Pos.y = 200;
	}

	LockOn();

	shotCnt++;
	if (shotCnt >= 45)
	{
		shotRedBulletCnt++;
		int random = rand() % 3;
		//弾が無ければ生成
		for (int i = 0;i < 3;i++)
		{
			if (enemyNumber == 0||enemyNumber==1)
			{
				if (shotRedBulletCnt >= 3)
				{
					if (i == random)
					{
						BULLET_MGR.ShotBossBullet2(enemy.Pos, (angle - 30) + 30 * i);
						shotRedBulletCnt = 0;
					}
					else
					{
						BULLET_MGR.ShotEnemy2Bullet(enemy.Pos, (angle - 30) + 30 * i);
					}
				}
				else
				{
					BULLET_MGR.ShotEnemy2Bullet(enemy.Pos, (angle-30)+30*i);
				}
			}
			else
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
		}
		
		shotCnt = 0;
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

	enemy.engineAnimCnt++;
	if (enemy.engineAnimCnt >= 21)
	{
		enemy.engineAnimCnt = 0;
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

	if (isLockOn)
	{
		LockOnAnimUpdate();
	}
	if (isFinishLockOnAnim)
	{
		lockOnBlinkingCnt++;
	}

	if (enemyNumber == 0)
	{
		enemy.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(angle+90));
	}
	else if (enemyNumber == 1)
	{
		enemy.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(angle +90));
	}
	else
	{
		enemy.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(angle));

	}
	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x, enemy.Pos.y, 0);
	enemy.Mat = enemy.Scale *enemy.Rot* enemy.Trans;

	enemy.EngineMat = enemy.Scale * enemy.Rot * enemy.Trans;

	enemy.Scale = Math::Matrix::CreateScale(7, 7, 1);
	enemy.LockOnMat = enemy.Scale * enemy.Trans;

}

void C_Enemy2::Draw()
{
	Math::Color col = { 1,1,1,1 };


	if (isHit)
	{
		Math::Color col = { 1,1,1,1 };
		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.BreakTex, Math::Rectangle(64 * (enemy.animCnt/3), 0, 64, 64), &col);
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(enemy.EngineMat);
		SHADER.m_spriteShader.DrawTex(enemy.EngineTex, Math::Rectangle{ 64 * (enemy.engineAnimCnt / 3),0,64,64 });

		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle(64 * (enemy.animCnt / 5	), 0, 64, 64), &col);
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
