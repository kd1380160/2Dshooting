#include "Boss.h"
#include"../Bullet/BulletManager.h"
#include"../Scene.h"

C_Boss::C_Boss(KdTexture* tex, KdTexture* shieldTex, KdTexture* breakTex)
{
	boss.Tex = tex;
	boss.BreakTex = breakTex;
	boss.Pos = { 0,400 };
	boss.Move = { 0,-3 };
	boss.HP = BOSS_HP_MAX;
	boss.Shield = 10;
	boss.Radius = 64;
	bossShieldTex = shieldTex;
	isShield = true;
	isMove = true;
	isShot = false;
	isLockOn = false;
	canFinisher = false;
	isDead = false;
	boss.animCnt = 0;
	boss.isFinishAnim = false;
	shieldCutoutPos = 7;
	shotCnt = 0;
	shotToPlayerCnt = 0;
	bossMoveXangle = 0;
	angle = 0;
	bullet2angle = 0;
	bullet2angleAdd = 120;
	phaseInterval = 0;
	deadCnt = 0;
}


void C_Boss::Init()
{
	
}

void C_Boss::Update(int generatorHp)
{	
	if (boss.HP > 0)
	{
		if (boss.Pos.y < 250)
		{
			boss.Pos.y = 250;
			boss.Move.y = 0;
			isShot = true;
		}

		//ジェネレーターのHPが0になったらシールドを解除する
		if (isShield)
		{
			if (generatorHp <= 0)
			{
				isShield = false;
				isMove = false;
				isShot = false;
				angle = 30;
				shotCnt = 0;
				bullet2angleAdd = 120;
			}
		}
		else
		{
			LockOn();
			//シールド破壊後、敵の弾が全て消えたら弾撃ち・動きを再開
			if (!BULLET_MGR.EnemyBulletAliveCheck())
			{
				isShot = true;
				isMove = true;
			}
		}

		//ボスの体力が半分以下になったら弾の角度を狭くする
		if (boss.HP <= BOSS_HP_MAX / 2)
		{
			angle = 40;
			bullet2angleAdd = 100;
		}

		shieldCutoutPos = generatorHp / 5;
		if (shieldCutoutPos >= 7)shieldCutoutPos = 7;

		if (isShot)
		{
			shotCnt++;
			if (isShield) //シールド破壊前（第一形態)
			{
				if (shotCnt <= 20)
				{
					BULLET_MGR.ShotBossBullet(boss.Pos, angle,4);
					angle += 3;
				}
				else if (shotCnt <= 30)
				{
					BULLET_MGR.ShotBossBullet2(boss.Pos, angle);
					angle += 3;
				}
				else if (shotCnt <= 40)
				{
					BULLET_MGR.ShotBossBullet(boss.Pos, angle,4);
					angle += 3;
				}
				else if (shotCnt <= 50)
				{
					BULLET_MGR.ShotBossBullet2(boss.Pos, angle);
					angle += 3;
				}
				else if (shotCnt >= 80)
				{
					shotCnt = 0;
				}
				if (angle >= 360)angle -= 360;
			}
			else //シールド破壊後（第二形態）
			{
				shotToPlayerCnt++;

				if (shotCnt >= 4)
				{
					//赤弾（吸えない）
					BULLET_MGR.ShotBossBullet2(boss.Pos, angle);
					BULLET_MGR.ShotBossBullet2(boss.Pos, angle + bullet2angleAdd);
					shotCnt = 0;
				}

				if (shotToPlayerCnt % 5 == 0)
				{
					//吸える弾をばらまく
					if (boss.HP <= BOSS_HP_MAX / 2) //体力が半分以下で範囲を狭くする
					{
						BULLET_MGR.ShotBossBullet(boss.Pos, rand() % (81) + (angle + 10),4);
					}
					else
					{
						BULLET_MGR.ShotBossBullet(boss.Pos, rand() % (101) + (angle + 10),4);
					}
				}
				if (shotToPlayerCnt >= 30)
				{
					//プレイヤーの方向に向かって弾を撃つ
					BULLET_MGR.ShotBossBullet2(boss.Pos, SCENE.GetPlayer()->GetPlayerPos());
					shotToPlayerCnt = 0;
				}
			}
		}

		//弾が当たったらHPを減らす
		if (BULLET_MGR.EnemyHitCheck(boss.Pos, boss.Radius))
		{
			if (!isShield)
			{
				boss.HP -= 1;
			}
		}

		if (isMove)
		{
			////左右に揺らす
			//bossMoveXangle += 1;
			//if (bossMoveXangle >= 360)
			//{
			//	bossMoveXangle -= 360;
			//}

			////cosカーブをボスのX座標に影響させる
			//boss.Move.x = cosf(DirectX::XMConvertToRadians(bossMoveXangle)) * 3;

			boss.Pos += boss.Move;
		}

		if (!isMove) //中央に来た時に止める(第二形態への移行のため)
		{
			if (boss.Pos.x < 0)
			{
				boss.Pos.x += 1;
				if (boss.Pos.x >= 0)boss.Pos.x = 0;
				bossMoveXangle = 0;
			}
			else
			{
				boss.Pos.x -= 1;
				if (boss.Pos.x <= 0)boss.Pos.x = 0;
				bossMoveXangle = 0;
			}
		}
	}
	else //ボスのHPが0になったら
	{
		BULLET_MGR.EnemyHitCheck(boss.Pos, boss.Radius);
		deadCnt++;

		if (deadCnt >= 90&&deadCnt < 210)
		{
			if (deadCnt % 5 == 0)
			{
				//ボスの周りに弾をばらまく
				for (int i = 0;i < 16;i++)
				{
					BULLET_MGR.ShotBossBullet(boss.Pos, 22.5f * i,15);
				}
			}
		}
		if (deadCnt == 250)
		{
			canFinisher = true;
		}

		if (canFinisher)
		{
			if (!BULLET_MGR.MagneticBulletAliveCheck())
			{
				if (!isDead)
				{
					isDead = true;
					boss.animCnt = 8;
				}
			}
		}
	}

	
	if (isDead)
	{
		boss.animCnt++;
		if (boss.animCnt >= 136)
		{
			boss.animCnt = 136;
			boss.isFinishAnim = true;
		}
	}
	


	boss.Scale = Math::Matrix::CreateScale(2.5f, -2.5f, 1);
	boss.Trans = Math::Matrix::CreateTranslation(boss.Pos.x, boss.Pos.y, 0);
	boss.Mat = boss.Scale * boss.Trans;

	bossShieldScaleMat = Math::Matrix::CreateScale(2.5f, 2.5f, 1);
	bossShieldMat = bossShieldScaleMat * boss.Trans;

}

void C_Boss::Draw()
{
	Math::Color color = { 2,2,2,1 };
	if (boss.HP <= BOSS_HP_MAX / 2)
	{
		if (isLockOn)
		{
			color = { 10,0,0,1 };
		}
		else
		{
			color = { 1,0,0,1 };
		}
	}
	else
	{
		if (isLockOn)
		{
			color = { 10,10,10,1 };
		}
	}
	
	if (!isDead)
	{
		SHADER.m_spriteShader.SetMatrix(boss.Mat);
		SHADER.m_spriteShader.DrawTex(boss.Tex, Math::Rectangle{ 0,0,128,128 }, &color);
	}
	else
	{
		Math::Color col = { 2,2,2,1 };
		SHADER.m_spriteShader.SetMatrix(boss.Mat);
		SHADER.m_spriteShader.DrawTex(boss.BreakTex, Math::Rectangle(128 * (boss.animCnt / 8), 0, 128, 128), &col);

	}

	if (isShield)
	{
		SHADER.m_spriteShader.SetMatrix(bossShieldMat);
		SHADER.m_spriteShader.DrawTex(bossShieldTex, Math::Rectangle{ bossShieldCutoutTexPos[shieldCutoutPos],0,128,128 });
	}
}

void C_Boss::Release()
{
	boss.Tex->Release();
}

void C_Boss::LockOn()
{
	const float x = boss.Pos.x - SCENE.GetMousePos().x;
	const float y = boss.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < BOSS_RADIUS)
	{
		isLockOn = true;
	}
}
