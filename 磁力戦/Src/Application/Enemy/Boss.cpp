#include "Boss.h"
#include"../Bullet/BulletManager.h"
#include"../Scene.h"

C_Boss::C_Boss(KdTexture* tex, KdTexture* shieldTex, KdTexture* breakTex, KdTexture* LockOnTex)
{
	boss.Tex = tex;
	boss.BreakTex = breakTex;
	boss.LockOnTex = LockOnTex;
	boss.Pos = { 0,400 };
	boss.Move = { 0,-3 };
	boss.HP = BOSS_HP_MAX;
	boss.HP = 100;
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
	isSecond = false;
	shieldCutoutPos = 7;
	shotCnt = 0;
	shotToPlayerCnt = 0;
	bossMoveXangle = 0;
	angle = 0;
	bullet2angle = -90;
	bullet2angleAdd = 120;
	bossLV1Angle = 0;
	bossLV1AngleAdd = 2;
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
			if (bossLV1Angle > 0 && bossLV1Angle < 60)
			{
				bossLV1Angle -= 1;
				if (bossLV1Angle <= 0)bossLV1Angle = 0;
			}
			if (bossLV1Angle<0 && bossLV1Angle>-60)
			{
				bossLV1Angle += 1;
				if (bossLV1Angle >= 0)bossLV1Angle = 0;
			}
			boss.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(bossLV1Angle));
			//シールド破壊後、敵の弾が全て消えたら弾撃ち・動きを再開
			if (!BULLET_MGR.EnemyBulletAliveCheck()&&bossLV1Angle==0)
			{
				isShot = true;
				isMove = true;
				isSecond = true;
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
					BULLET_MGR.ShotBossBullet(boss.Pos, angle, 4);
					angle += 3;
				}
				else if (shotCnt <= 30)
				{
					BULLET_MGR.ShotBossBullet2(boss.Pos, angle);
					angle += 3;
				}
				else if (shotCnt <= 40)
				{
					BULLET_MGR.ShotBossBullet(boss.Pos, angle, 4);
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

				
				bossLV1AngleAdd++;
				bossLV1Angle = sin(bossLV1AngleAdd * 0.05) * 60.0f;
				boss.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(bossLV1Angle));
			}
			else //シールド破壊後（第二形態）
			{
				bullet2angle = BULLET_MGR.GetAngleDeg(boss.Pos.x, boss.Pos.y, SCENE.GetPlayer()->GetPlayerPos().x, SCENE.GetPlayer()->GetPlayerPos().y);
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

				if (isMove)
				{
					//左右に揺らす
					bossMoveXangle += 1;
					if (bossMoveXangle >= 360)
					{
						bossMoveXangle -= 360;
					}

					//cosカーブをボスのX座標に影響させる
					boss.Move.x = cosf(DirectX::XMConvertToRadians(bossMoveXangle)) * 3;
					boss.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(bullet2angle + 90));
					//boss.Pos += boss.Move;
				}
			}
		}

		//弾が当たったらHPを減らす
		if (isShield)
		{
			BULLET_MGR.EnemyHitCheck(boss.Pos, SHIELS_RADIUS, true);
		}
		else
		{
			if (BULLET_MGR.EnemyHitCheck(boss.Pos, boss.Radius,false))
			{
				boss.HP -= 1;
			}
		}
		
		boss.Pos += boss.Move;
		//if (!isMove) //中央に来た時に止める(第二形態への移行のため)
		//{
		//	if (boss.Pos.x < 0)
		//	{
		//		boss.Pos.x += 1;
		//		if (boss.Pos.x >= 0)boss.Pos.x = 0;
		//		bossMoveXangle = 0;
		//	}
		//	else
		//	{
		//		boss.Pos.x -= 1;
		//		if (boss.Pos.x <= 0)boss.Pos.x = 0;
		//		bossMoveXangle = 0;
		//	}
		//}
	}
	else //ボスのHPが0になったら
	{
		BULLET_MGR.EnemyHitCheck(boss.Pos, boss.Radius, false);
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

	
	//死亡アニメーション
	if (isDead)
	{
		boss.animCnt++;
		if (boss.animCnt >= 136)
		{
			boss.animCnt = 136;
			boss.isFinishAnim = true;
		}
	}
	
	if (isLockOn)
	{
		BossLockOnAnimUpdate();
	}
	if (isFinishLockOnAnim)
	{
		lockOnBlinkingCnt++;
	}
	
	boss.Scale = Math::Matrix::CreateScale(2.5f, -2.5f, 1);
	boss.Trans = Math::Matrix::CreateTranslation(boss.Pos.x, boss.Pos.y, 0);
	boss.Mat = boss.Scale *boss.Rot* boss.Trans;

	bossShieldRotateMat= Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(bossLV1Angle/2));
	bossShieldScaleMat = Math::Matrix::CreateScale(2.5f, 2.5f, 1);
	bossShieldMat = bossShieldScaleMat *bossShieldRotateMat* boss.Trans;

	if (!isDead)
	{
		//boss.Rot = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians((bullet2angle + 90) / 2));
		boss.Scale = Math::Matrix::CreateScale(11, 11, 1);
		boss.LockOnMat = boss.Scale * boss.Rot * boss.Trans;
	}
}

void C_Boss::Draw()
{
	Math::Color color = { 2,2,2,1 };
	
	if (!isDead)
	{
		//ボス描画
		SHADER.m_spriteShader.SetMatrix(boss.Mat);
		SHADER.m_spriteShader.DrawTex(boss.Tex, Math::Rectangle{ 0,0,128,128 }, &color);	
	}
	else
	{
		//倒した後のアニメーション
		Math::Color col = { 2,2,2,1 };
		SHADER.m_spriteShader.SetMatrix(boss.Mat);
		SHADER.m_spriteShader.DrawTex(boss.BreakTex, Math::Rectangle(128 * (boss.animCnt / 8), 0, 128, 128), &col);

	}

	if (isLockOn)
	{
		BossLockOnAnimDraw();
	}

	if (isLockOn && !isDead && isFinishLockOnAnim)
	{
		if (lockOnBlinkingCnt >= 7)
		{
			color = { 2,0,0,1 };
		}
		if (lockOnBlinkingCnt >= 14)
		{
			lockOnBlinkingCnt = 0;
			color = { 20,0,0,1 };
		}

		SHADER.m_spriteShader.SetMatrix(boss.LockOnMat);
		SHADER.m_spriteShader.DrawTex(boss.LockOnTex, Math::Rectangle{ 0,0,17,17 }, &color);
	}

	//シールド表示
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

void C_Boss::BossLockOnAnimUpdate()
{
	if (isFinishLockOnAnim)return;

	float rad;	//ラジアン
	float deg;	//ディグリー
	float a;	//底辺
	float b;	//高さ
	float distance;

	for (int i = 0;i < LOCKON_DIVISION_NUM;++i)
	{
		distance = sqrt((boss.Pos.x - lockOnPos[i].x) * (boss.Pos.x - lockOnPos[i].x) + (boss.Pos.y - lockOnPos[i].y) * (boss.Pos.y - lockOnPos[i].y));

		//目的地から元の位置を引く！
		a = boss.Pos.x - lockOnPos[i].x;
		b = boss.Pos.y - lockOnPos[i].y;

		//角度を求める
		rad = atan2(b, a);

		//ディグリーに直す
		deg = DirectX::XMConvertToDegrees(rad);

		//負の値を正の値に直す
		if (deg < 0)
		{
			deg += 360;
		}

		lockOnMoveAmount.x = cos(DirectX::XMConvertToRadians(deg)) * (distance / 10);
		lockOnMoveAmount.y = sin(DirectX::XMConvertToRadians(deg)) * (distance / 10);

		lockOnPos[i] += lockOnMoveAmount;

		if (distance <= 50)
		{
			isFinishLockOnAnim = true;
		}
	}

	Math::Matrix trans, scale;
	scale = Math::Matrix::CreateScale(7, 7, 1);

	for (int i = 0;i < LOCKON_DIVISION_NUM;++i)
	{
		trans = Math::Matrix::CreateTranslation(lockOnPos[i].x, lockOnPos[i].y, 0);
		lockOnMat[i] = scale * trans;
	}
}

void C_Boss::BossLockOnAnimDraw()
{
	if (isFinishLockOnAnim)return;

	Math::Color col = { 20,0,0,1 };

	for (int i = 0;i < LOCKON_DIVISION_NUM;i++)
	{
		SHADER.m_spriteShader.SetMatrix(lockOnMat[i]);
		switch (i)
		{
		case 0:
			SHADER.m_spriteShader.DrawTex(boss.LockOnTex, Math::Rectangle{ 0,0,9,8 }, &col);
			break;
		case 1:
			SHADER.m_spriteShader.DrawTex(boss.LockOnTex, Math::Rectangle{ 8 ,0,9,8 }, &col);
			break;
		case 2:
			SHADER.m_spriteShader.DrawTex(boss.LockOnTex, Math::Rectangle{ 0,8,9,8 }, &col);
			break;
		case 3:
			SHADER.m_spriteShader.DrawTex(boss.LockOnTex, Math::Rectangle{ 8 ,8,9,8 }, &col);
			break;

		}
	}
}
