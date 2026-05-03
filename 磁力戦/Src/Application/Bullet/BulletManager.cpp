#include "BulletManager.h"
#include"../Scene.h"
#include"../Effect/EffectManager.h"
void C_BulletManager::Draw()
{
	//通常弾（プレイヤー発射）
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] != nullptr)
		{
			normalBullets[i]->Draw();
		}
	}


	//敵1弾
	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] != nullptr)
		{
			enemy1Bullets[i]->Draw();
		}
	}

	//敵2弾
	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] != nullptr)
		{
			enemy2Bullets[i]->Draw();
		}
	}

	//敵3弾
	for (int i = 0;i < ENEMY3_BULLET_MAX;i++)
	{
		if (enemy3Bullets[i] != nullptr)
		{
			enemy3Bullets[i]->Draw();
		}
	}

	//ボス弾
	for (int i = 0;i < BOSS_BULLET_MAX;i++)
	{
		if (bossBullets[i] != nullptr)
		{
			bossBullets[i]->Draw();
		}
	}

	//ボス弾2
	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		if (bossBullets2[i] != nullptr)
		{
			bossBullets2[i]->Draw();
		}
	}

	//磁力弾（プレイヤー発射）
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			magneticBullets[i]->Draw();
		}
	}
	if (isJamming) {
		for (int i = 0; i < 5; i++) {
			int y = rand() % 721-360;
			SHADER.m_spriteShader.SetMatrix(Math::Matrix::CreateTranslation(-640, 0, 0));
			SHADER.m_spriteShader.DrawLine(0, y, 1280, y, &Math::Color(100, 100, 255, 128)); // 半透明の青い線
		}
	}
}

void C_BulletManager::Update()
{
	Math::Vector2 playerpos = SCENE.GetPlayer()->GetPlayerPos();

	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (normalBullets[i] != nullptr)
		{
			normalBullets[i]->Update();

			if (normalBullets[i]->GetPos().y >= 400)
			{
				delete normalBullets[i];
				normalBullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (enemy1Bullets[i] != nullptr)
		{
			enemy1Bullets[i]->Update(playerpos);

			if (enemy1Bullets[i]->GetIsAbsorption())
			{
				delete  enemy1Bullets[i];
				enemy1Bullets[i] = nullptr;
			
				SpawnMagBullet(playerpos);
				continue;
			}

			//画面外に出た弾は消去
			if (enemy1Bullets[i]->GetPos().y <= -400)
			{
				delete enemy1Bullets[i];
				enemy1Bullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (enemy2Bullets[i] != nullptr)
		{
			enemy2Bullets[i]->Update(playerpos);

			if (enemy2Bullets[i]->GetIsAbsorption())
			{
				delete  enemy2Bullets[i];
				enemy2Bullets[i] = nullptr;

				SpawnMagBullet(playerpos);
				continue;
			}

			//画面外に出た弾は消去
			if (enemy2Bullets[i]->GetPos().y <= -400)
			{
				delete enemy2Bullets[i];
				enemy2Bullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < ENEMY3_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (enemy3Bullets[i] != nullptr)
		{
			enemy3Bullets[i]->Update(playerpos);

			if (enemy3Bullets[i]->GetIsAlpha())
			{
				delete enemy3Bullets[i];
				enemy3Bullets[i] = nullptr;
				continue;
			}

			//画面外に出た弾は消去
			if (enemy3Bullets[i]->GetPos().y <= -400)
			{
				delete enemy3Bullets[i];
				enemy3Bullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < ENEMY3_BULLET_MAX;++i)
	{
		if (enemy3Bullets[i] != nullptr)
		{
			break;
		}

		if (i == ENEMY3_BULLET_MAX - 1)
		{
			isJamming = false;
		}
	}

	for (int i = 0;i < BOSS_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (bossBullets[i] != nullptr)
		{
			bossBullets[i]->Update(playerpos);

			if (bossBullets[i]->GetIsAbsorption())
			{
				delete bossBullets[i];
				bossBullets[i] = nullptr;

				SpawnMagBullet(playerpos);
				continue;
			}

			//画面外に出た弾は消去
			if (bossBullets[i]->GetPos().y <= -400 || bossBullets[i]->GetPos().y >= 400
				|| bossBullets[i]->GetPos().x <= -700 || bossBullets[i]->GetPos().x >= 700)
			{
				delete bossBullets[i];
				bossBullets[i] = nullptr;
			}
		}
	}

	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (bossBullets2[i] != nullptr)
		{
			bossBullets2[i]->Update(playerpos);

			//画面外に出た弾は消去
			if (bossBullets2[i]->GetPos().y <= -400 || bossBullets2[i]->GetPos().y >= 400
				|| bossBullets2[i]->GetPos().x <= -700 || bossBullets2[i]->GetPos().x >= 700)
			{
				delete bossBullets2[i];
				bossBullets2[i] = nullptr;
			}
		}
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!isLClick)
		{
			isLClick = true;
			isMagShot = true;
			ENEMY_MGR.RegisterLockonEnemyNum();

			if (ENEMY_MGR.GetCanShotMagBullet())
			{
				for (int j = 0;j < LOCKON_MAX;j++)
				{
					lockonEnemyNumType[j][0] = -1;
					lockonEnemyNumType[j][1] = 6;

					lockonEnemyNumType[j][0] = ENEMY_MGR.GetLockonEnemyNum(j);
					lockonEnemyNumType[j][1] = ENEMY_MGR.GetLockonEnemyType(j);
				}

				for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
				{
					if (magneticBullets[i] != nullptr)
					{
						if (!isJamming) //磁力弾阻害が入っていない場合（敵3の弾が存在していない）
						{
							magneticBullets[i]->Shot();
							magneticBullets[i]->SetIsHomingTrue();
						}
					}
				}

				ShotMagBullet();
			}
		}
	}
	else
	{
		isLClick = false;
	}

	//ShotMagBullet();
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (magneticBullets[i] != nullptr)
		{
			if (SCENE_MGR.GetNowScene() == Game)
			{
				//磁力弾阻害が入っているかどうか
				if (!isJamming) //磁力弾阻害が入っていない場合（敵3の弾が存在していない）
				{
					if (magneticBullets[i]->GetIsShotFlg())
					{
						TrackingUpdate(i);
					}
					magneticBullets[i]->Update(SCENE.GetPlayer()->GetPlayerPos(), { 100,100 }, 5);
				}
				else //磁力弾阻害が入っている場合（敵3が生存）
				{
					magneticBullets[i]->Update(SCENE.GetPlayer()->GetPlayerPos(), { 100,100 }, 1);
				}
			}
			else if (SCENE_MGR.GetNowScene() == Tutorial)
			{
				magneticBullets[i]->Update(SCENE.GetPlayer()->GetPlayerPos(), { 100,100 }, 5);
			}
			

			//画面外に出た弾は消去
			if (magneticBullets[i]->GetPos().y >= 450 || magneticBullets[i]->GetPos().y <= -450
				|| magneticBullets[i]->GetPos().x >= 750 || magneticBullets[i]->GetPos().x <= -750)
			{
				delete magneticBullets[i];
				magneticBullets[i] = nullptr;
			}
		}
	}
}

void C_BulletManager::Init()
{
	isLClick = false;
	lockonCnt = 0;
	ClearAllBullet();
}

void C_BulletManager::TrackingUpdate(int num)
{
	//lockonEnemy4Cnt = 0;

	if (magneticBullets[num] != nullptr)
	{
		switch (SCENE_MGR.GetNowWave())
		{
		case Wave1:
			break;
		case Wave2:
			break;
		case Wave3:
			break;
		case Wave4:

			if (ENEMY_MGR.GetIsEnemyAlive(magneticBullets[num]->GetTargetEnemyType(), magneticBullets[num]->GetTargetEnemyNum()))
			{
				magneticBullets[num]->SetDestinationPos(ENEMY_MGR.GetLockOnEnemyPos(magneticBullets[num]->GetTargetEnemyType(), magneticBullets[num]->GetTargetEnemyNum()));
			}

			break;
		case Boss:

			if (!ENEMY_MGR.GetIsGeneratorAlive(0) && !ENEMY_MGR.GetIsGeneratorAlive(1))
			{
				if (ENEMY_MGR.GetIsBossSecond())
				{
					magneticBullets[num]->SetDestinationPos(ENEMY_MGR.GetBossPos());
				}
			}

			break;
		default:
			break;
		}
	}
}

void C_BulletManager::SpawnMagBullet(Math::Vector2 enemyPos)
{
	//弾が無ければ生成
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] == nullptr)
		{
			magneticBullets[i] = new C_MagneticBullet(&magneticBulletTex, enemyPos);
			break;
		}
	}
}

void C_BulletManager::ShotNormalBullet(Math::Vector2 playerPos)
{
	//弾が無ければ生成
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] == nullptr)
		{
			normalBullets[i] = new C_NormalBullet(playerPos, &normalBulletTex);
			break;
		}
	}
}

void C_BulletManager::ShotEnemy1Bullet(Math::Vector2 enemyPos)
{
	//弾が無ければ生成
	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] == nullptr)
		{
			enemy1Bullets[i] = new C_Enemy1Bullet(&enemy1BulletTex, enemyPos);
			break;
		}
	}
}

void C_BulletManager::ShotEnemy2Bullet(Math::Vector2 enemyPos, Math::Vector2 move)
{
	//弾が無ければ生成
	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] == nullptr)
		{
			enemy2Bullets[i] = new C_Enemy2Bullet(&enemy2BulletTex, enemyPos, move);
			break;
		}
	}
}

void C_BulletManager::ShotEnemy2Bullet(Math::Vector2 enemyPos, int angle)
{
	//弾が無ければ生成
	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] == nullptr)
		{
			enemy2Bullets[i] = new C_Enemy2Bullet(&enemy2BulletTex, enemyPos,angle);
			break;
		}
	}
}

void C_BulletManager::ShotEnemy3Bullet(Math::Vector2 enemyPos)
{
	//弾が無ければ生成
	for (int i = 0;i < ENEMY3_BULLET_MAX;i++)
	{
		if (enemy3Bullets[i] == nullptr)
		{
			isJamming = true;
			enemy3Bullets[i] = new C_Enemy3Bullet(&enemy3BulletTex, enemyPos);
			break;
		}
	}
}

void C_BulletManager::ShotBossBullet(Math::Vector2 bossPos,int degree, int speed)
{
	//弾が無ければ生成
	for (int i = 0;i < BOSS_BULLET_MAX;i++)
	{
		if (bossBullets[i] == nullptr)
		{
			bossBullets[i] = new C_BossBullet(&bossBulletTex,bossPos,degree,speed);
			break;
		}
	}
}

void C_BulletManager::ShotBossBullet2(Math::Vector2 bossPos, int degree)
{
	//弾が無ければ生成
	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		if (bossBullets2[i] == nullptr)
		{
			bossBullets2[i] = new C_BossBullet2(&bossBullet2Tex, bossPos, degree);
			break;
		}
	}
}

void C_BulletManager::ShotBossBullet2(Math::Vector2 bossPos, Math::Vector2 playerPos)
{
	//弾が無ければ生成
	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		if (bossBullets2[i] == nullptr)
		{
			bossBullets2[i] = new C_BossBullet2(&bossBullet2Tex, bossPos, playerPos);
			break;
		}
	}
}

void C_BulletManager::ShotBossBullet2(Math::Vector2 bossPos, int moveX, int moveY)
{
	//弾が無ければ生成
	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		if (bossBullets2[i] == nullptr)
		{
			bossBullets2[i] = new C_BossBullet2(&bossBullet2Tex, bossPos, moveX, moveY);
			break;
		}
	}
}

void C_BulletManager::ShotMagBullet()
{
	bool generatorAlive[2] = { false, false };
	int generatorCnt = 0;
	for (int i = 0;i < 2;i++)
	{
		if (ENEMY_MGR.GetIsGeneratorAlive(i))
		{
			generatorAlive[i] = true;
		}
	}

	int checkCnt = 0;
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			if (!magneticBullets[i]->GetIsHaveTarget())
			{
				if (SCENE_MGR.GetNowWave() != Boss)
				{
					while (1)
					{
						if ((lockonEnemyNumType[lockonCnt][1] == 0 || lockonEnemyNumType[lockonCnt][1] == 1 || lockonEnemyNumType[lockonCnt][1] == 2 || lockonEnemyNumType[lockonCnt][1] == 3 || lockonEnemyNumType[lockonCnt][1] == 4)
							&& (lockonEnemyNumType[lockonCnt][0] == 0 || lockonEnemyNumType[lockonCnt][0] == 1 || lockonEnemyNumType[lockonCnt][0] == 2 || lockonEnemyNumType[lockonCnt][0] == 3 || lockonEnemyNumType[lockonCnt][0] == 4))
						{
							magneticBullets[i]->SetTarget(lockonEnemyNumType[lockonCnt][1], lockonEnemyNumType[lockonCnt][0]);
							magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetLockOnEnemyPos(magneticBullets[i]->GetTargetEnemyType(), magneticBullets[i]->GetTargetEnemyNum()));
							magneticBullets[i]->SetIsHaveTarget();
							lockonCnt++;
							break;
						}
						else
						{
							checkCnt++;
							lockonCnt++;
						}
						if (lockonCnt >= 5)
						{
							lockonCnt = 0;
						}
						if (checkCnt >= 6)
						{
							//break;
						}
					}
				}
				else
				{
					if (generatorAlive[0] && generatorAlive[1])
					{
						if (ENEMY_MGR.GetIsLockonGenerator(0) && ENEMY_MGR.GetIsLockonGenerator(1))
						{
							magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetGeneratorPos(generatorCnt));
							magneticBullets[i]->SetIsHaveTarget();
							generatorCnt++;
							if (generatorCnt >= 2)generatorCnt = 0;
						}
						else if (ENEMY_MGR.GetIsLockonGenerator(0))
						{
							magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetGeneratorPos(0));
							magneticBullets[i]->SetIsHaveTarget();
						}
						else if (ENEMY_MGR.GetIsLockonGenerator(1))
						{
							magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetGeneratorPos(1));
							magneticBullets[i]->SetIsHaveTarget();
						}
					}
					else if (generatorAlive[0])
					{
						if (ENEMY_MGR.GetIsLockonGenerator(0))
						{
							magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetGeneratorPos(0));
							magneticBullets[i]->SetIsHaveTarget();
						}
					}
					else if (generatorAlive[1])
					{
						if (ENEMY_MGR.GetIsLockonGenerator(1))
						{
							magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetGeneratorPos(1));
							magneticBullets[i]->SetIsHaveTarget();
						}
					}
					else if (!generatorAlive[0] && !generatorAlive[1])//ジェネレーターが両方死ん出る場合（ボスの第2形態）
					{
						magneticBullets[i]->SetDestinationPos(ENEMY_MGR.GetBossPos());
						magneticBullets[i]->SetIsHaveTarget();
					}
				}
			}
		}
	}
}

void C_BulletManager::ShotMagBulletTutorial()
{
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			magneticBullets[i]->Shot();
		}
	}
}

bool  C_BulletManager::EnemyHitCheck(Math::Vector2 pos, int radius, bool shieldhit)
{
	//通常弾との当たり判定
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (normalBullets[i] != nullptr)
		{
			const float a = normalBullets[i]->GetPos().x - pos.x;
			const float b = normalBullets[i]->GetPos().y - pos.y;
			const float c = sqrt(a * a + b * b);
			const float sumRadius = normalBullets[i]->GetRadius() + radius;

			//当たってたらtrue
			if (c < sumRadius)
			{
				if (shieldhit)
				{
					EFFECT_MGR.SpawnBulletExplosion(normalBullets[i]->GetPos());
				}
				else
				{
					EFFECT_MGR.SpawnBulletExplosion(pos);
				}
				delete normalBullets[i];
				normalBullets[i] = nullptr;
				return true;
			}
		}

	}

	//磁力弾との当たり判定
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (magneticBullets[i] != nullptr)
		{
			const float a = magneticBullets[i]->GetPos().x - pos.x;
			const float b = magneticBullets[i]->GetPos().y - pos.y;
			const float c = sqrt(a * a + b * b);
			const float sumRadius = magneticBullets[i]->GetRadius() + radius;

			if (magneticBullets[i]->GetIsShotFlg())
			{
				//当たってたらtrue
				if (c < sumRadius)
				{
					if (shieldhit)
					{
						EFFECT_MGR.SpawnBulletExplosion(magneticBullets[i]->GetPos());
					}
					else
					{
						EFFECT_MGR.SpawnBulletExplosion(pos);
					}

					delete magneticBullets[i];
					magneticBullets[i] = nullptr;
					return true;
				}
			}
		}

	}

	//当たってなければfalse
	return false;
}

bool C_BulletManager::PlayerHitCHeck(Math::Vector2 pos, int radius)
{
	//通常弾との当たり判定
	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		//弾が存在する場合のみ更新
		if (bossBullets2[i] != nullptr)
		{
			const float a = bossBullets2[i]->GetPos().x - pos.x;
			const float b = bossBullets2[i]->GetPos().y - pos.y;
			const float c = sqrt(a * a + b * b);
			const float sumRadius = bossBullets2[i]->GetRadius() + radius;

			//当たってたらtrue
			if (c < sumRadius)
			{
				delete bossBullets2[i];
				bossBullets2[i] = nullptr;

				return true;
			}
		}

	}
	return false;
}

bool C_BulletManager::EnemyBulletAliveCheck()
{
	//敵1弾
	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] != nullptr)
		{
			return true;
		}
	}

	//敵2弾
	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] != nullptr)
		{
			return true;
		}
	}

	//敵3弾
	for (int i = 0;i < ENEMY3_BULLET_MAX;i++)
	{
		if (enemy3Bullets[i] != nullptr)
		{
			return true;
		}
	}

	//ボス弾
	for (int i = 0;i < BOSS_BULLET_MAX;i++)
	{
		if (bossBullets[i] != nullptr)
		{
			return true;
		}
	}

	//ボス弾2
	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		if (bossBullets2[i] != nullptr)
		{
			return true;
		}
	}
	return false;
}

bool C_BulletManager::MagneticBulletAliveCheck()
{
	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			return true;
		}
	}
	return false;
}

void C_BulletManager::Release()
{
	ClearAllBullet();

	normalBulletTex.Release();
	magneticBulletTex.Release();
	enemy1BulletTex.Release();
	enemy2BulletTex.Release();
	enemy3BulletTex.Release();
	bossBulletTex.Release();
	bossBullet2Tex.Release();
}

void C_BulletManager::ClearAllBullet()
{
	for (int i = 0;i < NORMAL_BULLET_MAX;i++)
	{
		if (normalBullets[i] != nullptr)
		{
			delete normalBullets[i];
			normalBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < MAGNETIC_BULLET_MAX;i++)
	{
		if (magneticBullets[i] != nullptr)
		{
			delete magneticBullets[i];
			magneticBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY1_BULLET_MAX;i++)
	{
		if (enemy1Bullets[i] != nullptr)
		{
			delete enemy1Bullets[i];
			enemy1Bullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY2_BULLET_MAX;i++)
	{
		if (enemy2Bullets[i] != nullptr)
		{
			delete enemy2Bullets[i];
			enemy2Bullets[i] = nullptr;
		}
	}

	for (int i = 0;i < ENEMY3_BULLET_MAX;i++)
	{
		if (enemy3Bullets[i] != nullptr)
		{
			delete enemy3Bullets[i];
			enemy3Bullets[i] = nullptr;
		}
	}

	for (int i = 0;i < BOSS_BULLET_MAX;i++)
	{
		if (bossBullets[i] != nullptr)
		{
			delete bossBullets[i];
			bossBullets[i] = nullptr;
		}
	}

	for (int i = 0;i < BOSS_BULLET2_MAX;i++)
	{
		if (bossBullets2[i] != nullptr)
		{
			delete bossBullets2[i];
			bossBullets2[i] = nullptr;
		}
	}
}

float C_BulletManager::GetAngleDeg(float srcX, float srcY, float destX, float destY)
{
	float rad;	//ラジアン
	float deg;	//ディグリー
	float a;	//底辺
	float b;	//高さ

	//目的地から元の位置を引く！
	a = destX - srcX;
	b = destY - srcY;

	//角度を求める
	rad = atan2(b, a);

	//ディグリーに直す
	deg = DirectX::XMConvertToDegrees(rad);

	//負の値を正の値に直す
	if (deg < 0)
	{
		deg += 360;
	}

	return deg;
}

int C_BulletManager::GetMagBulletHaveAmount()
{
	int cnt=0;
	for (int i = 0;i < MAGNETIC_BULLET_MAX;++i)
	{
		if (magneticBullets[i] != nullptr)
		{
			cnt++;
		}
	}

	return cnt;
}
