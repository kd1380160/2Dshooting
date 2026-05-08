#include "Enemy1.h"
#include "../Scene.h"
#include"../Bullet/BulletManager.h"


C_Enemy1::C_Enemy1(KdTexture* tex,KdTexture* breakTex, KdTexture* enginetex, KdTexture* lockonTex,
	int num,int nowwave, int setCnt)
{
	enemy.Tex = tex;
	enemy.BreakTex = breakTex;
	enemy.EngineTex = enginetex;
	enemy.LockOnTex = lockonTex;
	nowWave = nowwave;
	nowSet = setCnt;
	number = num;
	//enemy.Pos = { (float)( - 300 + 200 * num),400};
	//enemy.Pos = {(float)(rand()%(1280-ENEMY_RADIUS)-640),400};
	if (nowWave == Wave1)
	{
		//enemy.Pos = { (float)(-550 + 150 * (rand() % 8) + (rand() % 100 - 50)),400 };

		enemy.Pos = {(float)( - 200 + 100 * num) ,400};
	}
	else if (nowWave == Wave3)
	{
		switch (setCnt)
		{
		case 1:
			enemy.Pos = {(float)( - 100 + 200 * num),500};
			break;
		case 2:
			enemy.Pos = { (float)(-300+200*num),500};
			break;
		case 3:
			enemy.Pos = { (float)(-100+50*num),500 };
			break;
		}
	}
	enemy.Move = { 0,-10 };
	enemy.Radius = ENEMY_RADIUS;
	shotCnt = 0;
	shotRandCnt = 0;
	enemy.HP = ENEMY_HP_MAX;
	isLockOn = false;
	isHit = false;
	isTutorial = false;
	isAppear = false;
	enemy.isFinishAnim = false;
	enemy.animCnt = 0;
	enemy.engineAnimCnt = 0;
}

C_Enemy1::C_Enemy1(KdTexture* tex, KdTexture* breakTex, KdTexture* enginetex, KdTexture* lockonTex, bool istutorial)
{
	enemy.Tex = tex;
	enemy.BreakTex = breakTex;
	enemy.EngineTex = enginetex;
	enemy.LockOnTex = lockonTex;
	isTutorial = istutorial;
	enemy.Radius = ENEMY_RADIUS;
	enemy.Pos = { 0,500 };
	enemy.Move = { 0,-10 };
	enemy.HP = ENEMY_HP_MAX;
	isLockOn = false;
	isHit = false;
	enemy.isFinishAnim = false;
	isAppear = false;
	enemy.animCnt = 0;
	enemy.engineAnimCnt = 0;
	shotCnt = 0;
}

void C_Enemy1::Init()
{
}

void C_Enemy1::Update(Math::Vector2 playerpos)
{
	if (!isTutorial)
	{
		enemy.Pos += enemy.Move;
		if (nowWave == Wave1)
		{
			switch (number)
			{
			case 0:
				if (enemy.Pos.y <= 220)enemy.Pos.y = 220;
				break;
			case 1:
				if (enemy.Pos.y <= 200)enemy.Pos.y = 200;
				break;
			case 2:
				if (enemy.Pos.y <= 180)enemy.Pos.y = 180;
				break;
			case 3:
				if (enemy.Pos.y <= 200)enemy.Pos.y = 200;
				break;
			case 4:
				if (enemy.Pos.y <= 220)enemy.Pos.y = 220;
				break;
			}
		}
		else if (nowWave == Wave3)
		{
			if (enemy.Pos.y <= 150)enemy.Pos.y = 150;
		}

		LockOn();

		shotRandCnt++;
		if (shotRandCnt >= rand() % 16 + 50)
		{
			shotCnt++;
			if (shotCnt == 10)
			{
				//’e‚ª–³‚¯‚ê‚Î¶¬
				BULLET_MGR.ShotEnemy1Bullet(enemy.Pos);
			}
			else if (shotCnt == 20)
			{
				//’e‚ª–³‚¯‚ê‚Î¶¬
				BULLET_MGR.ShotEnemy1Bullet(enemy.Pos);
			}
			else if (shotCnt == 30)
			{
				BULLET_MGR.ShotBossBullet2(enemy.Pos, 0, -5);
				shotRandCnt = 0;
				shotCnt = 0;
			}
		}

		if (enemy.HP > 0)
		{
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
				
					for (int j = 0;j < 40;++j)
					{
						EFFECT_MGR.SpawnEnemyDebri(enemy.Pos, { 0.7f,0.9f,0.7f,1.0f });
					}
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
			if (enemy.animCnt >= 24)
			{
				enemy.animCnt = 24;
				enemy.isFinishAnim = true;
			}
		}

		if (isLockOn)
		{
			LockOnAnimUpdate();
		}
		if (isFinishLockOnAnim)
		{
			if (!isReduction)
			{
				lockOnSize -= 0.4f;
				if (lockOnSize <= 5.0f)
				{
					lockOnSize = 5.0f;
					isReduction = true;
				}
			}
			else
			{
				lockOnSize += 0.4f;
				if (lockOnSize >= 7.0f)
				{
					lockOnSize = 7.0f;
					isFinishReduction = true;
				}
			}

			if (isFinishReduction)
			{
				lockOnBlinkingCnt++;
			}
		}
	}
	else
	{
		if (!isAppear)
		{
			enemy.Pos += enemy.Move;
			if (enemy.Pos.y <= 200)
			{
				enemy.Pos.y = 200;
				isAppear = true;
			}
		}

		if (SCENE_MGR.GetIsFinishPage2())
		{
			LockOn();
		}

		if (isAppear)
		{
			shotCnt++;
			if (shotCnt == 10)
			{
				//’e‚ª–³‚¯‚ê‚Î¶¬
				BULLET_MGR.ShotEnemy1Bullet(enemy.Pos);
				shotCnt = 0;
			}
		}

		if (enemy.HP > 0)
		{
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

					for (int j = 0;j < 40;++j)
					{
						EFFECT_MGR.SpawnEnemyDebri(enemy.Pos, { 0.7f,0.9f,0.7f,1.0f });
					}
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
			if (enemy.animCnt >= 24)
			{
				enemy.animCnt = 24;
				enemy.isFinishAnim = true;
			}
		}

		if (isLockOn)
		{
			LockOnAnimUpdate();
		}
		if (isFinishLockOnAnim)
		{
			if (!isReduction)
			{
				lockOnSize -= 0.4f;
				if (lockOnSize <= 5.0f)
				{
					lockOnSize = 5.0f;
					isReduction = true;
				}
			}
			else
			{
				lockOnSize += 0.4f;
				if (lockOnSize >= 7.0f)
				{
					lockOnSize = 7.0f;
					isFinishReduction = true;
				}
			}

			if (isFinishReduction)
			{
				lockOnBlinkingCnt++;
			}
		}

	}
	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x + SCENE.GetPlayer()->GetShakeAmount(), enemy.Pos.y + SCENE.GetPlayer()->GetShakeAmount(), 0);
	enemy.Mat = enemy.Scale * enemy.Trans;

	enemy.Scale = Math::Matrix::CreateScale(lockOnSize, lockOnSize, 1);
	enemy.LockOnMat = enemy.Scale * enemy.Trans;

	enemy.Scale = Math::Matrix::CreateScale(2, -2, 1);
	enemy.Trans = Math::Matrix::CreateTranslation(enemy.Pos.x + SCENE.GetPlayer()->GetShakeAmount(), enemy.Pos.y + SCENE.GetPlayer()->GetShakeAmount() + SCENE.GetPlayer()->GetShakeAmount(), 0);
	enemy.EngineMat = enemy.Scale  * enemy.Trans;
}

void C_Enemy1::Draw()
{
	Math::Color col = { 3,3,3,1 };
	if (isHit)
	{
		col = { 1,1,1,1 };
		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.BreakTex, Math::Rectangle(64 * (enemy.animCnt / 3), 0, 64, 64), &col);
	}
	else
	{
		col = { 3,3,3,1 };
		SHADER.m_spriteShader.SetMatrix(enemy.EngineMat);
		SHADER.m_spriteShader.DrawTex(enemy.EngineTex, Math::Rectangle{ 64 * (enemy.engineAnimCnt / 3),0,64,64 });

		SHADER.m_spriteShader.SetMatrix(enemy.Mat);
		SHADER.m_spriteShader.DrawTex(enemy.Tex, Math::Rectangle(64 * (enemy.animCnt / 5), 0, 64, 64),&col);
	}
	
	if (isLockOn)
	{
		LockOnAnimDraw();
	}
	if (isLockOn&&!isHit&&isFinishLockOnAnim)
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
		SHADER.m_spriteShader.DrawTex(enemy.LockOnTex, Math::Rectangle{ 0,0,17,17 },&col);
	}
}

void C_Enemy1::LockOn()
{
	const float x = enemy.Pos.x - SCENE.GetMousePos().x;
	const float y = enemy.Pos.y - SCENE.GetMousePos().y;
	const float z = sqrt(x * x + y * y);

	if (z < ENEMY_RADIUS)
	{
		isLockOn = true;
	}
}


